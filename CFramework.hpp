// Framework.hpp
#ifndef FRAMEWORK_HPP
#define FRAMEWORK_HPP

#include <iostream>
#include "singleton.hpp"
#include "CTimer.hpp"

using namespace std;

#define g_pFramework CFramework::Get()

class CFramework : public TSingleton<CFramework>
{
	public:
			CFramework();
		bool Init	 (int ScreenWidth, int ScreenHeight,	// Spielfeld Breite, Höhe, Farbtiefe, Vollbild j/n
		   		      int ColorDepth, bool bFullscreen);
		void Quit	 ();	// Beenden
		void Update	 ();	// Anzeige aktualisieren
		void Clear	 ();	// Anzeige säubern
		void Render	 ();	// Anzeige neuzeichnen
		bool KeyDown (int Key_ID);	// Wurde eine Taste gedrückt
		SDL_Renderer* GetRenderer() { return m_pRenderer; }

	private:
		const Uint8  *m_pKeystate;	// array für aktuellen Tastaturstatus
		SDL_Window   *m_pWindow;	// SDL-Windows
		SDL_Renderer *m_pRenderer;	// SDL-Renderer

};

#endif // FRAMEWORK_HPP