# 02.06 drvs/AHCI.h
This header exposes functions for talking to AHCI devices.<br>
> [!CAUTION]
> This section is under construction. Please check the relevant code for better descriptions.
# Members
### SATA_SIG_ATA
```c
#define SATA_SIG_ATA	0x00000101	
```
- Purpose: SATA Signature for ATA type controllers
### SATA_SIG_ATAPI
```c
#define SATA_SIG_ATAPI	0xEB140101	
```
- Purpose: SATA Signature for ATAPI type controllers
### SATA_SIG_SEMB
```c
#define SATA_SIG_SEMB	0xC33C0101	
```
- Purpose: SATA Signature for SEMB type controllers
### SATA_SIG_PM
```c
#define SATA_SIG_PM 	0x96690101	
```
- Purpose: SATA Signature for PM type controllers

### AHCI_DEV_NULL
```c
#define AHCI_DEV_NULL 	0
```
- Purpose: AHCI Type for unrecognised devices 
### AHCI_DEV_SATA
```c
#define AHCI_DEV_SATA 	1
```
- Purpose: AHCI Type for SATA devices 
### AHCI_DEV_SEMB
```c
#define AHCI_DEV_SEMB 	2
```
- Purpose: AHCI Type for SEMB devices 
### AHCI_DEV_PM
```c
#define AHCI_DEV_PM 	3
```
- Purpose: AHCI Type for PM devices 
### AHCI_DEV_SATAPI
```c
#define AHCI_DEV_SATAPI 4
```
- Purpose: AHCI Type for SATAPI devices 

### HBA_PORT_IPM_ACTIVE
```c
#define HBA_PORT_IPM_ACTIVE 	1
```
- Purpose: Flag for when the Host Bus Adapter is active
### HBA_PORT_DET_PRESENT
```c
#define HBA_PORT_DET_PRESENT 	3
```
- Purpose: Flag for when the HBA is present

### AHCI_BASE
```c
#define	AHCI_BASE	0x400000
```
- Purpose: The AHCI Base Address (for memory mapped registers)

### HBA_PxCMD_ST
```c
#define HBA_PxCMD_ST    0x0001	
```
- Purpose: Flag for when the Host Bus Adapter @ Port x's command engine is started
### HBA_PxCMD_FRE	
```c
#define HBA_PxCMD_FRE   0x0010		
```
- Purpose: Flag for when the Host Bus Adapter @ Port x's command engine is accepting new Commands
### HBA_PxCMD_FR
```c
#define HBA_PxCMD_FR    0x4000	
```	
- Purpose: Flag for when the Host Bus Adapter @ Port x's command command fetcher is running
### HBA_PxCMD_CR
```c
#define HBA_PxCMD_CR    0x8000	
```	
- Purpose: Flag for when the Host Bus Adapter @ Port x's instruction reader is running

### HBA_PxIS_TFES
```c
#define HBA_PxIS_TFES	1 << 30	
```
- Purpose: Flag for when the Host Bus Adapter @ Port x encounters a task file error

### ATA_DEV_BUSY
```c
#define ATA_DEV_BUSY	0x80
```
- Purpose: Flag for when an ATA Device is busy
### ATA_DEV_DRQ
```c
#define ATA_DEV_DRQ	0x08
```
- Purpose: Flag for when an ATA Device isn't taking requests

### ATA_CMD_READ_DMA_EXT
```c
#define ATA_CMD_READ_DMA_EXT	0x25	
```
- Purpose: Read Command (using direct memory access)
### ATA_CMD_WRITE_DMA_EXT
```c
#define ATA_CMD_WRITE_DMA_EXT	0x35
```	
- Purpose: Write Command (using direct memory access)

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
- Purpose: Keeps track of all the Frame Information Structure Types

### struct FIS_REG_H2D
```c
struct _FIS_REG_H2D {
	uint8_t fis_type;
	
	uint8_t portm	: 4; 
	uint8_t rsv0	: 3; 
	uint8_t comctrl	: 1; 

	uint8_t command; 
	uint8_t feature_low; 
	
	uint8_t lba0; 
	uint8_t lba1; 
	uint8_t lba2; 
	uint8_t device; 
	
	uint8_t lba3; 
	uint8_t lba4; 
	uint8_t lba5; 
	uint8_t feature_high; 

	uint8_t count_low; 
	uint8_t count_high; 
	uint8_t icc; 
	uint8_t control; 
	
	uint8_t rsv1[4]; 
} __attribute__((packed));
typedef struct _FIS_REG_H2D FIS_REG_H2D;
```

