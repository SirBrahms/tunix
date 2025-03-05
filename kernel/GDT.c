#include "include/GDT.h"
#include "include/TSS.h"

GDT GDT_table[4] = { 0 };

void gdt_init() {
	// GDT_table[0] -> Null descriptor
	
	/* Kernel code segment */
	GDT_table[1].limit_low = 0;
	GDT_table[1].base_low = 0x00400000;
	GDT_table[1].accessed = 1;
	GDT_table[1].read_write = 0;
	GDT_table[1].dc = 0;
	GDT_table[1].executable = 1;
	GDT_table[1].descriptor = 1;
	GDT_table[1].dpl = 0;
	GDT_table[1].present = 1;
	GDT_table[1].limit_high = 0;
	GDT_table[1].long_mode = 0;
	GDT_table[1].db = 1;
	GDT_table[1].granular = 1;
	GDT_table[1].base_high = 0;

	/* Kernel data segment */
	GDT_table[2].limit_low = 0b1111111111111111;
	GDT_table[2].base_low = 0x00800000;
	GDT_table[2].accessed = 1;
	GDT_table[2].read_write = 0;
	GDT_table[2].dc = 0;
	GDT_table[2].executable = 0;
	GDT_table[2].descriptor = 1;
	GDT_table[2].dpl = 0;
	GDT_table[2].present = 1;
	GDT_table[2].limit_high = 0b1111;
	GDT_table[2].long_mode = 0;
	GDT_table[2].db = 1;
	GDT_table[2].granular = 1;
	GDT_table[2].base_high = 0;

	/* Task State Segment */
}
