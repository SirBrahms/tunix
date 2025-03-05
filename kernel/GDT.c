#include "include/GDT.h"

GDT GDT_table[4];

void gdt_init() {
	table[0] = 0; // Null descriptor
	
	/* Kernel code segment */
	table[1].limit_low = 0;
	table[1].base_low = 0x00400000;
	table[1].accessed = 1;
	table[1].read_write = 0;
	table[1].dc = 0;
	table[1].executable = 1;
	table[1].descriptor = 1;
	table[1].dpl = 0;
	table[1].present = 1;
	table[1].limit_high = 0;
	table[1].long_mode = 0;
	table[1].db = 1;
	table[1].granular = 1;
	table[1].base_high = 0;

	/* Kernel data segment */
	table[0].limit_low = 0; // XXX: Temp
}
