#ifndef __STRING_HEADER
#define __STRING_HEADER

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif
int memcmp(const void*, const void*, size_t);
void* memcpy(void* __restrict, const void* __restrict, size_t);
void* memmove(void*, const void*, size_t);
void* memset(void*, int, size_t);
size_t strlen(const char*);

char* strtok(char* str, const char* delim);
char* strpbrk(char*, const char*);
size_t strspn(const char*, const char*);
char* strchr(const char*, char);
#ifdef __cplusplus
}
#endif

#endif
