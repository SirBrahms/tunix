#include <stdlib.h>
#if defined(__is_libk)
#include "memmgr.h"
#endif

void* malloc(size_t size) {
#ifdef __is_libk
	void* ret = heap_alloc(__kernel_heap, size);
	if (ret != NULL)
		return ret;
	
	add_block(__kernel_heap, (uintptr_t)0x100000, 0x100000, 16);
	ret = heap_alloc(__kernel_heap, size);
	return ret;
#else

#endif
}
