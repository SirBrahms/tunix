# 02.07 - fs/FAT32.h
Dieser Header enthält relevante Funktionen und Informationen zum Lesen eines FAT32-Dateisystems.

## Mitglieder
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
typedef struct _fat32_ext_BR fat32_ext_BR
```
- Zweck: Das erweiterte Boot-Record für FAT32-formatierte Systeme
- Mitglieder:
    - ```fat_size```: FAT-Größe in Sektoren
    - ```flags```: Dateisystem-Flags
    - ```version```: FAT Versionsnummer
    - ```root_cluster```: Cluster-Nummer des Root-Verzeichnisses
    - ```fs_info_sec```: Sektor-Nummer der fs_info-Struktur
    - ```backup_boot_sec```: Sektor-Nummer des Backup-Boot-Sektors
    - ```rsv0```: Reserviert
    - ```drive_nr```: Laufwerksnummer
    - ```ntflags```: Flags unter WindowsNT
    - ```signature```: Signatur
    - ```serial_num```: Volumen-ID (Seriennummer)
    - ```volume_name```: Volumenname-String (mit Leerzeichen aufgefüllt)
    - ```system_identifier```: Systembezeichner (mit Leerzeichen aufgefüllt)

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
typedef struct _fat_BR fat_BR
```
- Zweck: Das Boot-Record für FAT-formatierte Systeme
- Mitglieder:
    - ```bootjmp```: Assembly-Instruktionen zum Überspringen des BPB
    - ```oem_id```: DOS-Version (mit Leerzeichen aufgefüllt)
    - ```bytes_per_sec```: Anzahl der Bytes pro Sektor
    - ```secs_per_cluster```: Anzahl der Sektoren pro Cluster
    - ```reserved_secs```: Anzahl der reservierten Sektoren
    - ```fat_num```: Anzahl der FATs
    - ```root_entries```: Anzahl der Einträge im Root-Verzeichnis
    - ```sec_num_16```: Anzahl der Sektoren
    - ```media_desc```: Medientyp
    - ```secs_per_fat```: Anzahl der Sektoren pro FAT (nur FAT12/16)
    - ```secs_per_track```: Anzahl der Sektoren pro Spur (für CBS-Adressierung)
    - ```heads```: Anzahl der Köpfe (für CBS-Adressierung)
    - ```hidden_secs```: Anzahl der versteckten Sektoren
    - ```sec_num_32```: FAT32 speichert hier die Sektoranzahl
    - ```extended```: Platz für das erweiterte Boot-Record

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
typedef struct _fat_dir fat_dir
```
- Zweck: Die Struktur für ein FAT-Verzeichnis
- Mitglieder:
    - ```name```: Name; Erste 8 Zeichen = Name, die letzten 3 Zeichen = Erweiterung
    - ```attributes```: Dateiattribute
    - ```rsv0```: Reserviert
    - ```creation_100th```: Erstellungszeit in Hundertstelsekunden
    - ```creation_time```: Erstellungszeit
    - ```creation_date```: Erstellungsdatum
    - ```last_access_date```: Datum des letzten Zugriffs
    - ```cluster_high```: Hohe 16 Bits für den nächsten Cluster des Eintrags
    - ```last_mod_date```: Datum der letzten Änderung
    - ```last_mod_time```: Uhrzeit der letzten Änderung
    - ```cluster_low```: Niedrige 16 Bits für den nächsten Cluster des Eintrags
    - ```filesize```: Dateigröße in Bytes

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
typedef struct _fat_lfn fat_lfn
```
- Zweck: Speichert lange Dateinamen im FAT-Format
- Mitglieder:
    - ```order```: Position, an der der lange Dateiname erscheint
    - ```chars0```: Die ersten fünf zwei-Byte-Zeichen (65 00 66 00 usw.)
    - ```attribute```: Immer 0x0F, um einen langen Dateinamen zu kennzeichnen
    - ```long_entry_type```: Langer Eintragstyp (0 = Nameeintrag)
    - ```checksum```: Prüfziffer, die aus dem kurzen Dateinamen erzeugt wird
    - ```chars1```: Die nächsten sechs zwei-Byte-Zeichen
    - ```rsv0```: Reserviert
    - ```chars2```: Die letzten zwei zwei-Byte-Zeichen

### Globale Variablen
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
- Zweck: Verfolgt die Position im Dateisystem (diese werden alle von fat32_init gesetzt)

### void fat32_init()
```c
void fat32_init();
```
- Zweck: Initialisiert den FAT32-Treiber
- Parameter: Keine
- Rückgabewert: Void

### uint32_t get_cluster_sec(int clusternr)
```c
inline uint32_t get_cluster_sec(int clusternr) {
	return ((clusternr - 2) * boot_fat.secs_per_cluster) + first_data_sec + partition_lba;
}
```
- Zweck: Gibt die LBA eines bestimmten Cluster-Nummer zurück
- Parameter:
    - ```clusternr```: Cluster-Nummer
- Rückgabewert: Die LBA
