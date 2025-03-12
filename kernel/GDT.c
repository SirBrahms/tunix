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

void entry_init(GDT_entry* entry, uint32_t limit, uint32_t base, uint8_t access, uint8_t flags) {
	
	
	entry->limit_low = limit & 0xFFFF;
	entry->base_low = base & 0xFFFFFF;
	entry->accessed = access >> 7;
	entry->read_write = access >> 6 & 0b1;
	entry->dc = access >> 5 & 0b1;
	entry->executable = access >> 4 & 0b1;
	entry->descriptor = access >> 3 & 0b1;
	entry->dpl = access >> 2 & 0b11;
	entry->present = access & 0b1;
}


