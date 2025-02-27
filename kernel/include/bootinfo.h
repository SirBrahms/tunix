#ifndef H_MULTIBOOT
#define H_MULTIBOOT

typedef unsigned char		mb_uint8_t;
typedef unsigned short		mb_uint16_t;
typedef unsigned int		mb_uint32_t;
typedef unsigned long long	mb_uint64_t;

typedef struct {	
	mb_uint32_t tabsize; // 28 bytes -> 32 bytes
	mb_uint32_t strsize; // 32 bytes -> 36 bytes
	mb_uint32_t addr; // 36 bytes -> 40 bytes
	mb_uint32_t __reserved; // 40 bytes -> 44 bytes
} aout_kernel_symtable_t;

typedef struct {
	mb_uint32_t num;
	mb_uint32_t size;
	mb_uint32_t addr;
	mb_uint32_t shndx;
} ELF_kernel_section_header_table_t;

typedef struct {
	mb_uint32_t flags; // 0 bytes -> 4 bytes

	mb_uint32_t mem_lower; // 4 bytes -> 8 bytes
	mb_uint32_t mem_upper; // 8 bytes -> 12 bytes

	mb_uint32_t boot_device; // 12 bytes -> 16 bytes

	mb_uint32_t cmdline; // 16 bytes -> 20 bytes
	
	mb_uint32_t mods_count; // 20 bytes -> 24 bytes
	mb_uint32_t mods_addr; // 24 bytes -> 28 bytes
	
	union {
		aout_kernel_symtable_t aout_kernel_symtable; // 28 -> 44 bytes
		ELF_kernel_section_header_table_t ELF_sechead; // ""
	} u;

	mb_uint32_t mmap_length; // 44 bytes -> 48 bytes
	mb_uint32_t mmap_addr; // 48 bytes -> 52 bytes
	
	mb_uint32_t drives_length; // 52 -> 56
	mb_uint32_t drives_addr; // 56 -> 60
	
	mb_uint32_t config_table; // 60 -> 64
	
	mb_uint32_t boot_loader_name; // 64 -> 68
	
	mb_uint32_t apm_table; // 68 -> 72
	
	mb_uint32_t vbe_control_info; // 72 -> 76
	mb_uint32_t vbe_mode_info; // 76 -> 80
	mb_uint16_t vbe_mode; // 80 -> 82
	mb_uint16_t vbe_interface_seg; // 82 -> 84
	mb_uint32_t vbe_interface_off; // 84 -> 86
	mb_uint16_t vbe_interface_len; // 86 -> 88
	
	mb_uint64_t framebuffer_addr; // 88 -> 96
	mb_uint32_t framebuffer_pitch; // 96 -> 100
	mb_uint32_t framebuffer_width; // 100 -> 104
	mb_uint32_t framebuffer_height; // 104 -> 108
	mb_uint8_t framebuffer_bpp; // 108 -> 109
	mb_uint8_t framebuffer_type; // 109 -> 110
	union {
		struct {
			mb_uint32_t framebuffer_palette_addr;
			mb_uint16_t framebuffer_palette_num_colors;
		};
		struct {
			mb_uint8_t framebuffer_red_field_position;
			mb_uint8_t framebuffer_red_mask_size;
			mb_uint8_t framebuffer_green_field_position;
			mb_uint8_t framebuffer_green_mask_size;
			mb_uint8_t framebuffer_blue_field_position;
			mb_uint8_t framebuffer_blue_mask_size;
		};
	};

} bootinfo_t;

#endif
