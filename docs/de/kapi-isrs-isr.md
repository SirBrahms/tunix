# 02.04 - isrs/ISR.h
Diese Header-Datei stellt die Funktionen zur Verfügung, die aufgerufen werden, wenn ein Interrupt auftritt.

# Mitglieder
### void exception_handler(void)
```c
void exception_handler(void)
```
- Zweck: Derzeit ungenutzt
- Parameter: Keine
- Rückgabewert: Void

### void exception_handler_statc(void)
```c
void exception_handler_statc(void)
```
- Zweck: Derzeit ungenutzt
- Parameter: Keine
- Rückgabewert: Void

### void isr_nop(void)
```c
extern void isr_nop(void)
```
- Zweck: Gibt sofort vom Interrupt zurück
- Parameter: Keine
- Rückgabewert: Void

### void isr_syscall_w(void)
```c
extern void isr_syscall_w(void)
```
- Zweck: Die Syscall-Handler-Funktion. Derzeit gibt sie nur "Syscall!" aus
- Parameter: Keine
- Rückgabewert: Void