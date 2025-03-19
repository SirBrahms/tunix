#include "PMM.h"

uintptr_t get_address(unsigned int row, unsigned int col) {
	return (uintptr_t)((BITS_PER_ROW * row) + col);
}

unsigned int get_bit_number(uintptr_t address) {
	return (unsigned int)(address / PAGE_SIZE);
}

int is_taken(unsigned int bit_number) {
	return &bitmap[bit_number] == P_TAKEN
}

void use_page(unsigned int bit_number) {
	&bitmap[bit_number] = P_TAKEN;
}

void free_page(unsigned int bit_number) {
	&bitmap[bit_number] = P_FREE;
}
