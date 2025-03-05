#include <stdlib.h>
#ifdef __is_libk
#include "tty.h"
#endif

__attribute__((__noreturn__))
void abort(void) {
	#if defined(__is_libk)
	// kernel panic
	write_string("aborted!");
	asm volatile("hlt");
	#endif
	while (1) {}
	__builtin_unreachable(); // optimisation
}
