#ifndef __VGA_HEADER__
#define __VGA_HEADER__
#include <stddef.h>
#include <stdint.h>

enum VGA_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

static const size_t VGA_width = 80;
static const size_t VGA_height = 20;

inline uint8_t VGA_entry_color(enum VGA_color fg, enum VGA_color bg) {
	return fg | bg << 4;
}
inline uint16_t VGA_entry(unsigned char uc, uint8_t color) {
	return (uint16_t)uc | (uint16_t)color << 8;
}

#endif
