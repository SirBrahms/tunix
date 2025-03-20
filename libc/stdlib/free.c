#include <stdlib.h>
#ifdef __is_libk
#endif

void free(void* ptr) {
	#ifdef __is_libk
	#else
	#endif
} 
