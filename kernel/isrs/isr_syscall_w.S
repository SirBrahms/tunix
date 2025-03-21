.section .text
.align 4
.global isr_syscall_w
.type isr_syscall_w, @function
isr_syscall_w:
	pushal
	cld
	call isr_syscall
	popal
	iret
