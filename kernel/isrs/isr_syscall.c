#include "tty.h"

void isr_syscall(void) {
	write_string("Syscall!\n");
}
