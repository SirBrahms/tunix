#ifndef __GDT_HEADER__
#define __GDT_HEADER__

#include <stdint.h>

struct _GDT_entry {
	unsigned short limit_low;
	unsigned short base_low;
    	unsigned char base_mid;
    	unsigned char access;
    	unsigned char granularity;
    	unsigned char base_high;
} __attribute__((packed));
typedef struct _GDT_entry GDT_entry;

struct _gdtr {
	unsigned short limit;
	unsigned int base;
} __attribute__((packed));
typedef struct _gdtr GDTR;

GDT_entry GDT[3];
GDTR gp;

//GDT* gdt_init();
void entry_init(int num, uint32_t limit, uint32_t base, uint8_t access, uint8_t flags); // initialises one gdt_entry
void gdt_init();
extern void load_GDT(); // loads the GDTR! (defined in the GDTR struct)

#endif
