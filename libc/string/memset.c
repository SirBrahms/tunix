#include <string.h>

void* memset(void* source, int value, size_t n) {
	unsigned char* buf = (unsigned char*)source;

	for (size_t i = 0; i < n; i++) {
		buf[i] = value;
	}

	return buf;
}
