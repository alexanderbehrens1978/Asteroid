// Game.hpp
#ifndef GAME_HPP
#define GAME_HPP

#include "CPlayer.hpp"
#include "CAsteroid.hpp"

class CGame
{
	public:
		CGame();

		void Init ();		// Initialiseren
		void Run  ();		// Starten
		void Quit ();		// Beenden
	
	private:
		void ProcessEvents   ();
		void SpawnAsteroids  ();
		void RenderAsteroids ();
		void CheckCollisions ();

		CPlayer *m_pPlayer;				// Spieler-Instanz
		CSprite *m_pSpriteBackground;	// Sprite f�r den Hintergrund
		CSprite *m_pSpriteAsteroid;		// Sprite f�r die Asteroiden
		float    m_fAsteroidTimer;		// Zeitgeber f�r n�chsten Asteroiden
		bool     m_bGameRun;			// L�uft das Spiel noch?
		list<CAsteroid> m_AsteroidList;	// Liste der Asteroiden

}; // CGame

#endif

