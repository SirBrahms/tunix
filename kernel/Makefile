define make_build_dir
if [ -d build/ ]; then echo "build/ exists"; else mkdir -p build; fi
endef
CC = i686-elf-gcc
CFLAGS = -Wall -Wextra -std=gnu99 -ffreestanding -O2
SRC =$(wildcard *.c)
OBJS =$(patsubst %.c,build/%.o,$(SRC))

.PHONY: all
all: build/os.bin

.PHONY: clean
clean: 
	rm -r build

build/boot.o: boot.S
	i686-elf-as boot.S -o build/boot.o

build/%.o: %.c
	i686-elf-gcc -c $(CFLAGS) -o $@ $<

build/os.bin: $(OBJS) build/boot.o
	$(call make_build_dir)
	i686-elf-gcc -T linker.ld -o build/os.bin -ffreestanding -O2 -nostdlib build/*.o -lgcc

iso: build/os.bin
	if [ -d isodir/ ]; then echo "isodir/ exists"; else mkdir -p isodir/boot/grub; fi
	cp build/os.bin isodir/boot/
	grub-mkrescue -o build/os.iso isodir
