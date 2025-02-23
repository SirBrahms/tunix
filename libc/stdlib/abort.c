#include <stdlib.h>
__attribute__((__noreturn__))
void abort(void) {
	#if defined(__is_libk)
	// kernel panic
	asm volatile("hlt");
	#endif
	while (1) {}
	__builtin_unreachable(); // optimisation
}
