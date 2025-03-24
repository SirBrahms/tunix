# 04 - Building Tunix
Building Tunix from the cloned repository can be tedious but offers additional configuration possibilities (see Section 04.2 - Build Options).

**Disclaimer:** The build process as described here only works on UNIX-Based systems. Windows and Apple Users will have to find alternatives.
## Prerequisites
First you will need a Cross Compiler, since TUNIX is written for the i686-Architecture. For this, you will need to build GCC and binutils from scratch. See https://wiki.osdev.org/GCC_Cross-Compiler on how to do this.
## Build
After cloning the repository, you will need to make a 'sysroot' directory at the same level as kernel and libc. After that, head into the libc directory and run ```make```, followed by ```make install```. After completing that step, change directory to the kernel dir. There, run ```make```, followed by ```sudo make img``` (you need sudo privileges because the img-making process uses loop devices). The built disk will be in build/disk.img
## Run
To run the OS use the following command: <br>
```bash
qemu-system-i386 -serial stdio -drive format=raw,id=disk,file=[PATH TO DISK],if=none -device ich9-ahci,addr=06,id=ahci -device ide-hd,drive=disk,bus=ahci.0
```
The Os has not been tested with other emulators and is not guranteed to work.
Using this setup, the OS will take its input from the console in which the command was run.