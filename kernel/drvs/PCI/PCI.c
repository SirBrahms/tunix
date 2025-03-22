#include "drvs/PCI.h"
#include <sys/io.h>
#include <stdlib.h>
#include "tty.h"

uint32_t pci_get_addr(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset) {
	uint32_t lbus = (uint32_t)bus;
	uint32_t lslot = (uint32_t)slot;
	uint32_t lfunc = (uint32_t)func;
	
	return (uint32_t)((lbus << 16) | (lslot << 11) | (lfunc << 8) | 
		(offset & 0xFC) | ((uint32_t)0x80000000));
}

uint16_t pci_read_word(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset) {
	uint32_t address = pci_get_addr(bus, slot, func, offset);
	
	// request the desired address
	outl(address, PCI_CONFIG_ADDR);

	// read PCI config at that address and offset and return lower 16 bits
	return (uint16_t)(inl(PCI_CONFIG_DATA) >> ((offset & 2) * 2) & 0xFFFF);
}

uint8_t pci_read_byte(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset) {
	outl(pci_get_addr(bus, slot, func, offset), PCI_CONFIG_ADDR);
	uint32_t rval = inl(PCI_CONFIG_DATA);

    	return (uint8_t)((rval >> (8 * (offset & 3))) & 0xFF);
}

uint32_t pci_read_dw(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset) {
	outl(pci_get_addr(bus, slot, func, offset), PCI_CONFIG_ADDR);

	return inl(PCI_CONFIG_DATA);
}


// check if given device exists - if yes, set rval[func] = 1
// 				- if no, return 0
uint8_t pci_valid_dev(uint8_t bus, uint8_t dev) {
	uint8_t func = 0;
	uint8_t rval = 0;

	uint16_t vendor_ID = pci_read_word(bus, dev, func, 0);
	if (vendor_ID == 0xFFFF) return 0; // no vendors with this id -> dev nonexistant
	rval |= 1 << 0; // set bit 0 -> function 0 exists
	
	uint8_t header_type = pci_read_byte(bus, dev, func, 0xE);
	if ((header_type & 0x80) != 0) { // check if the device is multifunc
		for (func = 1; func < 8; func++) {
			vendor_ID = pci_read_word(bus, dev, func, 0);
			if (vendor_ID != 0xFFFF) rval |= 1 << func; // set rval[func]
		}
	}

	return rval;
}

// find the system AHCI controller and return location of memory mapped registers
uint32_t pci_find_ahci() {
	for (uint8_t bus = 0; bus < 255; bus++) {
		for (uint8_t dev = 0; dev < 32; dev++) {
			uint8_t devinfo = pci_valid_dev(bus, dev);

			if (devinfo > 0) {
				// valid device found - check for AHCI
				uint8_t header_type = pci_read_byte(bus, dev, 0, 0xE);
				uint8_t clcode = pci_read_byte(bus, dev, 0, 0xB);
				uint8_t subclass = pci_read_byte(bus, dev, 0, 0xA);
				if (header_type == 0 && clcode == 1 && subclass == 6) {
					// correct type, class, subclass
					return pci_read_dw(bus, dev, 0, 0x24); // read BAR5 - relevant pointer
				}
			}
		}
	}
	abort();
}
