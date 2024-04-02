Das Weltraumspiel aus C++ für Spieleprogrammierer

Das ganze gibt es auch als Linux Variante !!!


Die SDL2-devel-2.30.1-VC hab ich in das Verzeichnis kopiert
https://github.com/libsdl-org/SDL/releases
-> Siehe include\SDL.h
-> Siehe lib\x86
-> Siehe lib\x64

In der Timer.hpp steht die SDL.h drin
Dort wurde der Pfad auch angepasst
#include "..\include\SDL.h"

Aktuell geht nur die 64Bit Version

Game.cpp ist wichtig !

TODO:
- Kollision geht nicht
- Punktestand anzeigen
- Computergegner
- Musik im Hintergrund
- Sound beim abgeben eines Schusses
- Highscore Liste
- Alle Klasse und Dateinamen anpassen
