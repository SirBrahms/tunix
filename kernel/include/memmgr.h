#ifndef __MEMMGR_HEADER
#define __MEMMGR_HEADER

#include <stdint.h>
#include <stddef.h>

typedef struct _HBLOCK{
	struct _HBLOCK* next;
	uint32_t used;
	uint32_t size;
	uint32_t bsize;
	uint32_t lfb;
} HBLOCK;

typedef struct {
	HBLOCK* fblock;
} HEAP;

extern HEAP* __kernel_heap;

void heap_init(HEAP*);
int add_block(HEAP*, uintptr_t, uint32_t, uint32_t);
void* heap_alloc(HEAP*, size_t);
void heap_free(HEAP*, void*);
static uint8_t get_NID(uint8_t, uint8_t);
#endif
