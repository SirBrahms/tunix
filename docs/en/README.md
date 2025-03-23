# The TUNIX Documentation
TUNIX is a simple operating system built mostly from scratch. The following documentation will outline important Kernel and libk APIS, as well as usage of the **P**recompiled **U**ser **Sh**ell (PUSh). Additionally, there are instructions for building the latest version of TUNIX and Coding Conventions for potential contributors or curious onlookers.
## Contents
1. libk
    1. string.h
    2. stdlib.h
2. Kernel API
    1. TTY.h
    2. IDT.h
    3. drvs/AHCI.h
    4. drvs/PCI.h
    5. fs/VFS.h
    6. fs/FAT32.h
    7. isrs/ISR.h
3. PUSh
    1. Usage
    2. Commands
4. [Build](https://github.com/SirBrahms/tunix/blob/main/docs/en/build.md#04---building-tunix)
5. Conventions
