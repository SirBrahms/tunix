#ifndef __TTY_HEADER__
#define __TTY_HEADER__

#include <stddef.h>
#include <stdint.h>
#include <sys/io.h>

void terminal_init(void);
void clear_terminal(void);
void clear_current_line(void);
void set_terminal_color(uint8_t color);
void put_terminal_entry_at(char c, uint8_t color, size_t x, size_t y);
void putchar(char c);
void write_tty(const char* str, size_t length);
void write_string(const char* str);

#ifdef __WITH_SERIAL

int serial_init();
int serial_received();
char read_serial(); // blocking
int serial_rts();
void write_serial(char c);

#endif // __WITH_SERIAL
#endif // __TTY_HEADER__
