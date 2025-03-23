#include "fs/FAT32.h"
#include "drvs/AHCI.h"
#include "tty.h"
#include <string.h>
#include <stdlib.h>


void parse_fat_br(uint8_t* raw, fat_BR* br) {
	memcpy(br->bootjmp, &raw[0], 3);
	memcpy(br->oem_id, &raw[3], 8);
	    
	br->bytes_per_sec = *(uint16_t*)&raw[11];   // Little-endian
	br->secs_per_cluster = raw[13];
	br->reserved_secs = *(uint16_t*)&raw[14];
	br->fat_num = raw[16];
	br->root_entries = *(uint16_t*)&raw[17];
	br->sec_num_16 = *(uint16_t*)&raw[19];
	br->media_desc = raw[21];
	br->secs_per_fat = *(uint16_t*)&raw[22];
	br->secs_per_track = *(uint16_t*)&raw[24];
	br->heads = *(uint16_t*)&raw[26];
	br->hidden_secs = *(uint32_t*)&raw[28];
	br->sec_num_32 = *(uint32_t*)&raw[32];
	memcpy(br->extended, &raw[36], 54);  // Copy the extended boot record
}

void fat32_init() {
	fat_BR br;
	uint8_t buf[512];

	ahci_read_sectors(master_dev, 0, 0, 1, (uint16_t*)buf);
	
	partition_lba = (uint32_t)((buf[0x1BE + 11] << 24) + (buf[0x1BE + 10] << 16) + (buf[0x1BE + 9] << 8) + buf[0x1BE + 8]);
	
	uint8_t bpb_temp[512];
	ahci_read_sectors(master_dev, partition_lba, 0, 1, (uint16_t*)bpb_temp);
	parse_fat_br(bpb_temp, &br);

	boot_fat = br;

	fat32_ext = (fat32_ext_BR*)boot_fat.extended;
	
	total_sectors = (boot_fat.sec_num_16 == 0) ? boot_fat.sec_num_32 : boot_fat.sec_num_16;
	fat_size = (boot_fat.secs_per_fat == 0) ? fat32_ext->fat_size : boot_fat.secs_per_fat;
	root_dir_secs = ((boot_fat.root_entries * 32) + (boot_fat.bytes_per_sec - 1)) / boot_fat.bytes_per_sec;
	first_data_sec = boot_fat.reserved_secs + (boot_fat.fat_num * fat_size) + root_dir_secs;
	first_fat_sec = boot_fat.reserved_secs;
	data_secs = total_sectors - (boot_fat.reserved_secs + (boot_fat.fat_num * fat_size) + root_dir_secs);
	total_clusters = data_secs / boot_fat.secs_per_cluster;
}


