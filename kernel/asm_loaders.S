.text
.align 4
.global load_GDT
.type load_GDT, @function
load_GDT:
	lgdt gp
	mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %ds
	mov %ax, %gs
	mov %ax, %ss
	ljmp $0x08, $_flush
_flush:
	ret

.global load_IDT
.type load_IDT, @function
load_IDT:
	cli
	lidt iptr
	sti // enable interrupts again
	ret
