#pragma once
#include <string>
#include <iostream>
#include "ObslugaKonsoli.h"
using namespace std;

namespace exceptions
{
	class WyjatekWprowadzenie
	{
	public:
		string komunikat;
		virtual void ustawKomunikat() = 0;
		void wypiszKomunikat()
		{
			console::ObslugaKonsoli::gotoxy(0, 22);
			cout << komunikat;
		}
	};
	class WyjatekWejscieNaSciane : public WyjatekWprowadzenie
	{
	public:
		COORD wspolrzedne;
		WyjatekWejscieNaSciane(COORD miejsce)
		{
			wspolrzedne = miejsce;
			ustawKomunikat();
		}
		void ustawKomunikat()
		{
			string Wsp = "(" + to_string(wspolrzedne.X) + "," + to_string(wspolrzedne.Y) + ")";
			komunikat = "Proba wejscia na sciane na polu: " + Wsp + "    ";
		}
	};

	class WyjatekUmiejetnoscNieaktywna : public WyjatekWprowadzenie
	{
	public:
		int pozostalyCzas;
		WyjatekUmiejetnoscNieaktywna(int pozostalyCooldown)
		{
			pozostalyCzas = pozostalyCooldown;
			ustawKomunikat();
		}
		void ustawKomunikat()
		{
			komunikat = "Umiejetnosc nieaktywna. Pozostalo " + to_string(pozostalyCzas) + " tur.";
		}
	};
}
