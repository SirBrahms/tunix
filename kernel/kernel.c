#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include "include/tty.h"
#include "IDT.h"
#include <string.h>
#include <stdlib.h>
#include "fs/VFS.h"
#include "drvs/PCI.h"
#include "drvs/AHCI.h"

// Compile Time checks
#if defined(__linux__)
#error "Not using a cross compiler"
#endif

#if !defined(__i386__)
#error "Not compiling to i386"
#endif

void kernel_main(void) {
	idt_init();
	vfs_init();

	terminal_init();
	if (serial_init() == 1) {
		abort();
	}

	volatile HBA_MEM* abar = (volatile HBA_MEM*)pci_find_ahci();
	ahci_probe_port(abar);
	write_string("got past it");	
	
	uint16_t* buf = NULL;

	ahci_read_sectors(master_dev, 0, 0, 2, buf);
	write_string((char*)buf);
	ahci_write_sectors(master_dev, 0, 0, 1, (uint16_t*)"A");
	ahci_read_sectors(master_dev, 0, 0, 2, buf);
	write_string((char*)buf);
	return;
}
