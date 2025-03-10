/* Function that loads the GDT */

gdtr:
.short // base
.long  // limit

.section .text
.global _set_GDT
.type _set_GDT, @function
_set_GDT:
	mov +4(%esp), %ax
	mov %ax, (gdtr)
	mov +8(%esp), %eax
	mov %eax, gdtr + 2
	lgdt (gdtr)
	ret
