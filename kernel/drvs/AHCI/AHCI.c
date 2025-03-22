#include "drvs/AHCI.h"
#include <string.h>
#include "tty.h"

void ahci_probe_port(volatile HBA_MEM* abar) {
	// search disks within implemented ports
	uint32_t pi = abar->pi;
	int i = 0;

	while (i < 16) {
		if (pi & 1) {
			int disktype = ahci_check_dev_type(&abar->ports[i]);
			if (disktype == AHCI_DEV_SATA) {
				write_string("SATA drive found at port ");
				putchar((char)i + 48);
				putchar('\n');

				ahci_port_rebase(&abar->ports[i], i);
				master_dev = &abar->ports[i];
			}
			else if (disktype == AHCI_DEV_SEMB) {
			}
			else if (disktype == AHCI_DEV_PM) {
			}
			else if (disktype == AHCI_DEV_SATAPI) {
			}
			else {
			}
		}
		i++;
		pi >>= 1;
	}
}

int ahci_check_dev_type(volatile HBA_PORT* port) {
	uint32_t sata_stat = port->sata_stat;

	uint8_t ipm = (sata_stat >> 8) & 0x0F;
	uint8_t det = sata_stat & 0x0F;

	if (det != HBA_PORT_DET_PRESENT)
		return AHCI_DEV_NULL;
	if (ipm != HBA_PORT_IPM_ACTIVE)
		return AHCI_DEV_NULL;

	switch (port->sig) {
		case SATA_SIG_ATA:
			return AHCI_DEV_SATA;
		case SATA_SIG_ATAPI:
			return AHCI_DEV_SATAPI;
		case SATA_SIG_SEMB:
			return AHCI_DEV_SEMB;
		case SATA_SIG_PM:
			return AHCI_DEV_PM;
		default:
			return AHCI_DEV_NULL;
	}
}

void ahci_port_rebase(volatile HBA_PORT* port, int portnr) {
	// rebases the ports memory location to something sensible
	ahci_stop_cmd(port);
	
	// command list offset = 1K * portnr
	// command list entry size = 32 bit
	// command list entry max count = 32
	// command list max size = 32 * 32 = 1M / port
	port->cl_base = AHCI_BASE + (portnr << 10);
	port->cl_base_u = 0; // not 64 bit mode
	memset((void*)port->cl_base, 0, 1024);
	
	// FIS offset = 32K + 256*portnr
	// FIS entry size = 256 bytes / port
	port->fis_base = AHCI_BASE + (32 << 10) + (portnr << 8);
	port->fis_base_u = 0;
	memset((void*)port->fis_base, 0, 256);


	// Command table offset: 40K + 8K * portnr
	// Command table size = 256*32 = 8K / port
	HBA_CMD_HEADER* cmdh = (HBA_CMD_HEADER*)(port->cl_base);
	for (size_t i = 0; i < 32; i++) {
		cmdh[i].prdtl = 8;
		cmdh[i].ctbl_desc_addr = AHCI_BASE + (40 << 10) + (portnr << 13) + (i << 8);
		cmdh[i].ctbl_desc_addr_u = 0;
		memset((void*)cmdh[i].ctbl_desc_addr, 0, 256);
	}

	ahci_start_cmd(port);
}

void ahci_start_cmd(volatile HBA_PORT* port) {
	// starts the command engine
	while (port->cmstat & HBA_PxCMD_CR) ; // wait until CR is clear
	
	port->cmstat |= HBA_PxCMD_FRE; // Allow fetching instructions
	port->cmstat |= HBA_PxCMD_ST; // Start command reading!
}

void ahci_stop_cmd(volatile HBA_PORT* port) {
	// stops the command engine
	port->cmstat &= ~HBA_PxCMD_ST; // Clear Start bit -> stop
	
	port->cmstat &= ~HBA_PxCMD_FRE; // Don't accept new FISes
	
	// Wait until FR (bit14), CR (bit15) are cleared
	while(1)
	{
		if (port->cmstat & HBA_PxCMD_FR)
			continue;
		if (port->cmstat & HBA_PxCMD_CR)
			continue;
		break;
	}
}

