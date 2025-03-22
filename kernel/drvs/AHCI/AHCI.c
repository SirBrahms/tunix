#include "drvs/AHCI.h"
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
			}
			else if (disktype == AHCI_DEV_SEMB) {
				write_string("SEMB drive found at port ");
				putchar((char)i + 48);
				putchar('\n');
			}
			else if (disktype == AHCI_DEV_PM) {
				write_string("PM drive found at port ");
				putchar((char)i + 48);
				putchar('\n');
			}
			else if (disktype == AHCI_DEV_SATAPI) {
				write_string("SATAPI drive found at port ");
				putchar((char)i + 48);
				putchar('\n');
			}
			else {
				write_string("No drive found at port ");
				putchar((char)i + 48);
				putchar('\n');
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
