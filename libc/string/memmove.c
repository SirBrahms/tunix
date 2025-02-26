#include <string.h>

void* memmove(void* dest, const void* src, size_t n) {
	unsigned char* destp = (unsigned char*)dest;
	unsigned char* srcp = (unsigned char*)src;
	
	if (destp < srcp) {
		for (size_t i = 0; i < n; i++)
			destp[i] = srcp[i];
	}
	else {
		for (size_t i = n; i != 0; i--) 
			destp[i - 1] = srcp[i - 1];
	}
	
	return destp;
}
