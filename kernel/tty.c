#include "include/tty.h"
#include "include/vga.h"

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
			terminal_buffer[index] = vga_entry(' ', terminal_color); // clearing
		}
	}
}

void clear_terminal(void) {
	for (size_t y = 0; y < VGA_height; y++) {
		for (size_t x = 0; x < VGA_width; x++) {
			const size_t index = y * VGA_width + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color); // clearing
		}
}

void set_terminal_color(uint8_t color) {
	terminal_color = color	
}

void put_terminal_entry_at(char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_width + x;
	terminal_buffer[index] = vga_entry(c, color)
}

void putchar(char c) {
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

void write(const char* str, size_t length) {
	for (size_t i = 0; i < length; i++) 
		putchar(str[i])
}

void write_string(const char* str) {
	write(str, strlen(str));
}
