# 01.01 - string.h
The string.h header exposes important functions to work with memory areas and strings.
## Members
### int memcmp(const void*, const void*, size_t)
```c
int memcmp(const void* p1, const void* p2, size_t size)
```
- Purpose: Compares two areas of memory with a given size
- Parameters:
    - ```const void* p1```: The first area of memory
    - ```const void* p2```: The second area of memory
    - ```size_t size```: The amount of bytes to compare
- Return Value: 0 if the areas are equal, otherwise the sign of the difference
### void* memcpy(void* __restrict, const void* __restrict, size_t)
```c
void* memcpy(void* destp, const void* srcp, size_t n)
```
- Purpose: Copies one area of memory with a given size to another
- Parameters:
    - ```void* destp```: The destination pointer
    - ```const void* srcp```: The source pointer
    - ```size_t n```: The amount of bytes to copy
- Return Value: The pointer to the destination
### void* memmove(void*, const void*, size_t)
```c
void* memmove(void* dest, const void* src, size_t n)
```
- Purpose: Copies one area of memory with a given size to another. The areas can overlap
- Parameters:
    - ```void* dest```: The destination pointer
    - ```const void* src```: The source pointer
    - ```size_t n```: The amount of bytes to copy
- Return Value: The pointer to the destination
### void* memset(void*, int, size_t)
```c
void* memset(void* source, int value, size_t n)
```
- Purpose: Sets an area of memory of size n to a given value
- Parameters:
    - ```void* source```: The memory location
    - ```int value```: The value to write
    - ```size_t n```: The amount of bytes to write
- Return Value: The pointer to the source
### size_t strlen(const char*)
```c
size_t strlen(const char* str)
```
- Purpose: Gets the length of a NULL-Terminated String
- Parameters:
    - ```const char* str```: The string
- Return Value: The length of the string
### char* strtok(char*, const char*)
```c
char* strtok(char* s, const char* delim)
```
- Purpose: Tokenises the String with a given delimiter.
- Parameters:
    - ```char* s```: The string to tokenise
    - ```const char* delim```: The delimiter
- Return Value: The token
### char* strpbrk(char*, const char*)
```c
char* strpbrk(char* str, const char* allow)
```
- Purpose: Scans a string until any allowed byte is encountered.
- Parameters:
    - ```char* str```: The string to scan
    - ```const char* allow```: The allowed characters
- Return Value: A pointer to the first allowed byte
### size_t strspn(const char*, const char*)
```c
size_t strspn(const char* str, const char* allow)
```
- Purpose: Finds the maximum initial segment of a string that only consists of allowed characters.
- Parameters:
    - ```const char* str```: The string to scan
    - ```const char* allow```: The allowed characters
- Return Value: The length of the found segment
### char* strchr(const char*, char)
```c
char* strchr(const char* s, char c)
```
- Purpose: Finds the first instance of a given character in a string.
- Parameters:
    - ```const char* str```: The string to scan
    - ```char c```: The character to find
- Return Value: A pointer to the found character