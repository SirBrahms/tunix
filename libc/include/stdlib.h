#ifndef __STDLIB_HEADER
#define __STDLIB_HEADER

#ifdef __cplusplus
extern "C" {
#endif
__attribute__((__noreturn__))
void abort(void);
void* malloc(size_t);
void free(void*);

#ifdef __cplusplus
}
#endif

#endif
