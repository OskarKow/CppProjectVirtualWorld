#pragma once
#include <string>
#include <windows.h>
#include "Organizm.h"

namespace organism
{
	class Organizm;
}

namespace informations
{
	class OknoInformacji
	{
	private:
		std::string *komunikaty;
		int iloscKomunikatow;
		void dodajDoTablicy(std::string komunikat);
	public:
		OknoInformacji();
		~OknoInformacji();
		void wyswietlKomunikaty();
		void dodajRezultatWalki(organism::Organizm* wygrany, organism::Organizm* przegrany, int numerTury);
		void dodajRozmnazanie(COORD wspolrzedneNowegoOrganizmu, std::string typ, int numerTury);
		void dodajZjedzenie(organism::Organizm* zwierze, organism::Organizm* roslina, int numerTury);
		void dodajZasianie(COORD wspolrzedneNowegoOrganizmu, std::string typ, int numerTury);
		void dodajString(std::string komunikat);
		std::string toString();
	};
}