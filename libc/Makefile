CC=i686-elf-gcc
AR=i686-elf-ar

DESTDIR=../sysroot
PREFIX=/usr/local
INCLUDEDIR=$(PREFIX)/include
LIBDIR=$(PREFIX)/lib

CFLAGS=-O2 -g -ffreestanding -Wall -Wextra
CPPFLAGS=-D__is_libc -Iinclude
LIBK_CFLAGS=$(CFLAGS)
LIBK_CPPFLAGS=$(CPPFLAGS) -D__is_libk

FREEOBJS=\
	 string/strlen.o\
	 string/memcpy.o\
	 string/memcmp.o\
	 string/memmove.o\
	 string/memset.o\
	 string/strtok.o\
	 stdlib/abort.o

OBJS=$(FREEOBJS)

LIBK_OBJS=$(FREEOBJS:.o=.libk.o)

BINARIES=libk.a #no libc yet

.PHONY: all clean install install-headers install-libs
.SUFFIXES: .o .libk.o .c .S


all: $(BINARIES)

libc.a: $(OBJS)
	$(AR) rcs $@ $(OBJS)

libk.a: $(LIBK_OBJS)
	$(AR) rcs $@ $(LIBK_OBJS)

.c.o: 
	$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS)

.S.o: 
	$(CC) -MD -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

.c.libk.o: 
	$(CC) -MD -c $< -o $@ -std=gnu11 $(LIBK_CFLAGS) $(LIBK_CPPFLAGS)

.S.libk.o: 
	$(CC) -MD -c $< -o $@ $(LIBK_CFLAGS) $(LIBK_CPPFLAGS)

clean:
	rm -f $(BINARIES) *.a
	rm -f $(OBJS) $(LIBK_OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) $(LIBK_OBJS:.o=.d) *.d */*.d */*/*.d

install: install-headers install-libs

install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -R include/. $(DESTDIR)$(INCLUDEDIR)/.

install-libs: $(BINARIES)
	mkdir -p $(DESTDIR)$(LIBDIR)
	cp $(BINARIES) $(DESTDIR)$(LIBDIR)

-include $(OBJS:.o=.d)
-include $(LIBK_OBJS:.o=.d)



