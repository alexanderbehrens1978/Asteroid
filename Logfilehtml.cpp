// Listing 8.15
// Anwendung der Logfile-Klasse
//
#include <iostream>
#include "Logfile.hpp"

using namespace std;

// Hauptprogramm
//
int main ()
{
	// Variablen
	//
	float Kontrolle = 123.456f;	// Variable zum Testen

	// Neues Logfile erstellen
	g_pLogfile->CreateLogfile("Logfile.html");

	// ‹berschrift erzeugen
	g_pLogfile->WriteTopic ("Unformatierter Text", 2);

	// Unformatierten Text ausgeben
	g_pLogfile->Textout ("Normaler, schwarzer Text<br>");
	g_pLogfile->Textout (RED, "Farbiger Text");
	g_pLogfile->Textout (BLUE, "Farbiger Text in Liste (1)");
	g_pLogfile->Textout (BLUE, "Farbiger Text in Liste (2)");
	g_pLogfile->Textout (BLUE, "Farbiger Text in Liste (3)");

	// ‹berschrift erzeugen
	g_pLogfile->WriteTopic ("Formatierter Text", 2);

	// Formatierten Text ausgeben
	g_pLogfile->fTextout ("Kontrollvariable: %f<br>", Kontrolle);
	g_pLogfile->fTextout (RED, "Kontrollvariable: %f", Kontrolle);
	g_pLogfile->fTextout (GREEN, true, "Liste Kontrolle: %f", Kontrolle);
	g_pLogfile->fTextout (GREEN, true, "Liste Kontrolle: %f", Kontrolle*2.0f);
	g_pLogfile->fTextout (GREEN, true, "Liste Kontrolle: %f", Kontrolle * 4.0f);

	// Eine erfolgreiche und eine fehlgeschlagene Funktion
	g_pLogfile->FunctionResult("Funktion_Eins", L_OK)
	g_pLogfile->FunctionResult("Funktion_Zwei", L_FAIL);

} // Logfile schlieﬂen