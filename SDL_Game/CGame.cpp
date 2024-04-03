//********************************************************************
//*                                                                  *
//*                      K l a s s e    CGame                        *
//*                                                                  *
//********************************************************************
//*                                                                  *
//*                      Dateiname   CGame.cpp                       *
//*                                                                  *
//********************************************************************
//*                                                                  *
//* Aufgabe: Hier findet die eigentliche Spiellogik statt. Dazu      *
//*          geh�ren unter anderem das Hinzuf�gen und Rendern        *
//*          von Asteroiden, das Rendern des Hintergrundbildes       *
//*          und die Kollisionspr�fung zwischen Asteroiden und       *
//*          Sch�ssen.                                               *
//*                                                                  *
//********************************************************************
//
#include "CGame.hpp"
//
// Konstruktor
//
// Aufgabe: Allgemeine Initialisierungen
//
CGame::CGame()
{
	m_pPlayer = NULL;
	m_pSpriteBackground = NULL;
	m_pSpriteAsteroid = NULL;
} // Konstruktor


// Init
//
// Aufgabe: Spieler, Hintergrund und Asteroid initialisieren
//
void CGame::Init()
{
	// Neuen Spieler initialisieren
	m_pPlayer = new CPlayer;
	m_pPlayer->Init();
	m_pPlayer->Reset();

	// Hintergrundbild (Sprite) laden
	m_pSpriteBackground = new CSprite;
	m_pSpriteBackground->Load ("Data/Background.bmp");
	
	// Sprite f�r Asteroiden laden
	m_pSpriteAsteroid = new CSprite;
	m_pSpriteAsteroid->Load ("Data/Asteroid.bmp", 20, 64, 64);

	// Timer f�r Asteroiden zur�cksetzen
	m_fAsteroidTimer = 0.0f;
	
	// Spiel l�uft
	m_bGameRun = true;
} // Init


// Quit
//
// Aufgabe: Instanzen freigeben
//
void CGame::Quit()
{
	// Spieler freigeben
	if (m_pPlayer != NULL)
	{
		m_pPlayer->Quit();
		delete (m_pPlayer);
		m_pPlayer = NULL;
	}

	// Hintergrundsprite freigeben
	if (m_pSpriteBackground != NULL)
	{
		delete (m_pSpriteBackground);
		m_pSpriteBackground = NULL;
	}
	
	// Asteroidensprite freigeben
	if (m_pSpriteAsteroid != NULL)
	{
		delete (m_pSpriteBackground);
		m_pSpriteBackground = NULL;
	}

} // Quit


// Run
//
// Aufgabe: Hauptschleife des Spiels
//
void CGame::Run()
{
	// Hauptschleife des Spiels durchlaufen
	//
	while (m_bGameRun == true)
	{
		// Events bearbeiten
		ProcessEvents();

		// Framework updaten und Buffer l�schen
		g_pFramework->Update();
		g_pFramework->Clear();

		// Hintergrundbild rendern
		m_pSpriteBackground->Render();

		// Spieler updaten und rendern
		m_pPlayer->Update();
		m_pPlayer->Render();

		// Neue Asteroiden hinzuf�gen
		SpawnAsteroids();

		// Kollisionen pr�fen
		CheckCollisionsShootAsteroid();     // Game.cpp

		
		// Asteroiden rendern
		RenderAsteroids();

		// Spiel darstellen
		g_pFramework->Render();

	}

} // Run


// ProcessEvents
// 
// Aufgabe: Events bearbeiten
//
void CGame::ProcessEvents()
{
	SDL_Event Event;

	// Gab es ein Event?
	if (SDL_PollEvent (&Event))
	{
		// Ja, also schauen welches
		switch (Event.type)
		{
			// Beenden?
			case (SDL_QUIT):
			{
				m_bGameRun = false;
			} break;
			
			
			// Wurde eine Taste gedr�ckt?
			case (SDL_KEYDOWN):
			{
				switch (Event.key.keysym.sym)
				{
					case (SDLK_ESCAPE):
					{
						// Ja, also Spiel beenden
						m_bGameRun = false;
			
					} break;

					default:
						break;
				}
			} break;
		}
	}
} // ProcessEvents

// SpawnAsteroids
//
// Aufgabe: Nach Ablauf einer bestimmten Zeit neuen Asteroiden erzeugen
//
void CGame::SpawnAsteroids()
{
	// Timer f�r n�chsten Asteroiden erh�hen
	m_fAsteroidTimer += g_pTimer->GetElapsed();

	// Wenn eine halbe Sekunde vergangen ist,
	// dann einen neuen Asteroiden erzeugen
	if (m_fAsteroidTimer >= 0.5f)
	{
		// Neuer Asteroid
		CAsteroid Asteroid;

		// Zuf�llige X-Position
		// Debug 
		int XPos = rand() % 736;
		//int XPos = 150;

		// Asteroid initialisieren
		Asteroid.Init(m_pSpriteAsteroid, static_cast<float>(XPos), -60.0f);

		// Asteroid in Liste einf�gen
		m_AsteroidList.push_back(Asteroid);

		// Zeitgeber wieder zur�cksetzen
		m_fAsteroidTimer = 0.0f;

	}

} // SpawnAsteroids


