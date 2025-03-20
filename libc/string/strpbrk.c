#include <string.h>

char* strpbrk(char* str, const char* allow) {
	while (*str != '\0')
    	{
      		const char *a = allow;
      		while (*a != '\0')
			if (*a++ == *str)
	  			return (char *) str;
      		++str;
    	}

	return NULL;
}
