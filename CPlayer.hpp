// Player.hpp
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <list>
#include "CSprite.hpp"
#include "CShot.hpp"

class CPlayer
{
	public:
		CPlayer     ();
		void Init   ();	// Spiel Initialisieren
		void Quit   ();	// Spiel Beenden
		void Render ();	// Spieler neuzeichnen
		void Update ();	// Spieler updaten
		void Reset  ();	// Spieler zurück setzen
		list<CShot> *GetShotList() { return &m_ShotList; }	// Irgendwas mit schiessen
		int GetX();		// X-Position des Spielers
		int GetY();		// Y-Position des Spielers
	
	private:
		void ProcessMoving   ();
		void ProcessShooting ();
		void CheckPosition   ();

		CSprite *m_pSpritePlayer;	// Sprite für Spieler
		CSprite *m_pSpriteShot;		// Sprite für Laserschüsse
		float m_fXPos;				// X-Position des Spielers
		float m_fYPos;				// Y-Position des Spielers
		float m_fAnimPhase;			// Aktuelle Animationsphase
		bool  m_bShotLock;			// Darf der nächste Schuss raus?
		list<CShot> m_ShotList;		// Lister der Schüsse

}; // CPlayer
#endif
