/* Multiboot header constant time */
.set ALIGN,	1<<0
.set MEMINFO,	1<<1
.set FLAGS,	ALIGN | MEMINFO
.set MAGIC,	0x1BADB002
.set CHECKSUM,	-(MAGIC + FLAGS)

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.section .bss
.align 16
stack_bottom:
.skip 16384		// 16 KiB
stack_top:

.section .text
.global _start
.type _start, @function
_start:
	mov $stack_top, %esp // stack pointer register points to top of the stack (which grows downwards)
	call kernel_main

	// Put system into an infinite loop
	cli
1:	hlt
	jmp 1b

.global load_GDT
.type load_GDT, @function
load_GDT:
	lgdt [gp]
	ret
