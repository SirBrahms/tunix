.section .text
.global load_GDT
.type load_GDT, @function
load_GDT:
	lgdt [gp]
	ret

.global load_IDT
.type load_IDT, @function
load_IDT:
	lidt [iptr]
	sti // enable interrupts again
	ret
