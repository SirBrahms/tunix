# 02.01 - TTY.h
Dieses Header-File ist für das Schreiben von Zeichen in den Videospeicher des Geräts verantwortlich. Es verwaltet außerdem die serielle Ein-/Ausgabe.

## Mitglieder
### void terminal_init(void)
```c
void terminal_init(void)
```
- **Zweck**: Initialisiert das Terminal  
- **Parameter**: Keine  
- **Rückgabewert**: Void  

### void clear_terminal(void)
```c
void clear_terminal(void)
```
- **Zweck**: Leert das Terminal  
- **Parameter**: Keine  
- **Rückgabewert**: Void  

### void clear_current_line(void)
```c
void clear_current_line(void)
```
- **Zweck**: Löscht die aktuelle Zeile im Terminal  
- **Parameter**: Keine  
- **Rückgabewert**: Void  

### void set_terminal_color(uint8_t)
```c
void set_terminal_color(uint8_t color)
```
- **Zweck**: Setzt die Terminalfarbe  
- **Parameter**:  
    - `uint8_t color`: Eine gültige VGA-Farbe  
- **Rückgabewert**: Void  

### void put_terminal_entry_at(char, uint8_t, size_t, size_t)
```c
void put_terminal_entry_at(char c, uint8_t color, size_t x, size_t y)
```
- **Zweck**: Setzt ein Zeichen mit einer bestimmten Farbe an die angegebenen Koordinaten  
- **Parameter**:  
    - `char c`: Das zu schreibende Zeichen  
    - `uint8_t color`: Eine gültige VGA-Farbe  
    - `size_t x`: Die x-Koordinate  
    - `size_t y`: Die y-Koordinate  
- **Rückgabewert**: Void  

### void putchar(char)
```c
void putchar(char c)
```
- **Zweck**: Schreibt ein Zeichen mit der aktuellen Terminalfarbe an die nächste freie Position  
- **Parameter**:  
    - `char c`: Das zu schreibende Zeichen  
- **Rückgabewert**: Void  

### void write_tty(const char* str, size_t length)
```c
void write_tty(const char* str, size_t length)
```
- **Zweck**: Schreibt eine Zeichenkette der angegebenen Länge an die nächste freie Position  
- **Parameter**:  
    - `const char* str`: Die zu schreibende Zeichenkette  
    - `size_t length`: Die Länge der Zeichenkette  
- **Rückgabewert**: Void  

### void write_string(const char* str)
```c
void write_string(const char* str)
```
- **Zweck**: Schreibt eine nullterminierte Zeichenkette an die nächste freie Position  
- **Parameter**:  
    - `const char* str`: Die zu schreibende Zeichenkette  
- **Rückgabewert**: Void  

### int serial_init()
```c
int serial_init()
```
- **Zweck**: Initialisiert den COM0-Port  
- **Parameter**: Keine  
- **Rückgabewert**: 0 bei Erfolg, 1 bei Fehler  

### int serial_received()
```c
int serial_received()
```
- **Zweck**: Prüft, ob der serielle Port neue Daten hat  
- **Parameter**: Keine  
- **Rückgabewert**: 0, wenn keine Daten vorliegen, 1, wenn Daten verfügbar sind  

### char read_serial()
```c
char read_serial()
```
- **Zweck**: Liest ein Zeichen von COM0  
- **Parameter**: Keine  
- **Rückgabewert**: Das gelesene Zeichen  

### int serial_rts()
```c
int serial_rts()
```
- **Zweck**: Prüft, ob das COM-Gerät bereit zum Senden ist  
- **Parameter**: Keine  
- **Rückgabewert**: 0, wenn nicht bereit, 1, wenn bereit  

### void write_serial(char)
```c
void write_serial(char c)
```
- **Zweck**: Schreibt ein Zeichen an den seriellen Port  
- **Parameter**:  
    - `char c`: Das zu schreibende Zeichen  
- **Rückgabewert**: Void  