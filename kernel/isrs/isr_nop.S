.section .text

.align 4
.global isr_nop
.type isr_nop, @function
isr_nop:
	iret
