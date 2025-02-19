#include "include/vga.h"

inline static uint8_t VGA_entry_color(enum VGA_color fg, enum VGA_color bg) {
	return fg | bg << 4;
}

inline static uint16_t VGA_entry(unsigned char uc, uint8_t color) {
	return (uint16_t)uc | (uint16_t)color << 8;
}
