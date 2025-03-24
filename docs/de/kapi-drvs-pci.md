# 02.05 drvs/PCI.h
Diese Header-Datei stellt Funktionen zur Verfügung, um mit dem PCI-Bus zu arbeiten. Derzeit unterstützt sie nur das Finden von SATA-Geräten.

## Mitglieder
### PCI_CONFIG_ADDR
```c
#define PCI_CONFIG_ADDR 0xCF8
```
- Zweck: Die Geräteadresse, die verwendet wird, um den PCI-Bus zu konfigurieren

### PCI_CONFIG_DATA
```c
#define PCI_CONFIG_DATA 0xCFC
```
- Zweck: Die Geräteadresse, die verwendet wird, um Daten vom PCI-Bus zu empfangen

### uint32_t pci_get_addr(uint8_t, uint8_t, uint8_t, uint8_t)
```c
uint32_t pci_get_addr(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset)
```
- Zweck: Erstellt eine Adresse für den PCI-Bus, um Daten zu laden oder zu speichern
- Parameter:
    - ```uint8_t bus```: Die Busnummer
    - ```uint8_t slot```: Die Slotnummer auf diesem Bus
    - ```uint8_t func```: Die Funktionsnummer für Multifunktionsgeräte
    - ```uint8_t offset```: Der Offset von der Basisadresse, die durch die oben genannten Parameter erzeugt wurde
- Rückgabewert: Eine PCI-Bus-Adresse

### uint16_t pci_read_word(uint8_t, uint8_t, uint8_t, uint8_t)
```c
uint16_t pci_read_word(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset)
```
- Zweck: Liest ein Wort vom angegebenen PCI-Gerät
- Parameter:
    - ```uint8_t bus```: Die Busnummer
    - ```uint8_t slot```: Die Slotnummer auf diesem Bus
    - ```uint8_t func```: Die Funktionsnummer für Multifunktionsgeräte
    - ```uint8_t offset```: Der Offset von der Basisadresse, die durch die oben genannten Parameter erzeugt wurde
- Rückgabewert: Das empfangene 16-Bit-Wort

### uint8_t pci_read_byte(uint8_t, uint8_t, uint8_t, uint8_t)
```c
uint8_t pci_read_byte(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset)
```
- Zweck: Liest ein Byte vom angegebenen PCI-Gerät
- Parameter:
    - ```uint8_t bus```: Die Busnummer
    - ```uint8_t slot```: Die Slotnummer auf diesem Bus
    - ```uint8_t func```: Die Funktionsnummer für Multifunktionsgeräte
    - ```uint8_t offset```: Der Offset von der Basisadresse, die durch die oben genannten Parameter erzeugt wurde
- Rückgabewert: Das empfangene Byte

### uint32_t pci_read_dw(uint8_t, uint8_t, uint8_t, uint8_t)
```c
uint32_t pci_read_dw(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset)
```
- Zweck: Liest ein Doppelwort vom angegebenen PCI-Gerät
- Parameter:
    - ```uint8_t bus```: Die Busnummer
    - ```uint8_t slot```: Die Slotnummer auf diesem Bus
    - ```uint8_t func```: Die Funktionsnummer für Multifunktionsgeräte
    - ```uint8_t offset```: Der Offset von der Basisadresse, die durch die oben genannten Parameter erzeugt wurde
- Rückgabewert: Das empfangene Doppelwort

### uint8_t pci_valid_dev(uint8_t, uint8_t)
```c
uint8_t pci_valid_dev(uint8_t bus, uint8_t dev)
```
- Zweck: Überprüft, ob ein Gerät gültig ist und gibt seine Funktionen zurück
- Parameter:
    - ```uint8_t``` bus: Die Busnummer
    - ```uint8_t dev```: Das zu überprüfende Gerät
- Rückgabewert: 0, wenn das Gerät ungültig ist; wenn das Gerät gültig ist, hat es 1 für jede Rückgabewert[valid_func]

### uint32_t pci_find_ahci()
```
uint32_t pci_find_ahci()
```
- Zweck: Sucht den PCI-Bus nach einem AHCI-Controller ab
- Parameter: Keine
- Rückgabewert: Das AHCI Base Memory Register (ABAR)