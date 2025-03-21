#ifndef __DRVS_AHCI_HEADER__
#define __DRVS_AHCI_HEADER__

#include  <stdint.h>

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
struct __FIS_REG_H2D {
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
typedef __FIS_REG_H2D FIS_REG_H2D;

// Used to receive notifications from the device
struct __FIS_REG_D2H {
	uint8_t fis_type;

	uint8_t portm	: 4; // Port multiplier
	uint8_t rsv0	: 2; // reserved
	uint8_t interrupt : 1; // interrupt bit
	uint8_t rsv1	: 1 // reserved

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
typedef __FIS_REG_D2H FIS_REG_D2H;

struct __FIS_DATA {
	uint8_t fis_type;

	uint8_t portm	: 4; // Port multiplier
	uint8_t rsv0	: 4; // reserved

	uint8_t rsv1[2];

	uint32_t data; // payload
} __attribute__((packed));
typedef __FIS_DATA FIS_DATA;

struct __FIS_PIO_SETUP {
	uint8_t fis_type;

	uint8_t portm	: 4; // Port multiplier
	uint8_t rsv0	: 1; // reserved
	uint8_t direction : 1; // data direction: 1 = device to host
	uint8_t interrupt : 1; // interrupt bit
	uint8_t rsv1	: 1 // reserved

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
typedef __FIS_PIO_SETUP FIS_PIO_SETUP;

struct __FIS_DMA_SETUP {
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
typedef __FIS_DMA_SETUP FIS_DMA_SETUP;



#endif
