#ifndef __FS_FAT32_HEADER
#define __FS_FAT32_HEADER

#include <stdint.h>

struct _fat32_ext_BR {
	uint32_t fat_size; // FAT size in sectors
	uint16_t flags;
	uint16_t version;
	uint32_t root_cluster; // cluster number of the root directory
	uint16_t fs_info_sec; // sector of the fs_info structure
	uint16_t backup_boot_sec; // sector number of the Backup Boot Sector
	uint8_t rsv0[12]; // reserved
	uint8_t drive_nr; // drive number
	uint8_t ntflags; // flags under WindowsNT
	uint8_t signature; // signature must be 0x28 or 0x29
	uint32_t serial_num; // volume ID (serial Number)
	uint8_t volume_name[11]; // volume name string (padded with spaces)
	uint8_t system_identifier[8]; // System Identifier, always FAT32 (padded with three spaces)
} __attribute__((packed));
typedef struct _fat32_ext_BR fat32_ext_BR;

struct _fat_BR {
	uint8_t bootjmp[3]; // asm instructions to jump over the BPB
	uint8_t oem_id[8]; // DOS: version, linux: mkdosfs, padded with spaces
	uint16_t bytes_per_sec; // number of bytes in a sector (little endian)
	uint8_t secs_per_cluster; // number of sectors per cluster
	uint16_t reserved_secs; // number of reserved sectors
	uint8_t fat_num; // number of FATs
	uint16_t root_entries; // number of rood directory entries
	uint16_t sec_num_16; // number of sectors
	uint8_t media_desc; // Media Descriptor Type
	uint16_t secs_per_fat; // Number of Sectors per FAT (FAT12/16) only
	uint16_t secs_per_track; // Num. of Sectors per track
	uint16_t heads; // number of heads
	uint32_t hidden_secs; // number of hidden sectors
	uint32_t sec_num_32; // the sector count is stored here if num_sec = 0 = 65535
	
	uint8_t extended[54]; // space for the extended Boot Record
} __attribute__((packed)) __attribute__((aligned(8)));
typedef struct _fat_BR fat_BR;

struct _fat_dir {
	uint8_t name[11]; // first 8 = name, last 3 = extension
	uint8_t attributes;
	uint8_t rsv0; 
	uint8_t creation_100th;
	uint16_t creation_time;
	uint16_t creation_date;
	uint16_t last_access_date;
	uint16_t cluster_high; // high 16 bits for the entry's next cluster
	uint16_t last_mod_date;
	uint16_t last_mod_time;
	uint16_t cluster_low; // low 16 bits for the entry's next cluster
	uint32_t filesize;
} __attribute__((packed));
typedef struct _fat_dir fat_dir;

struct _fat_lfn {
	uint8_t order; // where the long file name appears
	uint16_t chars0[5]; // the first five two byte characters (65 00 66 00 etc...)
	uint8_t attribute; // always 0x0F to indicate a long file name
	uint8_t long_entry_type; // long entry type (0 = name entry)
	uint8_t checksum; 
	uint16_t chars1[6];
	uint8_t rsv0;
	uint16_t chars2[2];
} __attribute__((packed));
typedef struct _fat_lfn fat_lfn;

fat_BR boot_fat;
fat32_ext_BR* fat32_ext;
uint32_t total_sectors = 0;
uint32_t fat_size = 0;
uint32_t root_dir_secs = 0;
uint32_t first_data_sec = 0;
uint32_t first_fat_sec = 0;
uint32_t data_secs = 0;
uint32_t total_clusters = 0;
uint32_t partition_lba = 0;

void fat32_init();

inline uint32_t get_cluster_sec(int clusternr) {
	return ((clusternr - 2) * boot_fat.secs_per_cluster) + first_data_sec;
}

#endif
