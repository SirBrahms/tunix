# 01.01 - TTY.h
This header is responsible for writing character data to the device's video memory. It also handles serial i/o.
## Members
### void terminal_init(void)
```c
void terminal_init(void)
```
- Purpose: Initialises the Terminal
- Parameters: None
- Return Value: Void
### void clear_terminal(void)
```c
void clear_terminal(void)
```
- Purpose: Clears the terminal
- Parameters: None
- Return Value: Void
### void clear_current_line(void)
```c
void clear_current_line(void)
```
- Purpose: Clears the current line in the terminal
- Parameters: None
- Return Value: Void
### void set_terminal_color(uint8_t)
```c
void set_terminal_color(uint8_t color)
```
- Purpose: Sets the terminal Color
- Parameters: 
    - ```uint8_t color```: A valid VGA Color
- Return Value: Void
### void put_terminal_entry_at(char, uint8_t, size_t, size_t)
```c
void put_terminal_entry_at(char c, uint8_t color, size_t x, size_t y)
```
- Purpose: Puts a character with a given color at the given coordinates
- Parameters: 
    - ```char c```: The character to write
    - ```uint8_t color```: A valid VGA Color
    - ```size_t x```: The x-coordinate
    - ```size_t y```: The y-coordinate
- Return Value: Void
### void putchar(char)
```c
void putchar(char c)
```
- Purpose: Puts a character with the current terminal color at the next open position
- Parameters: 
    - ```char c```: The character to write
- Return Value: Void
### void write_tty(const char* str, size_t length)
```c
void write_tty(const char* str, size_t length)
```
- Purpose: Writes a string of the given length at the next open position
- Parameters: 
    - ```const char* c```: The string to write
    - ````size_t length```: The length of the string
- Return Value: Void
### void write_string(const char* str)
```c
void write_string(const char* str)
```
- Purpose: Writes a zero-terminated string at the next open position
- Parameters: 
    - ```const char* c```: The string to write
- Return Value: Void
### int serial_init()
```c
int serial_init()
```
- Purpose: Initialises the COM0 Port
- Parameters: None
- Return Value: 0 if Successful, 1 if Faulty
### int serial_received()
```c
int serial_received()
```
- Purpose: Checks if the Serial Port has new Data
- Parameters: None
- Return Value: 0 if no Data, 1 if Data is available
### char read_serial()
```c
char read_serial()
```
- Purpose: Reads a character from COM0
- Parameters: None
- Return Value: The read character
### int serial_rts()
```c
int serial_rts()
```
- Purpose: Checks if the COM device is ready to send
- Paramters: None
- Return Value: 0 if not ready, 1 if ready
### void write_serial(char)
```c
void write_serial(char c)
```
- Purpose: Writes a character to the Serial Port
- Parameters:
    - ```char c```: The character to be written
- Return Value: void