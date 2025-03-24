# 02.02 - VGA.h
Dieses Header-File ist für die Erstellung von VGA-Textmodus-kompatiblen Zeichen verantwortlich.

## Mitglieder
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
- **Zweck**: Speichert alle möglichen VGA-Farbwerte  

### size_t VGA_width
```c
static const size_t VGA_width = 80;
```
- **Zweck**: Speichert die maximale Breite des VGA-Zeichenpuffers  

### size_t VGA_height
```c
static const size_t VGA_height = 20;
```
- **Zweck**: Speichert die maximale Höhe des VGA-Zeichenpuffers  

### uint8_t VGA_entry_color(enum VGA_color, enum VGA_color)
```c
inline uint8_t VGA_entry_color(enum VGA_color fg, enum VGA_color bg)
```
- **Zweck**: Erstellt ein Farbtupel (Vordergrund- und Hintergrundfarbe)  
- **Parameter**:  
    - `enum VGA_color fg`: Die gewünschte Vordergrundfarbe  
    - `enum VGA_color bg`: Die gewünschte Hintergrundfarbe  
- **Rückgabewert**: Das Farb-Kombinationsbyte  

### uint16_t VGA_entry(unsigned char, uint8_t)
```c
inline uint16_t VGA_entry(unsigned char uc, uint8_t color)
```
- **Zweck**: Erstellt einen VGA-Eintrag (Zeichen + Farbe)  
- **Parameter**:  
    - `unsigned char uc`: Das zu druckende Zeichen  
    - `uint8_t color`: Das Farbbyte  
- **Rückgabewert**: Ein 16-Bit-Zeichen mit Farbinformationen  