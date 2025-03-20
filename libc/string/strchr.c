#include <string.h>

char* strchr(const char* s, char c) {
	size_t i = 0;
	while (s[i]) {
		if (s[i] == c)
			return &s[i];
		i++;
	}

	return NULL;
}
