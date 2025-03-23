#include "KIS.h"
#include "tty.h"
#include <string.h>
#include "fs/FAT32.h"
#include "drvs/AHCI.h"

void p_main() {

}

/**
 * C++ version 0.4 char* style "itoa":
 * Written by Lukás Chmela
 * Released under GPLv3.
 */
char* itoa(int value, char* result, int base) {
    // check that the base if valid
    if (base < 2 || base > 36) { *result = '\0'; return result; }

    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
  
    // Reverse the string
    while(ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}

void interpret() {
	if (memcmp(current_cmd, "ls", 2) == 0) 
		ls();
	else if (memcmp(current_cmd, "cat", 3) == 0)
		cat();
	else if (memcmp(current_cmd, "isr", 3) == 0)
		isysr();
	else if (memcmp(current_cmd, "clear", 5) == 0)
		clear_terminal();
	else {
		write_string("[ WARN ] Command not recognised\n");
	}
	return;
}

static uint8_t temp_buf[32];

void ls() {
	uint32_t root_cluster32 = fat32_ext->root_cluster;
	uint8_t buf[512];
	ahci_read_sectors(master_dev, get_cluster_sec(root_cluster32) + partition_lba, 0, 1, (uint16_t*)buf);
	
	size_t centry = 0;
	while (buf[centry * 32] != 0 && centry * 32 < 512) {
		if (buf[centry * 32] != 0xE5) {
			if (buf[centry * 32 + 11] == 0x0F) {
				memcpy(temp_buf, &buf[centry * 32], 32);
				goto next;
			}
			fat_dir cdir;
			memcpy(&cdir, &buf[centry * 32], sizeof(fat_dir));
			write_tty((char*)cdir.name, 11);
			putchar('\n');
		}
next:
		centry++;	
	}

	return;
}

void cat() {
}

void isysr() {
	asm volatile("int $0x80");
}

