.global load_IDT
.type load_IDT, @function
load_IDT:
	cli
	lidt iptr
	sti // enable interrupts again
	ret
