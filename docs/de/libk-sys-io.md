# 01.04 - sys/io.h
Das io Header file implementiert Funktionen zum Lesen und Schreiben an Geräteports unter Verwendung der ```in[size]```-Anweisung.

## Mitglieder
### unsigned char inb(unsigned short int)
```c
static inline unsigned char inb(unsigned short int port)
```
- Zweck: Liest ein Byte vom angegebenen Port
- Parameter:
    - ```unsigned short int port```: Der Port
- Rückgabewert: Das gelesene Byte

### unsigned int inl(unsigned short int)
```c
static inline unsigned int inl(unsigned short int port)
```
- Zweck: Liest ein Langwort vom angegebenen Port
- Parameter:
    - ```unsigned short int port```: Der Port
- Rückgabewert: Das gelesene Langwort

### void outb(unsigned char, unsigned short int)
```c
static inline void outb(unsigned char value, unsigned short int port) 
```
- Zweck: Schreibt ein Byte zum angegebenen Port
- Parameter:
    - ```unsigned char value```: Der Wert, der geschrieben werden soll
    - ```unsigned short int port```: Der Port
- Rückgabewert: Void

### void outw(unsigned short int, unsigned short int)
```c
static inline void outw(unsigned char value, unsigned short int port) 
```
- Zweck: Schreibt ein Wort zum angegebenen Port
- Parameter:
    - ```unsigned char value```: Der Wert, der geschrieben werden soll
    - ```unsigned short int port```: Der Port
- Rückgabewert: Void

### void outl(unsigned int, unsigned short int)
```c
static inline void outl(unsigned char value, unsigned short int port) 
```
- Zweck: Schreibt ein Langwort zum angegebenen Port
- Parameter:
    - ```unsigned char value```: Der Wert, der geschrieben werden soll
    - ```unsigned short int port```: Der Port
- Rückgabewert: Void
