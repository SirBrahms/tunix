#include "include/tty.h"
#include "include/vga.h"
#include <string.h>

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void terminal_init(void) {
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = VGA_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*)0xB8000; // location of the buffer

	for (size_t y = 0; y < VGA_height; y++) {
		for (size_t x = 0; x < VGA_width; x++) {
			const size_t index = y * VGA_width + x;
			terminal_buffer[index] = VGA_entry(' ', terminal_color); // clearing
		}
	}
}

void clear_terminal(void) {
	for (size_t y = 0; y < VGA_height; y++) {
		for (size_t x = 0; x < VGA_width; x++) {
			const size_t index = y * VGA_width + x;
			terminal_buffer[index] = VGA_entry(' ', terminal_color); // clearing
		}
	}
}

void clear_current_line(void) {
	for (size_t x = 0; x < VGA_width; x++) {
		const size_t index = terminal_column * VGA_width + x;

		terminal_buffer[index] = VGA_entry(' ', terminal_color);
	}
}

void set_terminal_color(uint8_t color) {
	terminal_color = color;	
}

void put_terminal_entry_at(char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_width + x;
	terminal_buffer[index] = VGA_entry(c, color);
}

void putchar(char c) {
	if (c ==  '\r')
		return;
	if (c == '\n') {
		terminal_column = 0;

		if (terminal_row + 1 == VGA_height) {
			for (size_t y = 0; y < VGA_height; y++) {
				for (size_t x = 0; x < VGA_width; x++) {
					const size_t old_index = y * VGA_width + x;
					const size_t new_index = (y + 1) * VGA_width + x;

					terminal_buffer[old_index] = terminal_buffer[new_index];
				}
			}
		}
		else {
			terminal_row++;
		}
		return;
	}
	
	put_terminal_entry_at(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_width) {
		terminal_column = 0;

		if (++terminal_row == VGA_height) {
			terminal_row = 0;
		}
	}
}

void write_tty(const char* str, size_t length) {
	for (size_t i = 0; i < length; i++) 
		putchar(str[i]);
}

void write_string(const char* str) {
	write_tty(str, strlen(str));
}

#ifdef __WITH_SERIAL

const unsigned short int COM1 = 1016; 

int serial_init() {
	outb(0x00, COM1 + 1); // disable interrupts
	outb(0x80, COM1 + 3); // enable DLAB to set baud rate divisor
	outb(0x03, COM1 + 0); // divisor = 0x03 (low byte)
	outb(0x00, COM1 + 1); //                (high byte)
	outb(0x03, COM1 + 3); // 8 bit, no parity, one stop bit	
	outb(0xC7, COM1 + 2); // Enable input queue + clear input queue
	outb(0x0B, COM1 + 4); // enable IRQs
	outb(0x1E, COM1 + 4); // set in loopback mode (to test if it's there)
	outb(0xAE, COM1 + 0); // test by sending 0xAE

	if (inb(COM1 + 0) != 0xAE) {
		return 1; // faulty, did not loopback
	}

	outb(0x0F, COM1 + 4); // put it in operation mode
	return 0;
}

int serial_received() {
	return inb(COM1 + 5) & 1;
}

char read_serial() {
	while (serial_received() == 0);

	return inb(COM1);
}

int serial_rts() {
	return inb(COM1 + 5) & 0x20;
}

void write_serial(char c) {
	while (serial_rts() == 0);

	outb(c, COM1);	
}

#endif