// CheckCollisions
//
// Aufgabe: Kollisionen zwischen Asteroiden und Sch�ssen pr�fen
//
void CGame::CheckCollisionsShootAsteroid()
{

	// Schussliste des Spielers holen
	list<CShot> *ShotList = m_pPlayer->GetShotList();

	// Iteratoren f�r Asteroiden- und Schussliste
	list<CAsteroid>::iterator ItAsteroid = m_AsteroidList.begin();
	list<CShot>::iterator ItShot;
	// Raumschiff ? mit list<Wo auch immer das Raumschiff ist>::iterator ? mPlayer
	

	// Rects f�r Asteroiden und Sch�sse
	SDL_Rect RectAsteroid; // Asteroid
	SDL_Rect RectShot; // Schuss

	// Alle Asteroiden durchlaufen
	while (ItAsteroid != m_AsteroidList.end() )
	{
		// Rect des Asteroiden holen
		RectAsteroid = ItAsteroid->GetRect();

		// Alle Sch�sse durchlaufen
		for (ItShot = ShotList->begin();
			ItShot != ShotList->end();
			++ItShot)
		{
			// Rect des Schusses holen
			RectShot = ItShot->GetRect();
		
			if (RectShot.y < RectAsteroid.y + RectAsteroid.h &&
				RectShot.y + RectShot.h > RectAsteroid.y &&
				RectShot.x < RectAsteroid.x + RectAsteroid.w &&
				RectShot.x + RectShot.w > RectAsteroid.x)
				
			{
				// Ja, also gab es eine Kollision. Somit Schuss und 
				// Asteroid deaktivieren
				ItAsteroid->SetAlive(false);
				ItShot->SetAlive(false);
				
			}
		}

		// Asteroid l�schen, falls deaktiviert
		if (ItAsteroid->IsAlive () )
			ItAsteroid++;
		else
			ItAsteroid = m_AsteroidList.erase(ItAsteroid);

	}

} // CheckCollision

// CheckCollisionsAsteroidShip
//
// Aufgabe: Kollisionen zwischen Asteroiden und Schiff pr�fen
//
void CGame::CheckCollisionsAsteroidShip()
{

	// Schussliste des Spielers holen
	list<CShot>* ShotList = m_pPlayer->GetShotList();

	// Iteratoren f�r Asteroiden- und Schussliste
	list<CAsteroid>::iterator ItAsteroid = m_AsteroidList.begin();
	list<CShot>::iterator ItShot;
	// Raumschiff ? mit list<Wo auch immer das Raumschiff ist>::iterator ? mPlayer


	// Rects f�r Asteroiden und Schiff
	SDL_Rect RectAsteroid;
	SDL_Rect RectShip; // Muss gegen Schiff getauscht werden

	// Alle Asteroiden durchlaufen
	while (ItAsteroid != m_AsteroidList.end())
	{
		// Rect des Asteroiden holen
		RectAsteroid = ItAsteroid->GetRect();

		// Alle Sch�sse durchlaufen
		for (ItShot = ShotList->begin();
			ItShot != ShotList->end();
			++ItShot)
		{
			// Rect des Schusses holen
			RectShip = ItShot->GetRect();

			if (RectShip.y < RectAsteroid.y + RectAsteroid.h &&
				RectShip.y + RectShip.h > RectAsteroid.y &&
				RectShip.x < RectAsteroid.x + RectAsteroid.w &&
				RectShip.x + RectShip.w > RectAsteroid.x)

			{
				// Ja, also gab es eine Kollision. Somit Schuss und 
				// Asteroid deaktivieren
				ItAsteroid->SetAlive(false);
				ItShot->SetAlive(false);

			}
		}

		// Asteroid l�schen, falls deaktiviert
		if (ItAsteroid->IsAlive())
			ItAsteroid++;
		else
			ItAsteroid = m_AsteroidList.erase(ItAsteroid);

	}

} // CheckCollisionAsteroidShip

// RenderAsteroids
//
// Aufgabe: Alle Asteroiden rendern und updaten
//
void CGame::RenderAsteroids ()
{
	// Iterator f�r die Asteroiden-Liste
	list<CAsteroid>::iterator It;

	// Asteroiden-Liste durchlaufen
	for (It = m_AsteroidList.begin(); It != m_AsteroidList.end(); ++It)
	{
		// Asteroid rendern
		It->Render ();
	
		// Asteroid updaten
		It->Update ();

	}

} // RenderAsteroids

