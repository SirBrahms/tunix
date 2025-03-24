# 02.06 drvs/AHCI.h
Diese Header-Datei stellt Funktionen zur Verfügung, um mit AHCI-Geräten zu kommunizieren.<br>
> [!CAUTION]
> Dieser Abschnitt befindet sich noch im Aufbau. Bitte überprüfe den relevanten Code für genauere Beschreibungen.

# Mitglieder
### SATA_SIG_ATA
```c
#define SATA_SIG_ATA	0x00000101	
```
- Zweck: SATA-Signatur für ATA-Typ-Controller

### SATA_SIG_ATAPI
```c
#define SATA_SIG_ATAPI	0xEB140101	
```
- Zweck: SATA-Signatur für ATAPI-Typ-Controller

### SATA_SIG_SEMB
```c
#define SATA_SIG_SEMB	0xC33C0101	
```
- Zweck: SATA-Signatur für SEMB-Typ-Controller

### SATA_SIG_PM
```c
#define SATA_SIG_PM 	0x96690101	
```
- Zweck: SATA-Signatur für PM-Typ-Controller

### AHCI_DEV_NULL
```c
#define AHCI_DEV_NULL 	0
```
- Zweck: AHCI-Typ für nicht erkannte Geräte

### AHCI_DEV_SATA
```c
#define AHCI_DEV_SATA 	1
```
- Zweck: AHCI-Typ für SATA-Geräte

### AHCI_DEV_SEMB
```c
#define AHCI_DEV_SEMB 	2
```
- Zweck: AHCI-Typ für SEMB-Geräte

### AHCI_DEV_PM
```c
#define AHCI_DEV_PM 	3
```
- Zweck: AHCI-Typ für PM-Geräte

### AHCI_DEV_SATAPI
```c
#define AHCI_DEV_SATAPI 4
```c
- Zweck: AHCI-Typ für SATAPI-Geräte

### HBA_PORT_IPM_ACTIVE
```c
#define HBA_PORT_IPM_ACTIVE 	1
```
- Zweck: Flag, wenn der Host-Bus-Adapter aktiv ist

### HBA_PORT_DET_PRESENT
```c
#define HBA_PORT_DET_PRESENT 	3
```
- Zweck: Flag, wenn der HBA vorhanden ist

### AHCI_BASE
```c
#define	AHCI_BASE	0x400000
```
- Zweck: Die AHCI-Basisadresse (für RAM-gemappte Register)

### HBA_PxCMD_ST
```c
#define HBA_PxCMD_ST    0x0001	
```
- Zweck: Flag, wenn der Befehl des Host-Bus-Adapters @ Port x gestartet wurde

### HBA_PxCMD_FRE	
```c
#define HBA_PxCMD_FRE   0x0010	
```	
- Zweck: Flag, wenn der Befehl des Host-Bus-Adapters @ Port x neue Befehle akzeptiert

### HBA_PxCMD_FR
```c
#define HBA_PxCMD_FR    0x4000	
```
- Zweck: Flag, wenn der Befehlsabruf des Host-Bus-Adapters @ Port x läuft

### HBA_PxCMD_CR
```c
#define HBA_PxCMD_CR    0x8000	
```
- Zweck: Flag, wenn der Befehlsleser des Host-Bus-Adapters @ Port x läuft

### HBA_PxIS_TFES
```c
#define HBA_PxIS_TFES	1 << 30	
```
- Zweck: Flag, wenn der Host-Bus-Adapter @ Port x einen Task-File-Fehler hat

### ATA_DEV_BUSY
```c
#define ATA_DEV_BUSY	0x80
```
- Zweck: Flag, wenn ein ATA-Gerät beschäftigt ist

### ATA_DEV_DRQ
```c
#define ATA_DEV_DRQ	0x08
```
- Zweck: Flag, wenn ein ATA-Gerät keine Anfragen entgegennimmt

### ATA_CMD_READ_DMA_EXT
```c
#define ATA_CMD_READ_DMA_EXT	0x25	
```
- Zweck: Lese-Befehl (unter Verwendung von Direct Memory Access)

### ATA_CMD_WRITE_DMA_EXT
```c
#define ATA_CMD_WRITE_DMA_EXT	0x35
```
- Zweck: Schreib-Befehl (unter Verwendung von Direct Memory Access)

### enum FIS_TYPE
```c
typedef enum {
	FIS_TYPE_REG_H2D	= 0x27,	
	FIS_TYPE_REG_D2H	= 0x34,	
	FIS_TYPE_DMA_ACT	= 0x39,	
	FIS_TYPE_DMA_SETUP	= 0x41,	
	FIS_TYPE_DATA		= 0x46,	
	FIS_TYPE_BIST		= 0x58,	
	FIS_TYPE_PIO_SETUP	= 0x5F,	
	FIS_TYPE_DEV_BITS	= 0xA1,	
} FIS_TYPE;
```