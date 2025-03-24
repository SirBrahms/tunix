# 01.01 - string.h
Das Header file string.h stellt wichtige Funktionen zur Verfügung, um mit Speicherbereichen und Zeichenketten zu arbeiten.

## Mitglieder
### int memcmp(const void*, const void*, size_t)
```c
int memcmp(const void* p1, const void* p2, size_t size)
```
- Zweck: Vergleicht zwei Speicherbereiche mit einer gegebenen Größe
- Parameter:
    - ```const void* p1```: Der erste Speicherbereich
    - ```const void* p2```: Der zweite Speicherbereich
    - ```size_t size```: Die Anzahl der Bytes, die verglichen werden sollen
- Rückgabewert: 0, wenn die Bereiche gleich sind, andernfalls das Vorzeichen der Differenz

### void* memcpy(void* __restrict, const void* __restrict, size_t)
```c
void* memcpy(void* destp, const void* srcp, size_t n)
```
- Zweck: Kopiert einen Speicherbereich mit einer gegebenen Größe in einen anderen
- Parameter:
    - ```void* destp```: Der Ziel-Zeiger
    - ```const void* srcp```: Der Quell-Zeiger
    - ```size_t n```: Die Anzahl der Bytes, die kopiert werden sollen
- Rückgabewert: Der Zeiger auf das Ziel

### void* memmove(void*, const void*, size_t)
```c
void* memmove(void* dest, const void* src, size_t n)
```
- Zweck: Kopiert einen Speicherbereich mit einer gegebenen Größe in einen anderen. Die Bereiche können sich überschneiden
- Parameter:
    - ```void* dest```: Der Ziel-Zeiger
    - ```const void* src```: Der Quell-Zeiger
    - ```size_t n```: Die Anzahl der Bytes, die kopiert werden sollen
- Rückgabewert: Der Zeiger auf das Ziel

### void* memset(void*, int, size_t)
```
void* memset(void* source, int value, size_t n)
```
- Zweck: Setzt einen Speicherbereich der Größe n auf einen gegebenen Wert
- Parameter:
    - ```void* source```: Der Speicherort
    - ```int value```: Der Wert, der geschrieben werden soll
    - ```size_t n```: Die Anzahl der Bytes, die geschrieben werden sollen
- Rückgabewert: Der Zeiger auf die Quelle

### size_t strlen(const char*)
```c
size_t strlen(const char* str)
```
- Zweck: Gibt die Länge einer NULL-terminierten Zeichenkette zurück
- Parameter:
    - ```const char* str```: Die Zeichenkette
- Rückgabewert: Die Länge der Zeichenkette

### char* strtok(char*, const char*)
```c
char* strtok(char* s, const char* delim)
```
- Zweck: Zerlegt die Zeichenkette mit einem gegebenen Trennzeichen
- Parameter:
    - ```char* s```: Die Zeichenkette, die zerlegt werden soll
    - ```const char* delim```: Das Trennzeichen
- Rückgabewert: Das Token

### char* strpbrk(char*, const char*)
```c
char* strpbrk(char* str, const char* allow)
```
- Zweck: Durchsucht eine Zeichenkette, bis ein erlaubtes Byte gefunden wird
- Parameter:
    - ```char* str```: Die Zeichenkette, die durchsucht werden soll
    - ```const char* allow```: Die erlaubten Zeichen
- Rückgabewert: Ein Zeiger auf das erste erlaubte Byte

### size_t strspn(const char*, const char*)
```c
size_t strspn(const char* str, const char* allow)
```
- Zweck: Findet das maximale Anfangssegment einer Zeichenkette, das nur aus erlaubten Zeichen besteht
- Parameter:
    - ```const char* str```: Die Zeichenkette, die durchsucht werden soll
    - ```const char* allow```: Die erlaubten Zeichen
- Rückgabewert: Die Länge des gefundenen Segments

### char* strchr(const char*, char)
```c
char* strchr(const char* s, char c)
```
- Zweck: Findet die erste Instanz eines gegebenen Zeichens in einer Zeichenkette
- Parameter:
    - ```const char* str```: Die Zeichenkette, die durchsucht werden soll
    - ```char c```: Das zu findende Zeichen
- Rückgabewert: Ein Zeiger auf das gefundene Zeichen
