# 03 - KIS
KIS, was für Kernel Integrated Shell steht, ist ein einfaches Kernelmodus-Shell-Programm, das dazu dient, die OS-Funktionalität interaktiv zu testen, wenn der Benutzermodus nicht verfügbar ist. Es kommuniziert direkt mit den FAT32- und TTY-Treibern, um Ausgaben zu liefern.

## Mitglieder
KIS.h stellt die folgenden Mitglieder zur Verfügung:

### char current_cmd[128]
```c
char current_cmd[128];
```
- Zweck: Speichert den aktuellen Befehl

### size_t cmd_index
```c
size_t cmd_index;
```
- Zweck: Speichert den Index des nächsten beschreibbaren Slots in current_cmd

### KIS()
```c
void KIS();
```
- Zweck: Startet die Hauptschleife der Shell und speichert Befehle (die über die serielle Schnittstelle eingegeben werden) in current_cmd
- Parameter: Keine
- Rückgabewert: Void

### interpret()
```c
int interpret()
```
- Zweck: Interpretiert den in current_cmd gespeicherten Befehl
- Parameter: Keine
- Rückgabewert: 0, wenn die Hauptschleife fortgesetzt werden soll, 1, wenn ein Abbruch angefordert wurde

### ls()
```c
void ls()
```
- Zweck: Holt die Verzeichnisauflistung für den aktuellen Cluster
- Parameter: Keine
- Rückgabewert: Void

### isysr()
```c
void isysr();
```
- Zweck: Ruft den Interrupt 0x80 auf und übergibt die Kontrolle an den Syscall-Handler
- Parameter: Keine
- Rückgabewert: Void

### void cd()
```c
void cd();
```
- Zweck: Wechselt den aktuellen Cluster basierend auf der Benutzereingabe
- Parameter: Keine
- Rückgabewert: Void

### void cat()
```c
void cat();
```
- Zweck: Gibt den Textinhalt des aktuellen Clusters aus
- Parameter: Keine
- Rückgabewert: Void

## Befehle
Die KIS ermöglicht die Eingabe über die serielle Schnittstelle. Sie ist in der Lage, die folgenden Befehle auszuführen:
- ```cd [DIR]```: wechselt das Verzeichnis zu [DIR]
- ```ls```: listet den Inhalt des aktuellen Verzeichnisses auf
- ```cat```: listet den Textinhalt des aktuellen Verzeichnisses auf
    - Um eine Datei zu lesen: ```cd``` [DATEI] dann cat
- ```isr```: ruft den System-Interrupt-Handler auf
- ```clear```: löscht das Terminal
- ```exit```: beendet das System
