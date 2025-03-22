#ifndef __DRVS_AHCI_HEADER__
#define __DRVS_AHCI_HEADER__

#include  <stdint.h>

// SATA signatures
#define SATA_SIG_ATA	0x00000101	// SATA drive
#define SATA_SIG_ATAPI	0xEB140101	// SATAPI drive
#define SATA_SIG_SEMB	0xC33C0101	// Enclosure management bridge
#define SATA_SIG_PM 	0x96690101	// Port multiplier

#define AHCI_DEV_NULL 	0
#define AHCI_DEV_SATA 	1
#define AHCI_DEV_SEMB 	2
#define AHCI_DEV_PM 	3
#define AHCI_DEV_SATAPI 4

#define HBA_PORT_IPM_ACTIVE 	1
#define HBA_PORT_DET_PRESENT 	3

typedef enum {
	FIS_TYPE_REG_H2D	= 0x27,	// Register FIS - host to device
	FIS_TYPE_REG_D2H	= 0x34,	// Register FIS - device to host
	FIS_TYPE_DMA_ACT	= 0x39,	// DMA activate FIS - device to host
	FIS_TYPE_DMA_SETUP	= 0x41,	// DMA setup FIS - bidirectional
	FIS_TYPE_DATA		= 0x46,	// Data FIS - bidirectional
	FIS_TYPE_BIST		= 0x58,	// BIST activate FIS - bidirectional
	FIS_TYPE_PIO_SETUP	= 0x5F,	// PIO setup FIS - device to host
	FIS_TYPE_DEV_BITS	= 0xA1,	// Set device bits FIS - device to host
} FIS_TYPE;

// Used to send commands to the device
struct _FIS_REG_H2D {
	uint8_t fis_type;
	
	uint8_t portm	: 4; // Port multiplier
	uint8_t rsv0	: 3; // reserved
	uint8_t comctrl	: 1; // 1 = Command, 0 = Control

	uint8_t command; // command register
	uint8_t feature_low; // feature register 7:0
	
	uint8_t lba0; // LBA registers 7:0
	uint8_t lba1; // 15:8
	uint8_t lba2; // 23:16
	uint8_t device; // device register
	
	uint8_t lba3; // LBA 31:24
	uint8_t lba4; // LBA 39:32
	uint8_t lba5; // LBA 47:40
	uint8_t feature_high; // feature register 15:8

	uint8_t count_low; // 7:0
	uint8_t count_high; // 15:8
	uint8_t icc; // isochronous command completion
	uint8_t control; // control register
	
	uint8_t rsv1[4]; // reserved
} __attribute__((packed));
typedef struct _FIS_REG_H2D FIS_REG_H2D;

// Used to receive notifications from the device
struct _FIS_REG_D2H {
	uint8_t fis_type;

	uint8_t portm	: 4; // Port multiplier
	uint8_t rsv0	: 2; // reserved
	uint8_t interrupt : 1; // interrupt bit
	uint8_t rsv1	: 1; // reserved

	uint8_t status; // status register
	uint8_t error; // error register
	
	uint8_t lba0; // LBA registers 7:0
	uint8_t lba1; // 15:8
	uint8_t lba2; // 23:16
	uint8_t device; // device register
	
	uint8_t lba3; // LBA 31:24
	uint8_t lba4; // LBA 39:32
	uint8_t lba5; // LBA 47:40
	uint8_t rsv2; // reserved

	uint8_t count_low; // 7:0
	uint8_t count_high; // 15:8
	uint8_t rsv3[2];

	uint8_t rsv4[4]; // reserved
} __attribute__((packed));
typedef struct _FIS_REG_D2H FIS_REG_D2H;

struct _FIS_DATA {
	uint8_t fis_type;

	uint8_t portm	: 4; // Port multiplier
	uint8_t rsv0	: 4; // reserved

	uint8_t rsv1[2];

	uint32_t data; // payload
} __attribute__((packed));
typedef struct _FIS_DATA FIS_DATA;

struct _FIS_PIO_SETUP {
	uint8_t fis_type;

	uint8_t portm	: 4; // Port multiplier
	uint8_t rsv0	: 1; // reserved
	uint8_t direction : 1; // data direction: 1 = device to host
	uint8_t interrupt : 1; // interrupt bit
	uint8_t rsv1	: 1; // reserved

	uint8_t status; // status register
	uint8_t error; // error register
	
	uint8_t lba0; // LBA registers 7:0
	uint8_t lba1; // 15:8
	uint8_t lba2; // 23:16
	uint8_t device; // device register
	
	uint8_t lba3; // LBA 31:24
	uint8_t lba4; // LBA 39:32
	uint8_t lba5; // LBA 47:40
	uint8_t rsv2; // reserved

	uint8_t count_low; // 7:0
	uint8_t count_high; // 15:8
	uint8_t rsv3;
	uint8_t e_status; // new value of the status register
	
	uint16_t tcount; // transfer count
	uint8_t rsv4[2]; // reserved
} __attribute__((packed));
typedef struct _FIS_PIO_SETUP FIS_PIO_SETUP;

struct _FIS_DMA_SETUP {
	uint8_t fis_type;

