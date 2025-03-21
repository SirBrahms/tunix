#ifndef __ISRS_ISR_HEADER__
#define __ISRS_ISR_HEADER__

void exception_handler(void);
void exception_handler_statc(void);
extern void isr_nop(void);
extern void isr_syscall_w(void);

#endif
