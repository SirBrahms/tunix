.section .init
.global _init
.type _init, @function

_init:
	push %ebp
	movl %esp, %ebp

	/* crtbegin.o .init section goes here */

.section .fini
.global _fini
.type _fini, @function

_fini:
	push %ebp
	movl %esp, %ebp

	/* crtbegin.o .fini section goes here */
