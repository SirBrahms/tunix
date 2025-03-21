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

/*
 * Create the GDT
 */
.section .data
gdt_start:
gdt_null:
.long 0x0
.long 0x0

gdt_kcode:
.word 0xFFFF             # limit
.word 0x0                # base
.byte 0x0                # base
.byte 0b10011010         # 1st flags | type flags
.byte 0b11001111         # 2nd flags | limit
.byte 0x0                # base

gdt_kdata:
.word 0xFFFF             # limit
.word 0x0                # base
.byte 0x0                # base
.byte 0b10010010         # 1st flags | type flags
.byte 0b11001111         # 2nd flags | limit
.byte 0x0                # base
gdt_end:

gdtr:
.word (gdt_end - gdt_start - 1)
.long gdt_start

.section .text
.global _start
.type _start, @function
_start:
	# set the position of `%esp' to the top of the stack
	mov $stack_top, %esp

	# GDT, paging, and other features
flush_gdt:
	cli
	lgdt (gdtr)
	movw $0x10, %ax
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %fs
	movw %ax, %gs
	movw %ax, %ss
	ljmp $0x08, $flush_end
flush_end:

boot_kernel:
	call kernel_main

	// Put system into an infinite loop
	cli
1:	hlt
	jmp 1b

/*
.global load_GDT
.type load_GDT, @function
load_GDT:
	lgdt [gp]
	ret
*/

