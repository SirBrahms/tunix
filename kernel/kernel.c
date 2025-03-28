#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include "include/tty.h"
#include "IDT.h"
#include <string.h>
#include <stdlib.h>
#include "fs/FAT32.h"
#include "drvs/PCI.h"
#include "drvs/AHCI.h"
#include "KIS.h"

// Compile Time checks
#if defined(__linux__)
#error "Not using a cross compiler"
#endif

#if !defined(__i386__)
#error "Not compiling to i386"
#endif

void kernel_main(void) {
	idt_init();
	volatile HBA_MEM* abar = (volatile HBA_MEM*)pci_find_ahci();
	ahci_probe_port(abar);
	fat32_init();

	terminal_init();
	if (serial_init() == 1) {
		abort();
	}


	//write_string("test:\n");
	
	// Call Kernel Internal Shell
	KIS();
	return;
}
