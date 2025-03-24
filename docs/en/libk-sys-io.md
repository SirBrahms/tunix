# 01.04 - sys/io.h
The io header implements functions to read and write to device ports using the ```in[size]``` instruction.
## Members
### unsigned char inb(unsigned short int)
```c
static inline unsigned char inb(unsigned short int port)
```
- Purpose: Reads a byte from the specified port
- Parameters:
    - ```unsigned short int port```: The Port
- Return Value: The read byte
### unsigned int inl(unsigned short int)
```c
static inline unsigned int inl(unsigned short int port)
```
- Purpose: Reads a long from the specified port
- Parameters:
    - ```unsigned short int port```: The Port
- Return Value: The read long
### void outb(unsigned char, unsigned short int)
```c
static inline void outb(unsigned char value, unsigned short int port) 
```
- Purpose: Writes a byte to the specified port
- Parameters:
    - ```unsigned char value```: The Value to write
    - ```unsigned short int port```: The Port
- Return Value: Void
### void outw(unsigned short int, unsigned short int)
```c
static inline void outw(unsigned char value, unsigned short int port) 
```
- Purpose: Writes a word to the specified port
- Parameters:
    - ```unsigned char value```: The Value to write
    - ```unsigned short int port```: The Port
- Return Value: Void
### void outl(unsigned int, unsigned short int)
```c
static inline void outl(unsigned char value, unsigned short int port) 
```
- Purpose: Writes a long to the specified port
- Parameters:
    - ```unsigned char value```: The Value to write
    - ```unsigned short int port```: The Port
- Return Value: Void