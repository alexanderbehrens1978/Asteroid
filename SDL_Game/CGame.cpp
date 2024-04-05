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
//*          gehören unter anderem das Hinzufügen und Rendern        *
//*          von Asteroiden, das Rendern des Hintergrundbildes       *
//*          und die Kollisionsprüfung zwischen Asteroiden und       *
//*          Schüssen.                                               *
//*                                                                  *
//********************************************************************
//
#include "CGame.hpp"
#include <iostream>
//
// Konstruktor
//
// Aufgabe: Allgemeine Initialisierungen
//
CGame::CGame()
{
	m_pPlayer = NULL;
	m_fAsteroidTimer = NULL;
	m_pSpriteBackground = NULL;
	m_pSpriteAsteroid = NULL;
	m_pSpriteGameOver = NULL;
	m_bGameRun = false;
	m_bGameOver = false;
} // Konstruktor


// Init
//
// Aufgabe: Spieler, Hintergrund und Asteroid initialisieren
//
void CGame::Init()	// public
{
	// Neuen Spieler initialisieren
	m_pPlayer = new CPlayer;
	m_pPlayer->Init();
	m_pPlayer->Reset();

	// Hintergrundbild (Sprite) laden
	m_pSpriteBackground = new CSprite;
	m_pSpriteBackground->Load ("Data/Background.bmp");
	
	// Sprite für Asteroiden laden
	m_pSpriteAsteroid = new CSprite;
	m_pSpriteAsteroid->Load ("Data/Asteroid.bmp", 20, 64, 64);

	// hier muss der Highscore hin
	// Highscore als Bitmap mit den Zahlen 0 - 9

	// hier muss das Gameover hin
	// laden
	m_pSpriteGameOver = new CSprite;
	m_pSpriteGameOver->Load("Data/GameOver.bmp");

	// Timer für Asteroiden zurücksetzen
	m_fAsteroidTimer = 0.0f;
	
	// Spiel läuft
	m_bGameRun = true;
} // Init


// Run
//
// Aufgabe: Hauptschleife des Spiels
//
void CGame::Run()	// public
{
	while (m_bGameOver != true)
	{
		// Hauptschleife des Spiels durchlaufen
		//
		while (m_bGameRun == true)
		{
			// Events bearbeiten
			ProcessEvents();

			// Framework updaten und Buffer löschen
			g_pFramework->Update();
			g_pFramework->Clear();

			// Hintergrundbild rendern
			m_pSpriteBackground->Render();

			// Spieler updaten und rendern
			m_pPlayer->Update();
			m_pPlayer->Render();

			// Neue Asteroiden hinzufügen
			SpawnAsteroids();

			// Kollisionen prüfen
			CheckCollisionsShootAsteroid(); // kann der Schuss den Asteroiden abschiessen
			//CheckCollisionsAsteroidShip(); // beim berühren des Schiffs mit einem Asteroiden soll
										   // eine Meldung erscheinen

			// Asteroiden rendern
			RenderAsteroids();

			// GameOver hinzufügen
			//SpawnAsteroids() als Basis nehmen
			//ShowGameOver(); // Es sollte alles hier in einer Schleife laufen
			// und prüfen ob ShowGameOver() true oder false zurück gibt und darauf abbrechen

			// GameOver rendern
			// RenderAsteroids() als Basis nehmen

			// Spiel darstellen
			g_pFramework->Render();

		}
	}
} // Run


// Quit
//
// Aufgabe: Instanzen freigeben
//
void CGame::Quit()	// public
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

	// GameOversprite freigeben
	if (m_pSpriteGameOver != NULL)
	{
		delete (m_pSpriteGameOver);
		m_pSpriteGameOver = NULL;
	}

} // Quit


int CGame::SplashScreen()	// SplashScreen
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Failed to initialize the SDL2 library\n";
		return -1;
	}

	SDL_Window* splashscreen = SDL_CreateWindow("Splash Screen",
		1000, 200, // x, y
		680, 480,
		0);

	if (!splashscreen)
	{
		std::cout << "Failed to create window\n";
		return -1;
	}

	SDL_Surface* window_surface = SDL_GetWindowSurface(splashscreen);

	if (!window_surface)
	{
		std::cout << "Failed to get the surface from the window\n";
		return -1;
	}

	SDL_UpdateWindowSurface(splashscreen);


	//SDL_Delay(5000);
	// Renderer und Fenster freigeben

	//if (splashscreen != NULL)
	//{
	//	SDL_DestroyWindow(splashscreen);
	//}
	
}


//############################## P r i v a t e ####################################

