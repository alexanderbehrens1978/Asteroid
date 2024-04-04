//********************************************************************
//*                                                                  *
//*                      K l a s s e    CPlayer                      *
//*                                                                  *
//********************************************************************
//*                                                                  *
//*                      Dateiname   CPlayer.cpp                     *
//*                                                                  *
//********************************************************************
//*                                                                  *
//* Aufgabe: Die Spieler-Klasse. Sie beinhaltet neben der Position   *
//*          und dem Sprite des Spielers auch eine Liste aus CShot-  *
//*          Instanzen. Die Steuerung des Spielers findet ebenfalls  *
//*          hier statt.                                             *
//*                                                                  *
//********************************************************************
//
#include "CPlayer.hpp"
//
// Konstruktor
//
// Aufgabe: Allgemeine Initialisierungen
//
CPlayer::CPlayer()
{
	m_pSpritePlayer = NULL;
	m_pSpriteShot = NULL;

} // Konstruktor

// Init
//
// Aufgabe: Sprites erzeugen und laden
//
void CPlayer::Init()
{
	// Spielersprite erstellen
	m_pSpritePlayer = new CSprite;

	m_pSpritePlayer->Load("Data/Player.bmp", 11, 64, 64);

	// Schuss-Sprite erstellen
	m_pSpriteShot = new CSprite;

	m_pSpriteShot->Load("Data/Laser.bmp", 0, 64, 64);

} // Init



// Quit
//
// Aufgabe: Sprites freigeben
//
void CPlayer::Quit()
{
	// Spieler-Sprite freigeben
	if (m_pSpritePlayer != NULL)
	{
		delete (m_pSpritePlayer);
		m_pSpritePlayer = NULL;
	}

	// Schuss-Sprite freigeben
	if (m_pSpritePlayer != NULL)
	{
		delete (m_pSpritePlayer);
		m_pSpritePlayer = NULL;
	}

} // Quit


// Reset
// 
// Aufgabe: Spielerwerte auf Standard setzen
//
void CPlayer::Reset()
{
	// Startposition des Spielers
	m_fXPos = 376.0f;
	m_fYPos = 520.0f;

	// Animationsphase
	m_fAnimPhase = 5.0f;
	
	// Es darf geschossen werden
	m_bShotLock = false;

} // Reset


// Render
// 
// Aufgabe: Spieler und Schüsse rendern
//
void CPlayer::Render()
{
	// Position des Spielers setzen und Sprite rendern
	m_pSpritePlayer->SetPos(m_fXPos, m_fYPos);
	m_pSpritePlayer->Render(m_fAnimPhase);

	// Iterator für Schussliste
	list<CShot>::iterator it = m_ShotList.begin();

	// Schussliste durchlaufen
	while (it != m_ShotList.end())
	{
		// Schuss updaten
		it->Update();

		// Ist der Schuss noch aktiv?
		if (it->IsAlive())
		{
			// Ja, dann rendern
			it->Render();
			it++;
		}
		else
		{
			// Nein, dann aus der Liste entfernen
			it = m_ShotList.erase(it);
		}

	}

} // Render


// Update
//
// Aufgabe: Spieler updaten
//
void CPlayer::Update()
{
	// Bewegung des Spielers
	ProcessMoving();

	// Prüfen, ob geschossen wurde
	ProcessShooting();
	
	// Position und Animationsphase überprüfen
	CheckPosition();

} // Update

//
//	private:
//		void ProcessMoving();
//		void ProcessShooting();
//		void CheckPosition();
//
//		CSprite* m_pSpritePlayer;	// Sprite für Spieler
//		CSprite* m_pSpriteShot;		// Sprite für Laserschüsse
//		float m_fXPos;				// X-Position des Spielers
//		float m_fYPos;				// Y-Position des Spielers
//		float m_fAnimPhase;			// Aktuelle Animationsphase
//		bool  m_bShotLock;			// Darf der nächste Schuss raus?
//		list<CShot> m_ShotList;		// Lister der Schüsse
//
//
// ProcessMoving
//
// Aufgabe: Bewegung des Spielers
//
void CPlayer::ProcessMoving()
{
	// Nach links?
	if (g_pFramework->KeyDown(SDL_SCANCODE_LEFT))
	{
		// Spieler nach links bewegen
		m_fXPos -= 300.0f * g_pTimer->GetElapsed();

		// Animieren
		m_fAnimPhase -= 20.0f * g_pTimer->GetElapsed();
	
	}
	// Nach rechts?
	else if (g_pFramework->KeyDown(SDL_SCANCODE_RIGHT))
	{
		// Spieler nach rechts bewegen
		m_fXPos += 300.0f * g_pTimer->GetElapsed();
	
		// Animieren
		m_fAnimPhase += 20.0f * g_pTimer->GetElapsed();
	
	}
	// Spieler wurde nicht bewegt
	else
	{
		// Animation zurück zum Ausgangspunkt
		if (m_fAnimPhase > 5.0f)
			m_fAnimPhase -= 20.0f * g_pTimer->GetElapsed();
		if (m_fAnimPhase < 5.0f)
			m_fAnimPhase += 20.0f * g_pTimer->GetElapsed();
	}

} // ProcessMoving


// ProcessShooting
//
// Aufgabe: Waffe abfeuern
//
void CPlayer::ProcessShooting()
{
	// Wurde Space gedrückt und darf geschossen werden?
	if (g_pFramework->KeyDown(SDL_SCANCODE_SPACE) && m_bShotLock == false)
	{
		// Neuen Schuss erzeugen und initialisieren
		CShot Shot;
	
		Shot.Init(m_pSpriteShot, m_fXPos, m_fYPos);
		
		// Schuss in Liste einfügen
		m_ShotList.push_back(Shot);
		
		// Schießen erst wieder erlaubt, wenn Space losgelassen
		m_bShotLock = true;
	
	}

	// Ist die Leertaste nicht mehr gedrückt, schießen wieder erlaubt
	if (g_pFramework->KeyDown(SDL_SCANCODE_SPACE) == false)
		m_bShotLock = false;

} // ProcessShooting


// CheckPosition
//
// Aufgabe: Position und Animationsphase prüfen
//
void CPlayer::CheckPosition()
{
	// Linker und Rechter Rand
	if (m_fXPos < 0.0f)
		m_fXPos = 0.0f;
		
	else if (m_fXPos > 752.0f)
		m_fXPos = 752.0f;
	
	// Animationsphase prüfen
	if (m_fAnimPhase < 0.0f)
		m_fAnimPhase = 0.0f;
	else if (m_fAnimPhase > 10.0f)
		m_fAnimPhase = 10.0f;

} // CheckPosition


int CPlayer::GetX()
{
	return m_fXPos;
}

int CPlayer::GetY()
{
	return m_fYPos;
}

