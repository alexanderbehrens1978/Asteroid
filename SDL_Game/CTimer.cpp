//********************************************************************
//*                                                                  *
//*                  K l a s s e   CTimer                            *
//*                                                                  *
//********************************************************************
//*                                                                  *
//*                  Dateiname     CTimer.cpp                        *
//*                                                                  *
//********************************************************************
//*                                                                  *
//* Aufgabe:                                                         *
//*          Jedes Spiel braucht einen Zeitgeber, sei es f�r die     *
//*          sanfte Bewegung von Objekte, f�r die Spielzeit oder     *
//*          das Ausl�sen bestimmter Ereignisse. Diese Klasse hat    *
//*          die Aufgabe, die Zeit zu messen, die ein kompletter     *
//*          Durchlauf der Spielschleife ben�tigt. Diese Zeit        *
//*          wird in Sekunden gemessen und kann �ber eine            *
//*          entsprechende Memberfunktion ermittelt werden.          *
//*                                                                  *
//********************************************************************
//
// Timer.cpp
#include "CTimer.hpp"
//
// Konstruktor
//
// Aufgabe: Initialisierung
//
CTimer::CTimer()
{
	// Initialisierung
	m_fCurTime = 0.0f;
	m_fLastTime = SDL_GetTicks() / 1000.0f;
	m_fElapsed = 0.0f;

}

// Update
//
// Aufgabe: Timer updaten
//
void CTimer::Update()
{
	// Vergangene Zeit seit dem letzten Frame berechnen
	m_fCurTime = SDL_GetTicks() / 1000.0f;

	m_fElapsed = m_fCurTime - m_fLastTime;
	m_fLastTime = m_fCurTime;

} // Update