.section .init
	/* crtend.o init section here */
	popl %ebp
	ret

.section .fini
	/* crtend.o fini section here */
	popl %ebp
	ret