	uint8_t portm	: 4; // Port multiplier
	uint8_t rsv0	: 1;
	uint8_t direction : 1; // data direction
	uint8_t interrupt : 1; // interrupt
	uint8_t autoact	: 1; // auto activate - specifies if DMA activate FIS is needed
	
	uint8_t rsv1[2];
	
	uint64_t DMA_buffer_ID;

	uint32_t rsv2;

	uint32_t buffer_offset; // first two bytes need to be 0
	
	uint32_t transfer_count; // amount of bytes to transfer (bit 0 = 0)
	
	uint32_t rsv3;

} __attribute__((packed));
typedef struct _FIS_DMA_SETUP FIS_DMA_SETUP;

struct _HBA_PORT { /* volatile! */
	uint32_t cl_base;	// command list base address
	uint32_t cl_base_u;	// command list base address upper 32
	uint32_t fis_base;	// FIS base address
	uint32_t fis_base_u;	// FIS base address upper 32
	uint32_t iaddr;		// interrupt address
	uint32_t ienable;	// interrupt enable
	uint32_t cmstat;	// command and status
	uint32_t rsv0;		// reserved
	uint32_t tfd;		// task file data
	uint32_t sig;		// signature
	uint32_t sata_stat;	// SATA status
	uint32_t sata_ctrl;	// SATA control
	uint32_t sata_err;	// SATA error
	uint32_t sata_act;	// SATA active
	uint32_t ci;		// command issue
	uint32_t sata_notif;	// SATA notification
	uint32_t fbs;		// FIS-based switch control
	uint32_t rsv1[11];	// reserved
	uint32_t vendor[4];	// vendor-specific info
} __attribute__((packed));
typedef struct _HBA_PORT HBA_PORT;

struct _HBA_MEM { /* volatile */
	// Generic host control
	uint32_t cap;		// capabilities
	uint32_t ghc;		// global host control
	uint32_t is;		// interrupt status
	uint32_t pi;		// port implemented
	uint32_t version;	// ...
	uint32_t ccc_ctrl;	// command completion coalescing control
	uint32_t ccc_pts;	// " " " ports
	uint32_t em_loc;	// enclosure management location
	uint32_t em_ctrl;	// enclosure management control
	uint32_t cap_ext;	// capabilities extended
	uint32_t bohcs;		// bios os handoff control and status

	uint8_t rsv0[0x74];	// reserved
	
	uint8_t vendor[0x60];	// vendor-specific registers
	
	HBA_PORT ports[16];	// just 16 ports for now (up to 32)
} __attribute__((packed));
typedef struct _HBA_MEM HBA_MEM;

struct _HBA_FIS { /* volatile */
	FIS_DMA_SETUP dsfis; // DMA setup FIS
	uint8_t pad0[4];

	FIS_PIO_SETUP psfis; // PIO setup FIS
	uint8_t pad1[12];
	
	FIS_REG_D2H rfis; // register - device to host FIS 
	uint8_t pad2[4];

	uint8_t sdbfis[2]; // set device bits FIS
	
	uint8_t ufis[64]; 

	uint8_t rsv[0x60]; // reserved
} __attribute__((packed));
typedef struct _HBA_FIS HBA_FIS;

struct _HBA_CMD_HEADER {
	uint8_t cfis_len	: 5; // command fis length
	uint8_t atapi		: 1;
	uint8_t w_dir		: 1; // write direction 1 = H2D
	uint8_t prefetch	: 1; // prefetchable?

	uint8_t reset		: 1; 
	uint8_t bist		: 1;
	uint8_t c		: 1; // clear busy upon R_OK
	uint8_t rsv0		: 1; // reserved
	uint8_t pmp		: 4; // port multiplier port
	
	uint16_t prdtl; // physical memory descriptor of the table length (in entries)
	
	volatile uint32_t prdbc; // physical region descriptor byte count transferred
	
	uint32_t ctbl_desc_addr; // command table descriptor address
	uint32_t ctbl_desc_addr_u; // " " " " " upper 32 bits

	uint32_t rsv1[4]; // reserved
} __attribute__((packed));
typedef struct _HBA_CMD_HEADER HBA_CMD_HEADER;

struct _HBA_PRDT_ENTRY {
	uint32_t data_base; // data base address
	uint32_t data_baseu; // data base address upper 32 bits
	uint32_t rsv0; // reserved
	
	uint32_t dbc	: 22; // byte count (max 4M)
	uint32_t rsv1	: 9; // reserved
	uint32_t i	: 1; // interrupt on completion?
} __attribute__((packed));
typedef struct _HBA_PRDT_ENTRY HBA_PRDT_ENTRY;

struct _HBA_CMD_TBL {
	uint8_t cfis[64]; // command fis
	
	uint8_t acmd[16]; // ATAPI command (12 - 16 bytes) 

	uint8_t rsv[48]; // reserved
	
	HBA_PRDT_ENTRY prdt_entry[1]; // Physical region description table entries (0 - 65535)
} __attribute__((packed));
typedef struct _HBA_CMD_TBL HBA_CMD_TBL;

void ahci_probe_port(volatile HBA_MEM*);
int ahci_check_dev_type(volatile HBA_PORT*);

#endif
