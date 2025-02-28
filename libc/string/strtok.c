#include <string.h>
#include <stdbool.h>

// FIXME: Undefined behavior, need a malloc impl...
char* laststr;

char* strtok(char* str, const char* delim) {
	size_t i = 0;
	size_t j = 0;
	size_t length = strlen(str);
	size_t delim_len = strlen(delim);
	bool found = false;

	if (str == NULL)
		str = laststr;
	
	while (str[i] && !found)
	{
		if (str[i] == delim[0]) {
			for (j = 0; j < delim_len; j++) {
				if (str[i] != delim[j] || str[i] == '\0')
					break;
				else
					i++;
			}
			found = true;
		}
		else 
			i++;
	}

	char target[length + 1];
	memcpy(target, str, i);
	target[i] = '\0';
	return target;
}
