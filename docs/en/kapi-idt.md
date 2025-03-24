# 02.03 - IDT.h
This header describes the functions and structures neccessary for setting up an IDT.
## Members
### struct IDT_entry
```c
struct _IDT_entry {
	uint16_t offset_low;        	
   	uint16_t selector;        	
   	uint8_t  zero;            	
   	uint8_t  type_attributes; 	
   	uint16_t offset_high;        	
} __attribute__((packed));
typedef struct _IDT_entry IDT_entry;
```
- Purpose: This structure describes a singular Interrupt Gate
- Members:
    - ```uint16_t offset_low```: The low 16 bits of the Handler Function Address
   	- ```uint16_t selector```: A code segment selector in the GDT or LDT
   	- ```uint8_t  zero```: Reserved, set to 0
   	- ```uint8_t  type_attributes```: One Field containing Gate Type, DPL and P
   	- ```uint16_t offset_high```: The high 16 bit of the Handler Function Address
### struct IDTR
```c
struct _idtr {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed));
typedef struct _idtr IDTR;
```
- Purpose: This struct is loaded using the ```lidt``` instruction and points to the list of IDT entries
- Members:
    - ```uint16_t limit```: The size of the IDT entry list
	- ```uint32_t base```: The base address of the IDT entry list
### IDT_entry IDT[256]
```c
__attribute__((aligned(8))) IDT_entry IDT[256];
```
- Purpose: Array that contains all IDT entries, the previously mentioned Entry List
### IDTR iptr;
```c
__attribute__((aligned(8))) IDTR iptr;
```
- Purpose: The general IDTR struct. Should not be changed outside of the ```idt_init()``` function
### void idt_entry_init(int, uint32_t, uint16_t, uint8_t)
```c
void idt_entry_init(int num, uint32_t function_offset, uint16_t seg, uint8_t flags);
```
- Purpose: Initialises one IDT entry
- Parameters:
    - ```int num```: The index into the entry list
    - ```uint32_t function offset```: The address of the function this entry should point to
    - ```uint16_t seg```: A segment selector for the GDT or LDT
    - ```uint8_t flags```: Gate Type, DPL and P Values
- Return Value: Void
### void idt_init();
```c
void idt_init();
```
- Purpose: Initialises the entire IDT
- Parameters: None
- Return Value: Void
### void load_IDT();
```c
extern void load_IDT();
```
- Purpose: Loads the IDT into the correct CPU registers
- Parameters: None
- Return Value: Void
### uint16_t csegs(uint16_t, uint8_t, uint8_t) 
```c
inline uint16_t csegs(uint16_t index, uint8_t table, uint8_t rpl) {
	return ((index & 0x1FF) << 3) + ((table & 0b1) << 2) + (rpl & 0b11);
}
```
- Purpose: Creates a segment descriptor for the GDT or LDT
- Parameters:
    - ```uint16_t index```: The index into the selcted Table
    - ```uint8_t table```: 1 = GDT, 0 = LDT (only 1 bit)
    - ```uint8_t rpl```: The requested privilege level (only 2 bits)
- Return Value: The segment descriptor

### inline uint8_t ciflags(uint8_t, uint8_t)
```c
inline uint8_t ciflags(uint8_t gt, uint8_t dpl) {
	return (1 << 7) + ((dpl & 0b11) << 5) + (gt & 0b1111);
}
```
- Purpose: Creates an IDT Flag value
- Parameters:
    - ```uint8_t gt```: The Gate Type
    - ```uint8_t dpl```: The Privilege level needed to call this Gate
- Return Value: The IDT Flag byte