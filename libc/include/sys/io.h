#ifndef __SYS_IO_HEADER
#define __SYS_IO_HEADER

static inline unsigned char inb(unsigned short int port) {
	unsigned char _v;
	asm volatile ("inb %w1,%0":"=a" (_v):"Nd" (port));

	return _v;
}

static inline unsigned short int inw(unsigned short int port) {
	unsigned short int _v;
	asm volatile ("inw %w1,%0":"=a" (_v):"Nd" (port));

	return _v;
}

static inline unsigned int inl(unsigned short int port) {
	unsigned int _v;
	asm volatile ("inl %w1,%0":"=a" (_v):"Nd" (port));

	return _v;
}

static inline void outb(unsigned char value, unsigned short int port) {
	asm volatile ("outb %b0,%w1": :"a" (value), "Nd" (port));
}

static inline void outw(unsigned short int value, unsigned short int port) {
	asm volatile ("outw %w0,%w1": :"a" (value), "Nd" (port));
}

static inline void outl(unsigned int value, unsigned short int port) {
	asm volatile ("outl %0,%w1": :"a" (value), "Nd" (port));
}

#endif
