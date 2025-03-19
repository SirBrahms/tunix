define make_build_dir
if [ -d build/ ]; then echo "build/ exists"; else mkdir -p build; fi
endef
CC = i686-elf-gcc
AS = i686-elf-as
CFLAGS = -g -O2  -Wall -Wextra -std=gnu11 -Iinclude -I../sysroot/usr/local/include  -ffreestanding -D__WITH_SERIAL
SRC =$(wildcard *.c)
SRC +=$(wildcard fs/*.c)
SRC +=$(wildcard *.S)
OBJS =$(patsubst %.c,build/%.o,$(SRC))
OBJS +=$(patsubst %.S,build/%.o,$(SRC))


.PHONY: all
all: build/os.bin

.PHONY: clean
clean: 
	rm -r build




build/%.o: %.S
	$(AS) -c -o $@ $<

build/%.o: %.c
	mkdir -p build/fs
	$(CC) -c $(CFLAGS) -o $@ $< 

build/os.bin: $(OBJS)
	$(call make_build_dir)
	$(CC) -T linker.ld -o build/os.bin -ffreestanding -O2 build/*.o build/*/*.o  -nostdlib -l:libk.a -lgcc --sysroot=../sysroot -L "../sysroot/usr/local/lib" -L build/  -z muldefs 


iso: build/os.bin
	if [ -d isodir/ ]; then echo "isodir/ exists"; else mkdir -p isodir/boot/grub; fi
	cp build/os.bin isodir/boot/
	grub-mkrescue -o build/os.iso isodir
