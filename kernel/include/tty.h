#ifndef __TTY_HEADER__
#define __TTY_HEADER__

#include <stddef.h>
#include <stdint.h>

void terminal_init(void);
void clear_terminal(void);
void set_terminal_color(uint8_t color);
void put_terminal_entry_at(char c, uint8_t color, size_t x, size_t y);
void putchar(char c);
void write(const char* str, size_t length);
void write_string(const char* str);

#endif
