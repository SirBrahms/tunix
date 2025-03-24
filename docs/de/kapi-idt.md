# 02.03 - IDT.h
Dieses Header-File beschreibt die Funktionen und Strukturen, die für die Einrichtung eines Interrupt Descriptor Table (IDT) erforderlich sind.

## Mitglieder
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
- **Zweck**: Diese Struktur beschreibt ein einzelnes Interrupt-Gate  
- **Mitglieder**:  
    - `uint16_t offset_low`: Die unteren 16 Bits der Handler-Funktionsadresse  
    - `uint16_t selector`: Ein Code-Segment-Selektor in der GDT oder LDT  
    - `uint8_t zero`: Reserviert, auf 0 gesetzt  
    - `uint8_t type_attributes`: Enthält Gate-Typ, DPL und P  
    - `uint16_t offset_high`: Die oberen 16 Bits der Handler-Funktionsadresse  

### struct IDTR
```c
struct _idtr {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed));
typedef struct _idtr IDTR;
```
- **Zweck**: Diese Struktur wird mit der `lidt`-Instruktion geladen und verweist auf die Liste der IDT-Einträge  
- **Mitglieder**:  
    - `uint16_t limit`: Die Größe der IDT-Eintragsliste  
    - `uint32_t base`: Die Basisadresse der IDT-Eintragsliste  

### IDT_entry IDT[256]
```c
__attribute__((aligned(8))) IDT_entry IDT[256];
```
- **Zweck**: Array, das alle IDT-Einträge enthält  

### IDTR iptr;
```c
__attribute__((aligned(8))) IDTR iptr;
```
- **Zweck**: Allgemeine IDTR-Struktur. Sollte außerhalb der `idt_init()`-Funktion nicht verändert werden  

### void idt_entry_init(int, uint32_t, uint16_t, uint8_t)
```c
void idt_entry_init(int num, uint32_t function_offset, uint16_t seg, uint8_t flags);
```
- **Zweck**: Initialisiert einen einzelnen IDT-Eintrag  
- **Parameter**:  
    - `int num`: Der Index in der Eintragsliste  
    - `uint32_t function_offset`: Die Adresse der Funktion, auf die dieser Eintrag zeigen soll  
    - `uint16_t seg`: Ein Segment-Selektor für die GDT oder LDT  
    - `uint8_t flags`: Gate-Typ, DPL und P-Werte  
- **Rückgabewert**: Void  

### void idt_init();
```c
void idt_init();
```
- **Zweck**: Initialisiert die gesamte IDT  
- **Parameter**: Keine  
- **Rückgabewert**: Void  

### void load_IDT();
```c
extern void load_IDT();
```
- **Zweck**: Lädt die IDT in die entsprechenden CPU-Register  
- **Parameter**: Keine  
- **Rückgabewert**: Void  

### uint16_t csegs(uint16_t, uint8_t, uint8_t) 
```c
inline uint16_t csegs(uint16_t index, uint8_t table, uint8_t rpl) {
	return ((index & 0x1FF) << 3) + ((table & 0b1) << 2) + (rpl & 0b11);
}
```
- **Zweck**: Erstellt einen Segment-Deskriptor für die GDT oder LDT  
- **Parameter**:  
    - `uint16_t index`: Der Index in der ausgewählten Tabelle  
    - `uint8_t table`: 1 = GDT, 0 = LDT (nur 1 Bit)  
    - `uint8_t rpl`: Das gewünschte Privileg-Level (nur 2 Bits)  
- **Rückgabewert**: Der Segment-Deskriptor  

### inline uint8_t ciflags(uint8_t, uint8_t)
```c
inline uint8_t ciflags(uint8_t gt, uint8_t dpl) {
	return (1 << 7) + ((dpl & 0b11) << 5) + (gt & 0b1111);
}
```
- **Zweck**: Erstellt einen IDT-Flag-Wert  
- **Parameter**:  
    - `uint8_t gt`: Der Gate-Typ  
    - `uint8_t dpl`: Das Privileg-Level, das benötigt wird, um dieses Gate aufzurufen  
- **Rückgabewert**: Das IDT-Flag-Byte  