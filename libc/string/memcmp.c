#include <string.h>

int memcmp(const void* p1, const void* p2, size_t size) {
	unsigned char* ptr1 = (unsigned char*)p1;
	unsigned char* ptr2 = (unsigned char*)p2;

	for (size_t i = 0; i < size; i++) {
		if (ptr1[i] > ptr2[i])
			return 1;
		if (ptr1[i] < ptr2[i])
			return -1;
	}
	return 0;
}
