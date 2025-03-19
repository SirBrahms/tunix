#include "IDT.h"

void idt_entry_init(int num, uint32_t function_offset, uint16_t seg, uint8_t flags) {
	IDT[num].offset_low = function_offset & 0xFFFF;
	IDT[num].offset_high = (function_offset >> 16) & 0xFFFF;
	
	IDT[num].selector = seg;
	IDT[num].zero = 0;
	IDT[num].type_attributes = flags;
}

inline uint16_t csegs(uint16_t index, uint8_t table, uint8_t rpl) {
	return ((index & 0x1FF) << 3) + ((table & 0b1) << 2) + (rpl & 0b11);
}

inline uint8_t ciflags(uint8_t gt, uint8_t dpl) {
	return (1 << 7) + ((dpl & 0b11) << 5) + (gt & 0b1111);
}

void idt_init() {
	// initialise every single entry here...
}
