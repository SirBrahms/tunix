#ifndef __PMM_HEADER__
#define __PMM_HEADER__
// Physical memory manager

#include <stdint.h>
#include <stddef.h>

#define P_TAKEN 1
#define P_FREE 0
#define PAGE_SIZE 0x1000
#define BITS_PER_ROW 8 // uint8_t

uint8_t bitmap[8] = { 0 }; // One Page = 0x1000 bytes (1 bit = 1 Page)

uintptr_t get_address(unsigned int row, unsigned int col);
unsigned int get_bit_number(uintptr_t address);

int is_taken(unsigned int bit_number);
void use_page(unsigned int bit_number);
void free_page(unsigned int bit_number);



#endif
