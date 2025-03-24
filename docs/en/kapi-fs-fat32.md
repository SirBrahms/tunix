# 02.07 - fs/FAT32.h
This header contains relevant functions and information for reading a FAT32 Filesystem. 

## Members
### fat_32_ext_BR
```c
struct _fat32_ext_BR {
	uint32_t fat_size; 
	uint16_t flags;
	uint16_t version;
	uint32_t root_cluster; 
	uint16_t fs_info_sec; 
	uint16_t backup_boot_sec; 
	uint8_t rsv0[12]; 
	uint8_t drive_nr; 
	uint8_t ntflags; 
	uint8_t signature; 
	uint32_t serial_num; 
	uint8_t volume_name[11]; 
	uint8_t system_identifier[8]; 
} __attribute__((packed));
typedef struct _fat32_ext_BR fat32_ext_BR;
```
- Purpose: The extended Boot Record for FAT32 formatted systems
- Members:
    - ```int32_t fat_size```: FAT size in sectors
	- ```uint16_t flags```: Filesystem Flags
	- ```uint16_t version```: FAT Version Number
	- ```uint32_t root_cluster```: Cluster number of the root directory
	- ```uint16_t fs_info_sec```: Sector numer of the fs_info structure
	- ```uint16_t backup_boot_sec```: Sector number of the Backup Boot Sector
	- ```uint8_t rsv0[12]```: Reserved
	- ```uint8_t drive_nr```: Drive number
	- ```uint8_t ntflags```: Flags under WindowsNT
	- ```uint8_t signature```: Signature
	- ```uint32_t serial_num```: Volume ID (serial Number)
	- ```uint8_t volume_name[11]```: Volume name string (padded with spaces)
	- ```uint8_t system_identifier[8]```: System Identifier, (padded with spaces)
### struct fat_BR
```c
struct _fat_BR {
	uint8_t bootjmp[3]; 
	uint8_t oem_id[8]; 
	uint16_t bytes_per_sec; 
	uint8_t secs_per_cluster; 
	uint16_t reserved_secs; 
	uint8_t fat_num; 
	uint16_t root_entries; 
	uint16_t sec_num_16; 
	uint8_t media_desc; 
	uint16_t secs_per_fat; 
	uint16_t secs_per_track; 
	uint16_t heads; 
	uint32_t hidden_secs; 
	uint32_t sec_num_32; 
	
	uint8_t extended[54]; 
} __attribute__((packed)) __attribute__((aligned(8)));
typedef struct _fat_BR fat_BR;
```
- Purpose: The Boot Record for FAT formatted systems
- Members:
	- ```uint8_t bootjmp[3]```: Assembly instructions to jump over the BPB
	- ```uint8_t oem_id[8]```: DOS version (padded with spaces)
	- ```uint16_t bytes_per_sec```: Number of bytes in a sector
	- ```uint8_t secs_per_cluster```: Number of sectors per cluster
	- ```uint16_t reserved_secs```: Number of reserved sectors
	- ```uint8_t fat_num```: Number of FATs
	- ```uint16_t root_entries```: Number of rood directory entries
	- ```uint16_t sec_num_16```: Number of sectors
	- ```uint8_t media_desc```: Media Descriptor Type
	- ```uint16_t secs_per_fat```: Number of Sectors per FAT (FAT12/16) only
	- ```uint16_t secs_per_track```: Number of Sectors per track (For CBS Addressing)
	- ```uint16_t heads```: Number of heads (For CBS Addressing)
	- ```uint32_t hidden_secs```: Number of hidden sectors
	- ```uint32_t sec_num_32```: FAT32 stores its sector count here
	- ```uint8_t extended[54]```: Space for the extended Boot Record

### struct fat_dir
```c
struct _fat_dir {
	uint8_t name[11]; 
	uint8_t attributes;
	uint8_t rsv0; 
	uint8_t creation_100th;
	uint16_t creation_time;
	uint16_t creation_date;
	uint16_t last_access_date;
	uint16_t cluster_high; 
	uint16_t last_mod_date;
	uint16_t last_mod_time;
	uint16_t cluster_low; 
	uint32_t filesize;
} __attribute__((packed));
typedef struct _fat_dir fat_dir;
```
- Purpose: The Structure for a FAT Directory
- Members: 	
    - ```uint8_t name[11]```: Name; First 8 characters = name, last 3 characters = extension
	- ```uint8_t attributes```: File Attributes
	- ```uint8_t rsv0```: Reserved
	- ```uint8_t creation_100th```: Creation Time in hundredths of a second
	- ```uint16_t creation_time```: Creation Time
	- ```uint16_t creation_date```: Creation Date
	- ```uint16_t last_access_date```: Last Access Date
	- ```uint16_t cluster_high```: High 16 bits for the entry's next cluster
	- ```uint16_t last_mod_date```: Last Modification Date
	- ```uint16_t last_mod_time```: Last Modification Time
	- ```uint16_t cluster_low```: Low 16 bits for the entry's next cluster
	- ```uint32_t filesize```: Filesize in bytes

### struct fat_lfn
```c
struct _fat_lfn {
	uint8_t order; 
	uint16_t chars0[5]; 
	uint8_t attribute; 
	uint8_t long_entry_type; 
	uint8_t checksum; 
	uint16_t chars1[6];
	uint8_t rsv0;
	uint16_t chars2[2];
} __attribute__((packed));
typedef struct _fat_lfn fat_lfn;
```
- Purpose: Stores FAT Long File Names
- Members:
	- ```uint8_t order```: Where the long file name appears
	- ```uint16_t chars0[5]```: The first five two byte characters (65 00 66 00 etc...)
	- ```uint8_t attribute```: Always 0x0F to indicate a long file name
	- ```uint8_t long_entry_type```: Long entry type (0 = name entry)
	- ```uint8_t checksum```: Checksum generated from Short File Name
	- ```uint16_t chars1[6]```: Next 6 two byte chars
	- ```uint8_t rsv0```: Reserved
	- ```uint16_t chars2[2]```: Last two two byte chars

### Global Variables
```c
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
uint32_t current_cluster;
uint32_t prev_cluster;
```
- Purpose: Keep Track of Position in the File System (these are all set by fat32_init)

### void fat32_init()
```c
void fat32_init();
```
- Purpose: Initialises the FAT32 driver
- Parameters: None
- Return Value: Void

### uint32_t get_cluster_sec(int clusternr)
```c
inline uint32_t get_cluster_sec(int clusternr) {
	return ((clusternr - 2) * boot_fat.secs_per_cluster) + first_data_sec + partition_lba;
}
```
- Purpose: Returns the LBA of a given Cluster Number
- Parameters:
    - ```int clusternr```: Cluster Number
- Return Value: The LBA