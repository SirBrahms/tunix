#include <stdlib.h>
#ifdef __is_libk
#include "memmgr.h"
#endif

void free(void* ptr) {
	#ifdef __is_libk
	heap_free(__kernel_heap, ptr);
	#else
	#endif
} 
