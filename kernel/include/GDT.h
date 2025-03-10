#ifndef __GDT_HEADER__
#define __GDT_HEADER__

#include <stdint.h>

struct _GDT {
	unsigned int limit_low	: 16;
	unsigned int base_low 	: 24;
	/* Access byte */
	union {
		struct { // Access byte for hardware segments
			unsigned int accessed	: 1;
			unsigned int read_write	: 1;
			unsigned int dc		: 1;
			unsigned int executable : 1;

		};
		
		unsigned int type	: 4; // Software segments
	};
	unsigned int descriptor : 1;
	unsigned int dpl	: 2;
	unsigned int present	: 1;
	/* End Access byte */
	unsigned int limit_high : 4;
	/* Flags */
	//unsigned int _reserved	: 1;
	unsigned int long_mode	: 1;
	unsigned int db		: 1;
	unsigned int granular	: 1;
	/* End Flags */
	unsigned int base_high	: 8;

} __attribute__((packed));
typedef struct _GDT GDT;

void gdt_init();
void _load_gdt(uint16_t limit, uint32_t base);

#endif
