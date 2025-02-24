define make_build_dir
if [ -d build/ ]; then echo "build/ exists"; else mkdir -p build; fi
endef
CC = i686-elf-gcc
AS = i686-elf-as
CFLAGS = -g -O2  -Wall -Wextra -std=gnu11 -Iinclude -I../sysroot/usr/local/include  -ffreestanding
SRC =$(wildcard *.c)
OBJS =$(patsubst %.c,build/%.o,$(SRC))

.PHONY: all
all: build/os.bin

.PHONY: clean
clean: 
	rm -r build

build/boot.o: boot.S
	$(AS) boot.S -o build/boot.o

build/%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $< 

build/os.bin: $(OBJS) build/boot.o
	$(call make_build_dir)
	$(CC) -v  -T linker.ld -o build/os.bin -ffreestanding -O2 -nostdlib build/*.o  -l:libk.a -lgcc --sysroot=../sysroot -L "../sysroot/usr/local/lib" -L build/

iso: build/os.bin
	if [ -d isodir/ ]; then echo "isodir/ exists"; else mkdir -p isodir/boot/grub; fi
	cp build/os.bin isodir/boot/
	grub-mkrescue -o build/os.iso isodir
