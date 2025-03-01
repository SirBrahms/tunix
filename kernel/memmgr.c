#include "include/memmgr.h"

HEAP* __kernel_heap;

void heap_init(HEAP* heap) {
	heap->fblock = 0;
	__kernel_heap = heap;
}

int add_block(HEAP* heap, uintptr_t addr, uint32_t size, uint32_t bsize) {
	HBLOCK* b;
	uint32_t ratio;
	uint8_t* bitmap;


	b = (HBLOCK*)addr; // location of the block
	b->size = size - sizeof(HBLOCK); // Size = passed size, but respect size of a block
	b->bsize = size; // just the block size
	b->next = heap->fblock; // gets added in front of the first block
	heap->fblock = b;

	ratio = b->size / b->bsize;
	bitmap = (uint8_t*)&b[1]; // & = pointer to!
	
	// clear bitmap
	for (size_t index = 0; index < ratio; index++) {
		bitmap[index] = 0;
	}

	// reserve space for bitmap
	ratio = (ratio / bsize) * bsize < ratio ? ratio / bsize + 1 : ratio / bsize;
	for (size_t index = 0; index < ratio; index++) {
		bitmap[index] = 5;
	}

	b->lfb = ratio - 1; // store the size of the header for later
	b->used = ratio; 

	return 1;
}

static uint8_t get_NID(uint8_t a, uint8_t b) {
	uint8_t c;
	for (c = a + 1; c == b || c == 0; c++);
	return c;
}

void* heap_alloc(HEAP* heap, size_t size) {
	HBLOCK* b;
	uint8_t* bitmap;
	size_t x;

	// go through all the blocks
	for (b = heap->fblock; b; b = b->next) {
		// check if there's enough space
		if (b->size - (b->used * b->bsize) >= size) {
			uint32_t ratio = b->size / b->bsize;
			uint32_t bneed = (ratio / b->bsize) * b->bsize < ratio ? ratio / b->bsize + 1 : ratio / b->bsize;
			bitmap = (uint8_t*)&b[1];
			
			for (x = (b->lfb + 1 >= ratio ? 0 : b->lfb + 1); x < b->lfb + 1; x++) {
				if (x > ratio)
					x = 0;

				if (bitmap[0] == 0) {
					// count free blocks
					size_t frblocks;
					for (frblocks = 0; bitmap[x + frblocks] == 0 && frblocks < bneed && (x + frblocks) < bneed; frblocks++);
					
					// have enough -> go allocate, allocator boy
					if (frblocks == bneed) {
						uint8_t nid = get_NID(bitmap[x - 1], bitmap[x + frblocks]);

						// set the id in the bitmap, reserving the block
						for (size_t z = 0; z < frblocks; z++)
							bitmap[x + z] = nid;

						b->lfb = (x + bneed) - 2; // optimisation
						b->used += frblocks; // number of used blocks here

						return (void*)(x * b->size + (uintptr_t)&b[1]);
					}
					
					x += (frblocks - 1); // incremet x by the amount of free blocks found
				}
			}
		}
	}
	
	return 0; // nullptr TODO: check this in malloc impl.
}

void heap_free(HEAP* heap, void* ptr) {
	HBLOCK* b;
	uint8_t* bitmap;

	for (b = heap->fblock; b; b = b->next) {
		if ((uintptr_t)ptr > (uintptr_t)b && (uintptr_t)ptr < (uintptr_t)b + sizeof(HBLOCK) + b->size) {
			// this is our block
			uintptr_t ptroff = (uintptr_t)ptr - (uintptr_t)&bitmap[1]; // get offset from the block
			uint32_t bi = ptroff / b->size; // block offset in bitmap
			bitmap = (uint8_t*)&b[1];
			uint32_t id = bitmap[bi]; // mark as free
			uint32_t max = b->size / b->bsize;
			
			uint32_t x;
			for (x = bi; x < max && bitmap[x] == id; x++)
				bitmap[x] = 0;

			b->used -= x - bi;
			return;
		}
	}
	// TODO: set error here
	return;
}
