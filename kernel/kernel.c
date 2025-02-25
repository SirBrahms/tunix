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
	if (serial_init() == 1) {
		return;
	}
	
	while (1) {
		putchar(read_serial());
	}

	return;
}
