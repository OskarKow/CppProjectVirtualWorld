#include "OknoInformacji.h"
#include "ObslugaKonsoli.h"
#include <iostream>
#include <string>
using namespace std;
using namespace informations;
using namespace console;

OknoInformacji::OknoInformacji()
{
	iloscKomunikatow = 0;
	komunikaty = NULL;
}
OknoInformacji::~OknoInformacji()
{
	delete[] komunikaty;
}

void OknoInformacji::dodajDoTablicy(string komunikat)
{
	iloscKomunikatow++;
	int numerKomunikatu;
	//usuwamy ostatni komunikat
	if (iloscKomunikatow == 21)
	{
		iloscKomunikatow = 20;
		numerKomunikatu = 1;
	}
	else numerKomunikatu = 0;
	string *nowa = new string[iloscKomunikatow];
	for (int i = 0; i < iloscKomunikatow - 1; i++)
	{
		nowa[i] = komunikaty[numerKomunikatu];
		numerKomunikatu++;
	}
	nowa[iloscKomunikatow - 1] = komunikat;
	komunikaty = nowa;
}

void OknoInformacji::dodajRezultatWalki(organism::Organizm* wygrany, organism::Organizm* przegrany, int numerTury)
{
	string komunikat, wspolrzedne;
	wspolrzedne = "(" + to_string(wygrany->getAktualnePolozenie().X) + "," + to_string(wygrany->getAktualnePolozenie().Y) + ")";
	komunikat = "Tura nr " + to_string(numerTury) + " na polu: " + wspolrzedne + 
		wygrany->typJakoString() + " zabija " + przegrany->typJakoString() + ".";
	dodajDoTablicy(komunikat);
}

void OknoInformacji::dodajRozmnazanie(COORD wspolrzedneNowegoOrganizmu, string typ, int numerTury)
{
	string komunikat, wspolrzedne;
	wspolrzedne = "(" + to_string(wspolrzedneNowegoOrganizmu.X) + "," + to_string(wspolrzedneNowegoOrganizmu.Y) + ")";
	komunikat = "Tura nr " + to_string(numerTury) + " na polu: " + wspolrzedne + " urodzil sie nowy " + typ + ".";
	dodajDoTablicy(komunikat);
}

void OknoInformacji::dodajZjedzenie(organism::Organizm* zwierze, organism::Organizm* roslina, int numerTury)
{
	string komunikat, wspolrzedne;
	wspolrzedne = "(" + to_string(zwierze->getAktualnePolozenie().X) + "," + to_string(zwierze->getAktualnePolozenie().Y) + ")";
	komunikat = "Tura nr " + to_string(numerTury) + " na polu: " + wspolrzedne + " " 
		+ zwierze->typJakoString() + " zjada " + roslina->typJakoString() + ".";
	dodajDoTablicy(komunikat);
}

void OknoInformacji::wyswietlKomunikaty()
{
	for (int i = iloscKomunikatow - 1; i >= 0; i--)
	{
		ObslugaKonsoli::gotoxy(23, iloscKomunikatow - i - 1);
		cout << "|" << komunikaty[i];
	}
}

void OknoInformacji::dodajZasianie(COORD wspolrzedneNowegoOrganizmu, std::string typ, int numerTury)
{
	string komunikat, wspolrzedne;
	wspolrzedne = "(" + to_string(wspolrzedneNowegoOrganizmu.X) + "," + to_string(wspolrzedneNowegoOrganizmu.Y) + ")";
	komunikat = "Tura nr " + to_string(numerTury) + " na polu: " + wspolrzedne + " wyrosla roslina: " + typ + ".";
	dodajDoTablicy(komunikat);
}

string OknoInformacji::toString()
{
	string wynik;
	wynik = to_string(iloscKomunikatow) + "\n";
	for (int i = 0; i < iloscKomunikatow; i++)
	{
		wynik += (komunikaty[i] + "\n");
	}
	return wynik;
}

void OknoInformacji::dodajString(std::string komunikat)
{
	dodajDoTablicy(komunikat);
}