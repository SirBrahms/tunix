# The TUNIX Documentation
TUNIX is a simple operating system built mostly from scratch. The following documentation will outline important Kernel and libk APIS, as well as usage of the *K*ernel *I*ntegrated *S*hell (KIS). Additionally, there are instructions for building the latest version of TUNIX and Coding Conventions for potential contributors or curious onlookers.
## Contents
1. [libk](https://github.com/SirBrahms/tunix/blob/main/docs/en/libk.md#01---libk)
    1. [string.h](https://github.com/SirBrahms/tunix/blob/main/docs/en/libk-string.md#0101---stringh)
    2. [stdlib.h](https://github.com/SirBrahms/tunix/blob/main/docs/en/libk-stdlib.md#0102---stdlibh)
    3. [sys/cdefs.h](https://github.com/SirBrahms/tunix/blob/main/docs/en/libk-sys-cdefs.md#0103---syscdefsh)
    4. [sys/io.h](https://github.com/SirBrahms/tunix/blob/main/docs/en/libk-sys-io.md#0104---sysioh)
2. [Kernel API](https://github.com/SirBrahms/tunix/blob/main/docs/en/kernel_api.md)
    1. [TTY.h](https://github.com/SirBrahms/tunix/blob/main/docs/en/kapi-tty.md)
    2. [VGA.h](https://github.com/SirBrahms/tunix/blob/main/docs/en/kapi-vga.md)
    3. [IDT.h](https://github.com/SirBrahms/tunix/blob/main/docs/en/kapi-idt.md)
    4. [isrs/ISR.h](https://github.com/SirBrahms/tunix/blob/main/docs/en/kapi-isrs-isr.md)
    5. [drvs/PCI.h](https://github.com/SirBrahms/tunix/blob/main/docs/en/kapi-drvs-pci.md)
    6. [drvs/AHCI.h](https://github.com/SirBrahms/tunix/blob/main/docs/en/kapi-drvs-ahci.md)
    7. [fs/FAT32.h](https://github.com/SirBrahms/tunix/blob/main/docs/en/kapi-fs-fat32.md)
3. [KIS](https://github.com/SirBrahms/tunix/blob/main/docs/en/KIS.md#03---kis)
    1. Usage
    2. Commands
4. [Build](https://github.com/SirBrahms/tunix/blob/main/docs/en/build.md#04---building-tunix)
5. Conventions (Under Construction)
