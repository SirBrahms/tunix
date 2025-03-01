#ifndef __STDLIB_HEADER
#define __STDLIB_HEADER

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif
__attribute__((__noreturn__))
void abort(void);

void free(void*);
void* malloc(size_t);
#ifdef __cplusplus
}
#endif

#endif
