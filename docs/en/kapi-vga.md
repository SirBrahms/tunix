# 02.02 - VGA.h
This header is responsible for creating VGA Text-Mode compatible characters.
## Members
### enum VGA_color
```c
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
```
- Purpose: Saves all possible VGA color values
### size_t VGA_width
```c
static const size_t VGA_width = 80;
```
- Purpose: Saves the maximum Width for the VGA Character Buffer
### size_t VGA_height
```c
static const size_t VGA_height = 20;
```
- Purpose: Saves the maximum Height for the VGA Character Buffer
### uint8_t VGA_entry_color(enum VGA_color, enum VGA_color)
```c
inline uint8_t VGA_entry_color(enum VGA_color fg, enum VGA_color bg)
```
- Purpose: Creates a color tuple (foreground + background color)
- Parameters:
    - ```enum VGA_color fg```: The desired foreground color
    - ```enum VGA_color bg```: The desired background color
- Return Value: The color combination byte
### uint16_t VGA_entry(unsigned char, uint8_t)
```c
inline uint16_t VGA_entry(unsigned char uc, uint8_t color)
```
- Purpose: Creates a VGA entry (character + color)
- Parameters:
    - ```unsigned char uc```: The character to be printed
    - ```uint8_t color```: The color byte
- Return Value: A 16 bit character containing color information
