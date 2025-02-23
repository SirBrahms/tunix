#include <string.h>

size_t strlen(char* str) {
	size_t size;

	while(str[size]) {
		size++;
	}
	return size;
}
