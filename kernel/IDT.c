#include "IDT.h"
#include "isrs/ISR.h"

void idt_entry_init(int num, uint32_t function_offset, uint16_t seg, uint8_t flags) {
	IDT[num].offset_low = function_offset & 0xFFFF;
	IDT[num].offset_high = (function_offset >> 16) & 0xFFFF;
	
	IDT[num].selector = seg;
	IDT[num].zero = 0;
	IDT[num].type_attributes = flags;
}

void idt_init() {
	// initialise every single entry here...
	idt_entry_init(0, (uint32_t)&isr_nop, csegs(1, 0, 0), 0x8E); // just a no-op
	idt_entry_init(0x80, (uint32_t)&isr_syscall_w, csegs(1, 0, 0), 0x8E); // syscall
	
	iptr.limit = sizeof(IDT) - 1;
	iptr.base = (uint32_t)IDT;

	load_IDT(); // load the idt 
}