// ProcessEvents
// 
// Aufgabe: Events bearbeiten
//
void CGame::ProcessEvents()	// private
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
			
			
			// Wurde eine Taste gedrückt?
			case (SDL_KEYDOWN):
			{
				switch (Event.key.keysym.sym)
				{
					case (SDLK_ESCAPE):
					{
						// Ja, also Spiel beenden
						m_bGameRun = false;
			
					} break;

					case(SDLK_F4):
					{
						// Ja, also Spiel beenden
						m_bGameRun = false;
					} break;

					case(SDLK_F3):
					{
						// Ja, also Spiel beenden
						m_bGameRun = false;
					}

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
void CGame::SpawnAsteroids()	// private
{
	// Timer für nächsten Asteroiden erhöhen
	m_fAsteroidTimer += g_pTimer->GetElapsed();

	// Wenn eine halbe Sekunde vergangen ist,
	// dann einen neuen Asteroiden erzeugen
	if (m_fAsteroidTimer >= 0.5f)
	{
		// Neuer Asteroid
		CAsteroid Asteroid;

		// Zufällige X-Position
		// Debug 
		int XPos = rand() % 736;
		//int XPos = 150;

		// Asteroid initialisieren
		Asteroid.Init(m_pSpriteAsteroid, static_cast<float>(XPos), -60.0f);

		// Asteroid in Liste einfügen
		m_AsteroidList.push_back(Asteroid);

		// Zeitgeber wieder zurücksetzen
		m_fAsteroidTimer = 0.0f;

	}

} // SpawnAsteroids


// ShowGameOver
//
// Aufgabe: Das Ende nach Kriterium X, Y
//
bool CGame::ShowGameOver()	// private
{
		
		m_pSpriteGameOver->SetPos(250, 150); // x, y
		m_pSpriteGameOver->Render();

		//SDL_Delay(5000);
		// Renderer und Fenster freigeben
		
		SDL_Delay(5000);
		//SDL_QUIT;
		//CGame::Quit();
		//g_pFramework->Quit();
		//SDL_Quit();
		cout << "Game Over\n";

		m_bGameRun = false;

		return true;
} // ShowGameOver()



// CheckCollisions
//
// Aufgabe: Kollisionen zwischen Asteroiden und Schüssen prüfen
//
void CGame::CheckCollisionsShootAsteroid()	// private
{

	// Schussliste des Spielers holen
	list<CShot> *ShotList = m_pPlayer->GetShotList();

	// Iteratoren für Asteroiden- und Schussliste
	list<CAsteroid>::iterator ItAsteroid = m_AsteroidList.begin();
	list<CShot>::iterator ItShot;
	// Raumschiff ? mit list<Wo auch immer das Raumschiff ist>::iterator ? mPlayer
	

	// Rects für Asteroiden und Schüsse
	SDL_Rect RectAsteroid; // Asteroid
	SDL_Rect RectShot; // Schuss

	// Alle Asteroiden durchlaufen
	while (ItAsteroid != m_AsteroidList.end() )
	{
		// Rect des Asteroiden holen
		RectAsteroid = ItAsteroid->GetRect();

		// Alle Schüsse durchlaufen
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

		// Asteroid löschen, falls deaktiviert
		if (ItAsteroid->IsAlive () )
			ItAsteroid++;
		else
			ItAsteroid = m_AsteroidList.erase(ItAsteroid);

	}

} // CheckCollision

// CheckCollisionsAsteroidShip
//
// Aufgabe: Kollisionen zwischen Asteroiden und Schiff prüfen
//
void CGame::CheckCollisionsAsteroidShip()	// private
{
	// Aufgabe: Überprüfen ob der Asteroid mit dem Schiff kollidiert
	// 

	// Schussliste des Spielers holen
	list<CShot>* ShotList = m_pPlayer->GetShotList();

	// Iteratoren für Asteroiden- und Schussliste
	list<CAsteroid>::iterator ItAsteroid = m_AsteroidList.begin();
	list<CShot>::iterator ItShot;
	// Raumschiff ? mit list<Wo auch immer das Raumschiff ist>::iterator ? mPlayer


	// Rects für Asteroiden und Schiff
	SDL_Rect RectAsteroid;
	SDL_Rect RectShip; // Muss gegen Schiff getauscht werden

	// Alle Asteroiden durchlaufen
	while (ItAsteroid != m_AsteroidList.end())
	{
		// Rect des Asteroiden holen
		RectAsteroid = ItAsteroid->GetRect();

		// Alle Schüsse durchlaufen
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

	}

} // CheckCollisionAsteroidShip

// RenderAsteroids
//
// Aufgabe: Alle Asteroiden rendern und updaten
//
void CGame::RenderAsteroids ()	// private
{
	// Iterator für die Asteroiden-Liste
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

