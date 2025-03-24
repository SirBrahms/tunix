#include "KIS.h"
#include "tty.h"
#include <string.h>
#include "fs/FAT32.h"
#include "drvs/AHCI.h"
#include <stdbool.h>

void KIS() {
	while (1) {
		char c = read_serial();

		if (c == '\n' || c == '\r') {	
			putchar('\n');
			if (interpret())
				break;
			cmd_index = 0;
			current_cmd[cmd_index] = '\0';
		}
		else if (c == 0x8 || c == 0x7F) {
			cmd_index--;
			current_cmd[cmd_index] = '\0';
		}
		else if (cmd_index < 128) {
			putchar(c);
			current_cmd[cmd_index] = c;
			cmd_index++;
			current_cmd[cmd_index] = '\0'; // terminate the string
		}
		else {
			write_string("[ WARN ] Command too long\n");
			cmd_index = 0;
			current_cmd[cmd_index] = '\0';
			putchar('\n');
		}
	}
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

int interpret() {
	if (memcmp(current_cmd, "ls", 2) == 0) 
		ls();
	else if (memcmp(current_cmd, "isr", 3) == 0)
		isysr();
	else if (memcmp(current_cmd, "cd", 2) == 0)
		cd();
	else if (memcmp(current_cmd, "clear", 5) == 0)
		clear_terminal();
	else if (memcmp(current_cmd, "cat", 3) == 0) 
		cat();
	else if (memcmp(current_cmd, "exit", 4) == 0) 
		return 1;
	else {
		write_string("[ WARN ] Command not recognised\n");
	}
	return 0;
}

static uint8_t temp_buf[32];

void ls() {
	uint8_t buf[512];
	ahci_read_sectors(master_dev, get_cluster_sec(current_cluster), 0, 1, (uint16_t*)buf);
	
	size_t centry = 0;
	while (buf[centry * 32] != 0 && centry * 32 < 512) {
		if (buf[centry * 32] != 0xE5) {
			if (buf[centry * 32 + 11] == 0x0F) {
				memcpy(temp_buf, &buf[centry * 32], 32);
				centry++;
				continue;
			}
			fat_dir cdir;
			memcpy(&cdir, &buf[centry * 32], sizeof(fat_dir));
			write_tty((char*)cdir.name, 11);
			putchar('\n');
		}
		centry++;	
	}

	return;

}

bool compare_fat_name(fat_dir* entry, const char* name) {
	char padded_name[11];
    	memset(padded_name, ' ', 11); // Fill with spaces (FAT standard)

    	const char *ext = strchr(name, '.'); // Find extension separator
    	size_t name_len = ext ? (size_t)(ext - name) : strlen(name);
    	size_t ext_len = ext ? strlen(ext + 1) : 0;

    	if (name_len > 8) name_len = 8;
    	if (ext_len > 3) ext_len = 3;

    	memcpy(padded_name, name, name_len);
    	if (ext) memcpy(padded_name + 8, ext + 1, ext_len);

    	return memcmp(entry->name, padded_name, 11) == 0;
}

void cat() {
	uint8_t buf[512];
	ahci_read_sectors(master_dev, get_cluster_sec(current_cluster), 0, 1, (uint16_t*)buf);
	
	size_t centry = 0;
	while (buf[centry * 32] != 0 && centry * 32 < 512) {
		if (buf[centry * 32] != 0xE5) {
			if (buf[centry * 32 + 11] == 0x0F) {
				memcpy(temp_buf, &buf[centry * 32], 32);
				centry++;
				continue;
			}
			fat_dir cdir;
			memcpy(&cdir, &buf[centry * 32], sizeof(fat_dir));
			write_tty((char*)&buf[centry * 32], 32);
		}
		centry++;	
	}
	putchar('\n');

	return;

}

void cd() {
	uint8_t buf[512];
	ahci_read_sectors(master_dev, get_cluster_sec(current_cluster), 0, 1, (uint16_t*)buf);
	
	char* tok = strtok(current_cmd, " ");
	tok = strtok(NULL, " ");
	size_t centry = 0;
	while (buf[centry * 32] != 0 && centry * 32 < 512) {
		if (buf[centry * 32] != 0xE5) { // Unused
			if (buf[centry * 32 + 11] == 0x0F) {
				memcpy(temp_buf, &buf[centry * 32], 32);
				centry++;
				continue;
			}
			fat_dir cdir;
			memcpy(&cdir, &buf[centry * 32], sizeof(fat_dir));
			if (memcmp(tok, "..", 2) == 0) {
				current_cluster = prev_cluster;
				return;
			}
			else if (memcmp(tok, "/", 1) == 0) {
				current_cluster = fat32_ext->root_cluster;
				return;
			}
			
			if (compare_fat_name(&cdir, tok)) {
				// found our dir, cd
				prev_cluster = current_cluster;
				current_cluster = ((uint32_t)(cdir.cluster_high << 16)) | cdir.cluster_low;
				return;
			}
		}
		centry++;
	}

	write_string("[ WARN ] Directory doesn't exist\n");
}

void isysr() {
	asm volatile("int $0x80");
}

