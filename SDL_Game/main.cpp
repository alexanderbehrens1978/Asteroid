// Listing 12.1
// C++ für Spieleprogrammierer
// Das Weltraumspiel
// 
// Als x64 Debug läuft das Programm !
// Kollision klappt nicht
// 
// Game.cpp ist wichtig
// 
//
#include "Framework.hpp"
#include "Game.hpp"



int main(int argc, char* argv[])
{
	// Framework initialisieren
	//if (g_pFramework->Init (800, 600, 16, true) == false)  // Vollbild Modus
	if(g_pFramework->Init (800, 600, 16, false) == false) // Fenster Modus
		return (0);

	// Neue Instanz des Spiels
	CGame Game;

	// Spiel initialisieren
	Game.Init();

	// Spiel laufen lassen. Diese Funktion läuft so lange,
	// bis das Spiel geschlossen oder die Escape-Taste
	// gedrückt wird
	Game.Run();

	// Spiel beenden
	Game.Quit();

	// Framework beenden
	g_pFramework->Quit();
	g_pFramework->Del();

	return (0);

}