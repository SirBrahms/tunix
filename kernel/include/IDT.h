#ifndef __IDT_HEADER__
#define __IDT_HEADER__

#include <stdint.h>
#include <stddef.h>

struct _IDT_entry {
	uint16_t offset_low;        	// offset bits 0..15
   	uint16_t selector;        	// a code segment selector in GDT or LDT
   	uint8_t  zero;            	// unused, set to 0
   	uint8_t  type_attributes; 	// gate type, dpl, and p fields
   	uint16_t offset_high;        	// offset bits 16..31
} __attribute__((packed));
typedef struct _IDT_entry IDT_entry;

struct _idtr {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed));
typedef struct _idtr IDTR;

void idt_entry_init(int num, uint32_t function_offset, uint16_t seg, uint8_t flags);
void idt_init();
extern void load_IDT();

#endif
