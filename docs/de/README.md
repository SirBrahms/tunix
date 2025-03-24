# Die TUNIX-Dokumentation

TUNIX ist ein einfaches Betriebssystem, das größtenteils von Grund auf neu entwickelt wurde. Die folgende Dokumentation beschreibt wichtige Kernel- und libk-APIs sowie die Nutzung der Kernel Integrated Shell (KIS). Zusätzlich gibt es Anleitungen zum Erstellen der neuesten Version von TUNIX sowie Coding-Konventionen für potenzielle Mitwirkende oder interessierte Beobachter.

## Inhalt
1. [libk](https://github.com/SirBrahms/tunix/blob/main/docs/de/libk.md#01---libk)
    1. [string.h](https://github.com/SirBrahms/tunix/blob/main/docs/de/libk-string.md#0101---stringh)
    2. [stdlib.h](https://github.com/SirBrahms/tunix/blob/main/docs/de/libk-stdlib.md#0102---stdlibh)
    3. [sys/cdefs.h](https://github.com/SirBrahms/tunix/blob/main/docs/de/libk-sys-cdefs.md#0103---syscdefsh)
    4. [sys/io.h](https://github.com/SirBrahms/tunix/blob/main/docs/de/libk-sys-io.md#0104---sysioh)
2. [Kernel API](https://github.com/SirBrahms/tunix/blob/main/docs/de/kernel_api.md)
    1. [TTY.h](https://github.com/SirBrahms/tunix/blob/main/docs/de/kapi-tty.md)
    2. [VGA.h](https://github.com/SirBrahms/tunix/blob/main/docs/de/kapi-vga.md)
    3. [IDT.h](https://github.com/SirBrahms/tunix/blob/main/docs/de/kapi-idt.md)
    4. [isrs/ISR.h](https://github.com/SirBrahms/tunix/blob/main/docs/de/kapi-isrs-isr.md)
    5. [drvs/PCI.h](https://github.com/SirBrahms/tunix/blob/main/docs/de/kapi-drvs-pci.md)
    6. [drvs/AHCI.h](https://github.com/SirBrahms/tunix/blob/main/docs/de/kapi-drvs-ahci.md)
    7. [fs/FAT32.h](https://github.com/SirBrahms/tunix/blob/main/docs/de/kapi-fs-fat32.md)
3. [KIS](https://github.com/SirBrahms/tunix/blob/main/docs/ede/KIS.md#03---kis)
    1. Nutzung
    2. Befehle
4. [Build](https://github.com/SirBrahms/tunix/blob/main/docs/de/build.md#04---building-tunix)
5. Konventionen (Under Construction)