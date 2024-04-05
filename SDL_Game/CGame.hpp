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
		int SplashScreen();	// SplashScreen
	
	private:
		void ProcessEvents   ();
		void SpawnAsteroids  ();
		bool ShowGameOver    ();
		void RenderAsteroids ();
		void CheckCollisionsShootAsteroid ();
		void CheckCollisionsAsteroidShip();

		CPlayer *m_pPlayer;				// Spieler-Instanz
		CSprite *m_pSpriteBackground;	// Sprite f�r den Hintergrund
		CSprite *m_pSpriteAsteroid;		// Sprite f�r die Asteroiden
		CSprite* m_pSpriteGameOver;		// Sprite f�r GameOver
		float    m_fAsteroidTimer;		// Zeitgeber f�r n�chsten Asteroiden
		bool     m_bGameRun;			// L�uft das Spiel noch?
		bool     m_bGameOver;			// GameOver
		list<CAsteroid> m_AsteroidList;	// Liste der Asteroiden

}; // CGame

#endif

