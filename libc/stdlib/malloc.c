#include <stdlib.h>
#if defined(__is_libk)
#endif

void* malloc(size_t size) {
#ifdef __is_libk
#else

#endif
}
