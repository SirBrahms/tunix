#ifndef __DRVS_PCI_HEADER__
#define __DRVS_PCI_HEADER__

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define PCI_CONFIG_ADDR 0xCF8
#define PCI_CONFIG_DATA 0xCFC

uint32_t pci_get_addr(uint8_t, uint8_t, uint8_t, uint8_t);

uint16_t pci_read_word(uint8_t, uint8_t, uint8_t, uint8_t);
uint8_t pci_read_byte(uint8_t, uint8_t, uint8_t, uint8_t);
uint32_t pci_read_dw(uint8_t, uint8_t, uint8_t, uint8_t);
uint8_t pci_valid_dev(uint8_t, uint8_t);
uint32_t pci_find_ahci();

#endif
