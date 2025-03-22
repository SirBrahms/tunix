#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include "include/tty.h"
#include "IDT.h"
#include <string.h>
#include <stdlib.h>
#include "fs/VFS.h"
#include "drvs/PCI.h"

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
	
	pci_find_ahci();
	
	return;
}
