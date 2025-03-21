#include "include/GDT.h"
#include "include/TSS.h"


// XXX: doesn't work
#if 1 == 0 // exclude this part of the code
GDT gdt_init(GDT** GDT_tbl) {
	// GDT_tbl[0] . Null descriptor

	/* Kernel code segment */
	GDT_tbl[1].limit_low = 0;
	GDT_tbl[1].base_low = 0x00400000;
	GDT_tbl[1].accessed = 1;
	GDT_tbl[1].read_write = 0;
	GDT_tbl[1].dc = 0;
	GDT_tbl[1].executable = 1;
	GDT_tbl[1].descriptor = 1;
	GDT_tbl[1].dpl = 0;
	GDT_tbl[1].present = 1;
	GDT_tbl[1].limit_high = 0;
	GDT_tbl[1].long_mode = 0;
	GDT_tbl[1].db = 1;
	GDT_tbl[1].granular = 1;
	GDT_tbl[1].base_high = 0;

	/* Kernel data segment */
	GDT_tbl[2].limit_low = 0b1111111111111111;
	GDT_tbl[2].base_low = 0x00800000;
	GDT_tbl[2].accessed = 1;
	GDT_tbl[2].read_write = 0;
	GDT_tbl[2].dc = 0;
	GDT_tbl[2].executable = 0;
	GDT_tbl[2].descriptor = 1;
	GDT_tbl[2].dpl = 0;
	GDT_tbl[2].present = 1;
	GDT_tbl[2].limit_high = 0b1111;
	GDT_tbl[2].long_mode = 0;
	GDT_tbl[2].db = 1;
	GDT_tbl[2].granular = 1;
	GDT_tbl[2].base_high = 0;

	/* Task State Segment */

	GDT_tbl[3].limit_low = (sizeof(TSS_segment) - 1) & 0xFFFF;
	GDT_tbl[3].base_low = (uint32_t)&TSS_segment & 0xFFFFFF;
	GDT_tbl[3].type = 0x9;
	GDT_tbl[3].descriptor = 0;
	GDT_tbl[3].dpl = 0;
	GDT_tbl[3].present = 1;
	GDT_tbl[3].limit_high = (sizeof(TSS_segment) - 1) >> 16;
	GDT_tbl[3].long_mode = 0;
	GDT_tbl[3].db = 0;
	GDT_tbl[3].granular = 0;
	GDT_tbl[3].base_high = (uint32_t)&TSS_segment >> 24; 	

	return &GDT_tbl;
}
#endif

void entry_init(int num, uint32_t limit, uint32_t base, uint8_t access, uint8_t flags) {
	GDT[num].base_low = base & 0xFFFF;
	GDT[num].base_mid = (base >> 16) & 0xFF;
	GDT[num].base_high = (base >> 24) & 0xFF;

	GDT[num].limit_low = (limit & 0xFFFF);
	GDT[num].granularity = (limit >> 16) & 0x0F;

	GDT[num].granularity |= (flags & 0xF0);
	GDT[num].access = access;
}

void gdt_init() {
	// Set GDTR struct
	gp.limit = sizeof(GDT) - 1;
	gp.base = (unsigned int)&GDT;

	// create entries
	entry_init(0, 0, 0, 0, 0); // Null descriptor
	entry_init(1, 0x000FFFFF, 0x00200000, 0x9A, 0xCF); // Kernel code
	entry_init(2, 0x000FFFFF, 0x00200000, 0x92, 0xCF); // Kernel data
	
	load_GDT();
}
