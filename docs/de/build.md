# 04 - Building Tunix
Das Erstellen von Tunix aus dem geklonten Repository kann mühsam sein, bietet jedoch zusätzliche Konfigurationsmöglichkeiten (siehe Abschnitt 04.2 - Build-Optionen).

**Disclaimer:** Der hier beschriebene Build-Prozess funktioniert nur auf UNIX-basierten Systemen. Windows- und Apple-Nutzer müssen nach Alternativen suchen.

## Voraussetzungen
Zuerst benötigen Sie einen Cross-Compiler, da TUNIX für die i686-Architektur geschrieben wurde. Dafür müssen Sie GCC und Binutils von Grund auf neu erstellen. Weitere Informationen dazu finden Sie unter https://wiki.osdev.org/GCC_Cross-Compiler.

## Build
Nachdem Sie das Repository geklont haben, müssen Sie ein 'sysroot'-Verzeichnis auf derselben Ebene wie kernel und libc erstellen. Gehen Sie dann in das libc-Verzeichnis und führen Sie ```make``` aus, gefolgt von ```make install```. Nachdem dieser Schritt abgeschlossen ist, wechseln Sie in das Verzeichnis des Kernels. Dort führen Sie ```make``` aus, gefolgt von ```sudo make img``` (Sie benötigen Sudo-Rechte, da der Image-Erstellungsprozess Loop-Geräte verwendet). Das erstellte Disk-Image befindet sich in build/disk.img.

## Ausführen
Um das Betriebssystem zu starten, verwenden Sie den folgenden Befehl: <br>
```bash
qemu-system-i386 -serial stdio -drive format=raw,id=disk,file=[PFAD ZUR DISK],if=none -device ich9-ahci,addr=06,id=ahci -device ide-hd,drive=disk,bus=ahci.0
```

Das Betriebssystem wurde nicht mit anderen Emulatoren getestet und es wird keine Garantie für die Funktionalität gegeben. Mit dieser Einrichtung wird das Betriebssystem seine Eingabe aus der Konsole beziehen, in der der Befehl ausgeführt wurde.