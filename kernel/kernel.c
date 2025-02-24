#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include "include/tty.h"

// Compile Time checks
#if defined(__linux__)
#error "Not using a cross compiler"
#endif

#if !defined(__i386__)
#error "Not compiling to i386"
#endif

void kernel_main(void) {
	terminal_init();
	write_string("Hello World!");
	return;
}
