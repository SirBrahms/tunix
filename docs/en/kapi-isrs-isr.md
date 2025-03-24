# 02.04 - isrs/ISR.h
This headerfile exposes the functions called when an interrupt occurs.
# Members
### void exception_handler(void)
```c
void exception_handler(void)
```
- Purpose: Currently Unused
- Parameters: None
- Return Value: Void
### void exception_handler_statc(void)
```c
void exception_handler_statc(void)
```
- Purpose: Currently Unused
- Parameters: None
- Return Value: Void
### void isr_nop(void)
```c
extern void isr_nop(void)
```
- Purpose: Immediately returns from the interrupt
- Parameters: None
- Return Value: Void
### void isr_syscall_w(void)
```c
extern void isr_syscall_w(void)
```
- Purpose: The Syscall handler function. Currently only prints "Syscall!"
- Parameters: None
- Return Value: Void