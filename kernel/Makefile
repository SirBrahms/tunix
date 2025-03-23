define make_build_dir
if [ -d build/ ]; then echo "build/ exists"; else mkdir -p build; fi
endef
define newline


endef
CC = i686-elf-gcc
AS = i686-elf-as
CFLAGS = -g -O2  -Wall -Wextra -std=gnu11 -Iinclude -I../sysroot/usr/local/include  -ffreestanding -D__WITH_SERIAL
SRC =$(wildcard *.c)
SRC +=$(wildcard */*.c)
SRC +=$(wildcard */*/*.c)
SRC +=$(wildcard *.S)
SRC +=$(wildcard */*.S)
OBJS =$(patsubst %.c,build/%.o,$(SRC))
OBJS +=$(patsubst %.S,build/%.o,$(SRC))

GRUBCFG = menuentry "TUNIX" { \
	 multiboot /boot/os.bin \
	 }


.PHONY: all
all: build/setassert build/os.bin

.PHONY: clean
clean: 
	rm -r build
	rm -r isodir

build/setassert:
	mkdir -p build/fs
	mkdir -p build/drvs/PCI
	mkdir -p build/drvs/AHCI
	mkdir -p build/isrs
	mkdir -p isodir/boot/grub
	mkdir -p build/KIS
	echo $(GRUBCFG) > isodir/boot/grub/grub.cfg
	echo $(HDCFG) > build/hd.layout
	touch build/setassert

build/%.o: %.S
	$(AS) -c -o $@ $<

build/%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $< 

build/os.bin: $(OBJS)
	$(call make_build_dir)
	$(CC) -T linker.ld -o build/os.bin -ffreestanding -O2 build/*.o build/*/*.o build/*/*/*.o  -nostdlib -l:libk.a -lgcc --sysroot=../sysroot -L "../sysroot/usr/local/lib" -L build/  -z muldefs 


iso: build/os.bin
	cp build/os.bin isodir/boot/
	grub-mkrescue -o build/os.iso isodir

img: build/os.bin
	dd if=/dev/zero of=build/disk.img bs=512 count=131072
	sfdisk build/disk.img < hd.layout
	losetup /dev/loop0 build/disk.img 
	losetup /dev/loop1 build/disk.img -o 1048576
	mkdosfs -F32 -f 2 /dev/loop1
	mkdir -p /mnt/os
	mount /dev/loop1 /mnt/os
	grub-install --boot-directory=/mnt/os/boot --no-floppy --modules="normal part_msdos fat multiboot biosdisk" /dev/loop0
	echo $(GRUBCFG) > /mnt/os/boot/grub/grub.cfg
	cp build/os.bin /mnt/os/boot
	touch /mnt/os/a.txt
	sync
	umount /mnt/os
	losetup -D