int ahci_find_cmdslot(volatile HBA_PORT* port) {
	uint32_t slots = (port->sata_act | port->ci);
	for (size_t i = 0; i < 32; i++) {
		if ((slots & 1) == 0)
			return i;
		slots >>= 1;
	}
	write_string("Couldn't find free command slot\n");
	return -1;
}

bool ahci_read_sectors(volatile HBA_PORT* port, uint32_t startl, uint32_t starth, uint32_t count, uint16_t* buf) {
	port->istat = (uint32_t) -1; // clear all pending interrupts
	int spin = 0; // spin timeout counter
	int slot = ahci_find_cmdslot(port);
	if (slot == -1) 
		return false;
	
	HBA_CMD_HEADER* cmdh = (HBA_CMD_HEADER*)port->cl_base;
	cmdh += slot;
	cmdh->cfis_len = sizeof(FIS_REG_H2D) / sizeof(uint32_t); //(since one entry is 32 bits)
	cmdh->w_dir = 0; // read from device to host
	cmdh->prdtl = (uint16_t)((count - 1) >> 4) + 1;

	HBA_CMD_TBL* cmdt = (HBA_CMD_TBL*)(cmdh->ctbl_desc_addr);
	memset(cmdt, 0, sizeof(HBA_CMD_TBL) + ((cmdh->prdtl - 1) * sizeof(HBA_PRDT_ENTRY)));
	
	int i = 0;
	for (i = 0; i < cmdh->prdtl - 1; i++) {
		cmdt->prdt_entry[i].data_base = (uint32_t)buf;
		cmdt->prdt_entry[i].data_base_u = 0;
		cmdt->prdt_entry[i].dbc = 8 * 1024 - 1; // 8K bytes (always minus one)
		cmdt->prdt_entry[i].i = 1;

		buf += 4 * 1024;
		count -= 16;
	}
	
	// last entry
	cmdt->prdt_entry[i].data_base = (uint32_t) buf;
	cmdt->prdt_entry[i].dbc = (count << 9) - 1;	// 512 bytes per sector
	cmdt->prdt_entry[i].i = 1;

	// Setup command
	FIS_REG_H2D* cmdfis = (FIS_REG_H2D*)(&cmdt->cfis);

	cmdfis->fis_type = FIS_TYPE_REG_H2D;
	cmdfis->comctrl = 1; // Command
	cmdfis->command = ATA_CMD_READ_DMA_EXT;

	cmdfis->lba0 = (uint8_t)(startl & 0xFF);
	cmdfis->lba1 = (uint8_t)((startl >> 8) & 0xFF);
	cmdfis->lba2 = (uint8_t)((startl >> 16) & 0xFF);
	cmdfis->device = 1 << 6; // lba mode
	cmdfis->lba3 = (uint8_t)((startl >> 24) & 0xFF);
	cmdfis->lba4 = (uint8_t)(starth & 0xFF);
	cmdfis->lba5 = (uint8_t)((starth >> 8) & 0xFF);

	cmdfis->count_low = count & 0xFF;
	cmdfis->count_high = (count >> 8) & 0xFF;

	while ((port->tfd & (ATA_DEV_BUSY | ATA_DEV_DRQ)) && spin < 100000) {
		spin++;
	}
	if (spin == 100000) {
		write_string("Port is hung\n");
		return false;
	}

	port->ci = 1 << slot; // issue the command
	
	while (1) {
		if ((port->ci & (1 << slot)) == 0)
			break;
		if (port->istat & HBA_PxIS_TFES) {
			write_string("Read error\n");
			return false;
		}
	}

	if (port->istat & HBA_PxIS_TFES) {
		write_string("Read error\n");
		return false;
	}

	return true;

}	
