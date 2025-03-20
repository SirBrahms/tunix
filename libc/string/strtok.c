#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "tty.h"

static char* laststr;

char* strtok(char* s, const char* delim) {
	if (s == NULL)
		s = laststr;
	else
		laststr = s;

	while (*laststr != '\0' && strchr(delim, *laststr) != NULL) {
        	laststr++;
    	}

	if (*laststr == '\0') {
		return NULL;
	}

	char* token = laststr;

	while (*laststr != '\0'  && strchr(delim, *laststr) == NULL) {
        	laststr++;
    	}

	if (*laststr != '\0') {
        	*laststr = '\0'; // Null-terminate the token
        	laststr++; // Move to the next character
    	} 
	else {
        	laststr = NULL; // End of string reached
    	}
    
    	return token;
}
