#include <string.h>

size_t strspn(const char* str, const char* allow) {
  	size_t count = 0;

  	for (const char* s = str; *s != '\0'; ++s)
    	{
      		for (const char* a = allow; *a != '\0'; ++a) {
			if (*s == *a)
	  			break;
      			if (*a == '\0')
				return count;
      			else
				++count;
		}
    	}

  	return count;	
}
