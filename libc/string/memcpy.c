#include <string.h>

void* memcpy(void* destp, const void* srcp, size_t n) {
	unsigned char* dest = (unsigned char*)destp;
	unsigned char* src = (unsigned char*)srcp;

	for (size_t i = 0; i < n; i++) {
		dest[i] = src[i];
	}

	return dest;
}
