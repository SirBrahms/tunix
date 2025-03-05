#ifndef __STDLIB_HEADER
#define __STDLIB_HEADER

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _MDN {
	struct _MDN* next;
	uintptr_t offset;
	uint32_t size;
	uint32_t block_size;
} MDN;


__attribute__((__noreturn__))
void abort(void);

void free(void*);
void* malloc(size_t);
#ifdef __cplusplus
}
#endif

#endif