### struct FIS_REG_D2H
```c
struct _FIS_REG_D2H {
	uint8_t fis_type;

	uint8_t portm	: 4; 
	uint8_t rsv0	: 2; 
	uint8_t interrupt : 1; 
	uint8_t rsv1	: 1; 

	uint8_t status; 
	uint8_t error; 
	
	uint8_t lba0; 
	uint8_t lba1; 
	uint8_t lba2; 
	uint8_t device; 
	
	uint8_t lba3; 
	uint8_t lba4; 
	uint8_t lba5; 
	uint8_t rsv2; 

	uint8_t count_low; 
	uint8_t count_high; 
	uint8_t rsv3[2];

	uint8_t rsv4[4]; 
} __attribute__((packed));
typedef struct _FIS_REG_D2H FIS_REG_D2H;
```

### struct FIS_DATA
```c
struct _FIS_DATA {
	uint8_t fis_type;

	uint8_t portm	: 4; 
	uint8_t rsv0	: 4; 

	uint8_t rsv1[2];

	uint32_t data; 
} __attribute__((packed));
typedef struct _FIS_DATA FIS_DATA;
```

### struct FIS_PIO_SETUP
``` c
struct _FIS_PIO_SETUP {
	uint8_t fis_type;

	uint8_t portm	: 4; 
	uint8_t rsv0	: 1; 
	uint8_t direction : 1; 
	uint8_t interrupt : 1; 
	uint8_t rsv1	: 1; 

	uint8_t status; 
	uint8_t error; 
	
	uint8_t lba0; 
	uint8_t lba1; 
	uint8_t lba2; 
	uint8_t device; 
	
	uint8_t lba3; 
	uint8_t lba4; 
	uint8_t lba5; 
	uint8_t rsv2; 

	uint8_t count_low; 
	uint8_t count_high; 
	uint8_t rsv3;
	uint8_t e_status; 
	
	uint16_t tcount; 
	uint8_t rsv4[2]; 
} __attribute__((packed));
typedef struct _FIS_PIO_SETUP FIS_PIO_SETUP;
```

### struct FIS_DMA_SETUP
```c
struct _FIS_DMA_SETUP {
	uint8_t fis_type;

	uint8_t portm	: 4; 
	uint8_t rsv0	: 1;
	uint8_t direction : 1; 
	uint8_t interrupt : 1; 
	uint8_t autoact	: 1; 
	
	uint8_t rsv1[2];
	
	uint64_t DMA_buffer_ID;

	uint32_t rsv2;

	uint32_t buffer_offset; 
	
	uint32_t transfer_count; 
	
	uint32_t rsv3;

} __attribute__((packed));
typedef struct _FIS_DMA_SETUP FIS_DMA_SETUP;
```

### struct HBA_PORT
```c
struct _HBA_PORT { /* volatile! */
	uint32_t cl_base;	
	uint32_t cl_base_u;	
	uint32_t fis_base;	
	uint32_t fis_base_u;	
	uint32_t istat;		
	uint32_t ienable;	
	uint32_t cmstat;	
	uint32_t rsv0;		
	uint32_t tfd;		
	uint32_t sig;		
	uint32_t sata_stat;	
	uint32_t sata_ctrl;	
	uint32_t sata_err;	
	uint32_t sata_act;	
	uint32_t ci;		
	uint32_t sata_notif;	
	uint32_t fbs;		
	uint32_t rsv1[11];	
	uint32_t vendor[4];	
} __attribute__((packed));
typedef struct _HBA_PORT HBA_PORT;
```

