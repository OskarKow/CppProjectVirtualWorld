#include "Rosliny.h"
#include "OknoInformacji.h"
#include <ctime>
#include <windows.h>
using namespace plant;


void Roslina::rozprzestrzeniajSie(world::Swiat* swiat)
{
		COORD wolne = swiat->wylosujWolnePole(aktualnePolozenie);
		if (wolne.X > 0 && wolne.Y > 0)
		{
			swiat->getDoDodania()->dodajOrganizm(swiat->stworzOrganizm(wolne.X, wolne.Y, typ));
			swiat->getOknoInformacji()->dodajZasianie(wolne, typJakoString(), swiat->getNumerTury());
		}
}
//roslina jest zjadana
void Roslina::walcz(world::Swiat* swiat, organism::Organizm* napastnik)
{
	swiat->getDoUsuniecia()->dodajOrganizm(this);
	swiat->setPole(aktualnePolozenie, napastnik->getTyp());
	swiat->setPole(napastnik->getPoprzedniePolozenie(), PUSTE);
	swiat->getOknoInformacji()->dodajZjedzenie(napastnik, this, swiat->getNumerTury());
}

Trawa::Trawa(int x, int y)
{
	sila = 0;
	inicjatywa = 0;
	aktualnePolozenie.X = poprzedniePolozenie.X = x;
	aktualnePolozenie.Y = poprzedniePolozenie.Y = y;
	typ = TRAWA;
	wyglad = 'T';
	wiek = 0;
}
Trawa::Trawa(COORD aktualne, COORD poprzednie, int sila, int wiek)
{
	this->sila = sila;
	this->wiek = wiek;
	inicjatywa = 0;
	aktualnePolozenie = aktualne;
	poprzedniePolozenie = poprzednie;
	typ = TRAWA;
	wyglad = 'T';
}
Trawa::~Trawa()
{

}
void Trawa::akcja(world::Swiat* swiat)
{
	int losowa = rand() % (100 / SZANSA_ZASIANIA);
	if (losowa == 0)
	{
		rozprzestrzeniajSie(swiat);
	}
}
Mlecz::Mlecz(int x, int y)
{
	sila = 0;
	inicjatywa = 0;
	aktualnePolozenie.X = poprzedniePolozenie.X = x;
	aktualnePolozenie.Y = poprzedniePolozenie.Y = y;
	typ = MLECZ;
	wyglad = 'M';
	wiek = 0;
}
Mlecz::Mlecz(COORD aktualne, COORD poprzednie, int sila, int wiek)
{
	this->sila = sila;
	this->wiek = wiek;
	inicjatywa = 0;
	aktualnePolozenie = aktualne;
	poprzedniePolozenie = poprzednie;
	typ = MLECZ;
	wyglad = 'M';
}
Mlecz::~Mlecz()
{

}
void Mlecz::akcja(world::Swiat* swiat)
{
	int losowa;
	bool probaUdana = false;
	for (int i = 0; i < 3; i++)
	{
		losowa = rand() % (100 / SZANSA_ZASIANIA);
		if (losowa == 0) probaUdana = true;
	}
	if (probaUdana) rozprzestrzeniajSie(swiat);
}
Guarana::Guarana(int x, int y)
{
	sila = 0;
	inicjatywa = 0;
	aktualnePolozenie.X = poprzedniePolozenie.X = x;
	aktualnePolozenie.Y = poprzedniePolozenie.Y = y;
	typ = GUARANA;
	wyglad = 'G';
	wiek = 0;
}
Guarana::Guarana(COORD aktualne, COORD poprzednie, int sila, int wiek)
{
	this->sila = sila;
	this->wiek = wiek;
	inicjatywa = 0;
	aktualnePolozenie = aktualne;
	poprzedniePolozenie = poprzednie;
	typ = GUARANA;
	wyglad = 'G';
}
Guarana::~Guarana()
{

}
void Guarana::walcz(world::Swiat* swiat, organism::Organizm* napastnik)
{
	swiat->getDoUsuniecia()->dodajOrganizm(this);
	swiat->setPole(aktualnePolozenie, napastnik->getTyp());
	swiat->setPole(napastnik->getPoprzedniePolozenie(), PUSTE);
	swiat->getOknoInformacji()->dodajZjedzenie(napastnik, this, swiat->getNumerTury());
	napastnik->zwiekszSile(3);
}
void Guarana::akcja(world::Swiat* swiat)
{
	int losowa = rand() % (100 / SZANSA_ZASIANIA);
	if (losowa == 0)
	{
		rozprzestrzeniajSie(swiat);
	}
}
WilczeJagody::WilczeJagody(int x, int y)
{
	sila = 99;
	inicjatywa = 0;
	aktualnePolozenie.X = poprzedniePolozenie.X = x;
	aktualnePolozenie.Y = poprzedniePolozenie.Y = y;
	typ = JAGODY;
	wyglad = 'J';
	wiek = 0;
}
WilczeJagody::WilczeJagody(COORD aktualne, COORD poprzednie, int sila, int wiek)
{
	this->sila = sila;
	this->wiek = wiek;
	inicjatywa = 0;
	aktualnePolozenie = aktualne;
	poprzedniePolozenie = poprzednie;
	typ = JAGODY;
	wyglad = 'J';
}
WilczeJagody::~WilczeJagody()
{

}
void WilczeJagody::akcja(world::Swiat* swiat)
{
	int losowa = rand() % (100 / SZANSA_ZASIANIA);
	if (losowa == 0)
	{
		rozprzestrzeniajSie(swiat);
	}
}
void WilczeJagody::walcz(world::Swiat* swiat, organism::Organizm* napastnik)
{
	swiat->setPole(napastnik->getPoprzedniePolozenie(), PUSTE);
	swiat->getDoUsuniecia()->dodajOrganizm(napastnik);
	swiat->getDoUsuniecia()->dodajOrganizm(this);
	swiat->setPole(aktualnePolozenie, PUSTE);
	swiat->getOknoInformacji()->dodajZjedzenie(napastnik, this, swiat->getNumerTury());
}