### struct HBA_MEM
```
struct _HBA_MEM { /* volatile */
	
	uint32_t cap;		
	uint32_t ghc;		
	uint32_t is;		
	uint32_t pi;		
	uint32_t version;	
	uint32_t ccc_ctrl;	
	uint32_t ccc_pts;	
	uint32_t em_loc;	
	uint32_t em_ctrl;	
	uint32_t cap_ext;	
	uint32_t bohcs;		

	uint8_t rsv0[0x74];	
	
	uint8_t vendor[0x60];	
	
	HBA_PORT ports[32];	
} __attribute__((packed));
typedef struct _HBA_MEM HBA_MEM;
```

### struct HBA_FIS
```c
struct _HBA_FIS { /* volatile */
	FIS_DMA_SETUP dsfis; 
	uint8_t pad0[4];

	FIS_PIO_SETUP psfis; 
	uint8_t pad1[12];
	
	FIS_REG_D2H rfis; 
	uint8_t pad2[4];

	uint8_t sdbfis[2]; 
	
	uint8_t ufis[64]; 

	uint8_t rsv[0x60]; 
} __attribute__((packed));
typedef struct _HBA_FIS HBA_FIS;
```

### struct HBA_CMD_HEADER
```c
struct _HBA_CMD_HEADER {
	uint8_t cfis_len	: 5; 
	uint8_t atapi		: 1;
	uint8_t w_dir		: 1; 
	uint8_t prefetch	: 1; 

	uint8_t reset		: 1; 
	uint8_t bist		: 1;
	uint8_t c		: 1; 
	uint8_t rsv0		: 1; 
	uint8_t pmp		: 4; 
	
	uint16_t prdtl; 
	
	volatile uint32_t prdbc; 
	
	uint32_t ctbl_desc_addr; 
	uint32_t ctbl_desc_addr_u; 

	uint32_t rsv1[4]; 
} __attribute__((packed));
typedef struct _HBA_CMD_HEADER HBA_CMD_HEADER;
```

### struct HBA_PRDT_ENTRY
```c
struct _HBA_PRDT_ENTRY {
	uint32_t data_base; 
	uint32_t data_base_u; 
	uint32_t rsv0; 
	
	uint32_t dbc	: 22; 
	uint32_t rsv1	: 9; 
	uint32_t i	: 1; 
} __attribute__((packed));
typedef struct _HBA_PRDT_ENTRY HBA_PRDT_ENTRY;
```

### struct HBA_CMD_TBL
```c
struct _HBA_CMD_TBL {
	uint8_t cfis[64]; 
	
	uint8_t acmd[16]; 

	uint8_t rsv[48]; 
	
	HBA_PRDT_ENTRY prdt_entry[8]; 
} __attribute__((packed));
typedef struct _HBA_CMD_TBL HBA_CMD_TBL;
```

### HBA_PORT* master_dev
```c
volatile HBA_PORT* master_dev
```
- Purpose: Keeps track of the main AHCI device (hard disk)

### void ahci_probe_port(volatile HBA_MEM*);
```c
void ahci_probe_port(volatile HBA_MEM* abar)
```
### int ahci_check_dev_type(volatile HBA_PORT*);
```c
int ahci_check_dev_type(volatile HBA_PORT* port)
```
### void ahci_port_rebase(volatile HBA_PORT*, int);
```c
void ahci_port_rebase(volatile HBA_PORT* port, int portnr)
```
### void ahci_start_cmd(volatile HBA_PORT*);
```c
void ahci_start_cmd(volatile HBA_PORT* port)
```
### void ahci_stop_cmd(volatile HBA_PORT*);
```c
void ahci_stop_cmd(volatile HBA_PORT* port)
```
### int ahci_find_cmdslot(volatile HBA_PORT*);
```c
int ahci_find_cmdslot(volatile HBA_PORT* port)
```
### bool ahci_read_sectors(volatile HBA_PORT*, uint32_t, uint32_t, uint32_t, uint16_t*);
```c
bool ahci_read_sectors(volatile HBA_PORT* port, uint32_t startl, uint32_t starth, uint32_t count, uint16_t* buf)
```
### bool ahci_write_sectors(volatile HBA_PORT*, uint32_t, uint32_t, uint32_t, uint16_t*);
```c
bool ahci_write_sectors(volatile HBA_PORT* port, uint32_t startl, uint32_t starth, uint32_t count, uint16_t* buf)
```