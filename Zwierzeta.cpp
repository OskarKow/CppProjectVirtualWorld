#include "Zwierzeta.h"
#include "OknoInformacji.h"
#include "ObslugaKonsoli.h"
#include "Wyjatki.h"
#include <ctime>
#include <iostream>
using namespace animal;
using namespace console;
using namespace std;
using namespace exceptions;
enum WCISNIETY_KLAWISZ;

COORD Zwierze::wylosujSasiedniePole()
{
	int losowa;
	COORD nowe = { 0,0 };
	do
	{
		losowa = rand() % 4;
		switch (losowa)
		{
		case 0:
			nowe = { aktualnePolozenie.X, aktualnePolozenie.Y - 1 };
			break;
		case 1:
			nowe = { aktualnePolozenie.X + 1, aktualnePolozenie.Y };
			break;
		case 2:
			nowe = { aktualnePolozenie.X, aktualnePolozenie.Y + 1 };
			break;
		case 3:
			nowe = { aktualnePolozenie.X - 1, aktualnePolozenie.Y };
			break;
		}
	} while (nowe.X < 0 || nowe.X > 19 || nowe.Y < 0 || nowe.Y > 19);
	return nowe;
}

void Zwierze::poruszSie(world::Swiat* swiat, COORD docelowe)
{
	poprzedniePolozenie = aktualnePolozenie;
	aktualnePolozenie = docelowe;
	if (swiat->getPole(docelowe.X, docelowe.Y) == PUSTE)
	{
		swiat->setPole(poprzedniePolozenie, PUSTE);
		swiat->setPole(aktualnePolozenie, typ);
	}
	else {
		kolizja(swiat);
	}
}

void Zwierze::rozmnazajSie(world::Swiat* swiat)
{
	aktualnePolozenie = poprzedniePolozenie;
	COORD wspolrzedne = swiat->wylosujWolnePole(aktualnePolozenie);
	if (wspolrzedne.X > 0 && wspolrzedne.Y > 0)
	{
		swiat->getDoDodania()->dodajOrganizm(swiat->stworzOrganizm(wspolrzedne.X, wspolrzedne.Y, typ));
		swiat->getOknoInformacji()->dodajRozmnazanie(wspolrzedne, this->typJakoString(), swiat->getNumerTury());
	}
	
}

bool Zwierze::wygranaWalka(organism::Organizm* napastnik)
{
	if (this->sila > napastnik->getSila()) return true;
	if (this->sila <= napastnik->getSila()) return false;
}
//Ogolny sposob walki dla wiekszosci zwierzat
void Zwierze::walcz(world::Swiat* swiat, organism::Organizm* napastnik)
{
	if (wygranaWalka(napastnik))
	{
		swiat->getDoUsuniecia()->dodajOrganizm(napastnik);
		swiat->setPole(napastnik->getPoprzedniePolozenie(), PUSTE);
		swiat->getOknoInformacji()->dodajRezultatWalki(this, napastnik, swiat->getNumerTury());
	}
	else
	{
		swiat->getDoUsuniecia()->dodajOrganizm(this);
		swiat->setPole(aktualnePolozenie, napastnik->getTyp());
		swiat->setPole(napastnik->getPoprzedniePolozenie(), PUSTE);
		swiat->getOknoInformacji()->dodajRezultatWalki(napastnik, this, swiat->getNumerTury());
	}
}

Wilk::Wilk(int x, int y)
{
	sila = 9;
	inicjatywa = 5;
	wiek = 0;
	aktualnePolozenie.X = poprzedniePolozenie.X = x;
	aktualnePolozenie.Y = poprzedniePolozenie.Y = y;
	wyglad = 'W';
	typ = WILK;
}
Wilk::Wilk(COORD aktualne, COORD poprzednie, int sila, int wiek)
{
	this->sila = sila;
	inicjatywa = 5;
	this->wiek = wiek;
	aktualnePolozenie = aktualne;
	poprzedniePolozenie = poprzednie;
	wyglad = 'W';
	typ = WILK;
}
Wilk::~Wilk()
{

}
void Wilk::akcja(world::Swiat* swiat)
{
	COORD nowe_pole = wylosujSasiedniePole();
	poruszSie(swiat, nowe_pole);
}
void Wilk::kolizja(world::Swiat* swiat)
{
	Organizm* drugi = swiat->getOrganizm(aktualnePolozenie, this);
	if (drugi != NULL)
	{
		if (drugi->getTyp() == typ)
		{
			rozmnazajSie(swiat);
		}
		else {
			drugi->walcz(swiat, this);
		}
	}
}
Owca::Owca(int x, int y)
{
	sila = 4;
	inicjatywa = 4;
	wiek = 0;
	aktualnePolozenie.X = poprzedniePolozenie.X = x;
	aktualnePolozenie.Y = poprzedniePolozenie.Y = y;
	wyglad = 'O';
	typ = OWCA;
}
Owca::Owca(COORD aktualne, COORD poprzednie, int sila, int wiek)
{
	this->sila = sila;
	inicjatywa = 5;
	this->wiek = wiek;
	aktualnePolozenie = aktualne;
	poprzedniePolozenie = poprzednie;
	wyglad = 'O';
	typ = OWCA;
}
Owca::~Owca()
{

}
void Owca::akcja(world::Swiat* swiat)
{
	COORD nowe_pole = wylosujSasiedniePole();
	poruszSie(swiat, nowe_pole);
}
void Owca::kolizja(world::Swiat* swiat)
{
	Organizm* drugi = swiat->getOrganizm(aktualnePolozenie, this);
	if (drugi != NULL)
	{
		if (drugi->getTyp() == typ)
		{
			rozmnazajSie(swiat);
		}
		else {
			drugi->walcz(swiat, this);
		}
	}
}
Zolw::Zolw(int x, int y)
{
	sila = 2;
	inicjatywa = 1;
	wiek = 0;
	aktualnePolozenie.X = poprzedniePolozenie.X = x;
	aktualnePolozenie.Y = poprzedniePolozenie.Y = y;
	wyglad = 'Z';
	typ = ZOLW;
}
Zolw::Zolw(COORD aktualne, COORD poprzednie, int sila, int wiek)
{
	this->sila = sila;
	inicjatywa = 5;
	this->wiek = wiek;
	aktualnePolozenie = aktualne;
	poprzedniePolozenie = poprzednie;
	wyglad = 'Z';
	typ = ZOLW;
}
Zolw::~Zolw()
{

}
void Zolw::walcz(world::Swiat* swiat, organism::Organizm* napastnik)
{
	if (napastnik->getSila() < 5)
	{
		napastnik->setAktualnePolozenie(napastnik->getPoprzedniePolozenie());
	}
	else {
		if (wygranaWalka(napastnik))
		{
			swiat->getDoUsuniecia()->dodajOrganizm(napastnik);
			swiat->setPole(napastnik->getPoprzedniePolozenie(), PUSTE);
			swiat->getOknoInformacji()->dodajRezultatWalki(this, napastnik, swiat->getNumerTury());
		}
		else
		{
			swiat->getDoUsuniecia()->dodajOrganizm(this);
			swiat->setPole(aktualnePolozenie, napastnik->getTyp());
			swiat->setPole(napastnik->getPoprzedniePolozenie(), PUSTE);
			swiat->getOknoInformacji()->dodajRezultatWalki(napastnik, this, swiat->getNumerTury());
		}
	}
}
void Zolw::akcja(world::Swiat* swiat)
{
	int losowa = rand() % 4;
	if (losowa == 0)
	{
		COORD nowe_pole = wylosujSasiedniePole();
		poruszSie(swiat, nowe_pole);
	}
}
void Zolw::kolizja(world::Swiat* swiat)
{
	Organizm* drugi = swiat->getOrganizm(aktualnePolozenie, this);
	if (drugi != NULL)
	{
		if (drugi->getTyp() == typ)
		{
			rozmnazajSie(swiat);
		}
		else {
			drugi->walcz(swiat, this);
		}
	}
}
Antylopa::Antylopa(int x, int y)
{
	sila = 4;
	inicjatywa = 4;
	wiek = 0;
	aktualnePolozenie.X = poprzedniePolozenie.X = x;
	aktualnePolozenie.Y = poprzedniePolozenie.Y = y;
	wyglad = 'A';
	typ = ANTYLOPA;
}
Antylopa::Antylopa(COORD aktualne, COORD poprzednie, int sila, int wiek)
{
	this->sila = sila;
	inicjatywa = 5;
	this->wiek = wiek;
	aktualnePolozenie = aktualne;
	poprzedniePolozenie = poprzednie;
	wyglad = 'A';
	typ = ANTYLOPA;
}
Antylopa::~Antylopa()
{

}
void Antylopa::walcz(world::Swiat* swiat, organism::Organizm* napastnik)
{
	int ucieczka = rand() % 2;
	if (ucieczka)
	{
		COORD nowePole = swiat->wylosujWolnePole(aktualnePolozenie);
		if (nowePole.X > 0 && nowePole.Y > 0)
		{
			swiat->setPole(napastnik->getAktualnePolozenie(), napastnik->getTyp());
			swiat->setPole(napastnik->getPoprzedniePolozenie(), PUSTE);
			poprzedniePolozenie = aktualnePolozenie;
			aktualnePolozenie = nowePole;
			swiat->setPole(aktualnePolozenie, typ);
			return;
		}
	}
	if (wygranaWalka(napastnik))
	{
		swiat->getDoUsuniecia()->dodajOrganizm(napastnik);
		swiat->setPole(napastnik->getPoprzedniePolozenie(), PUSTE);
		swiat->getOknoInformacji()->dodajRezultatWalki(this, napastnik, swiat->getNumerTury());
	}
	else
	{
		swiat->getDoUsuniecia()->dodajOrganizm(this);
		swiat->setPole(aktualnePolozenie, napastnik->getTyp());
		swiat->setPole(napastnik->getPoprzedniePolozenie(), PUSTE);
		swiat->getOknoInformacji()->dodajRezultatWalki(napastnik, this, swiat->getNumerTury());
	}
}
void Antylopa::akcja(world::Swiat* swiat)
{
	COORD mozliwePola[4];
	int iloscWolnych = 0;
	if (aktualnePolozenie.Y > 1)
	{
		mozliwePola[iloscWolnych] = { aktualnePolozenie.X, aktualnePolozenie.Y - 2 };
		iloscWolnych++;
	}
	if (aktualnePolozenie.X < 18)
	{
		mozliwePola[iloscWolnych] = { aktualnePolozenie.X + 2, aktualnePolozenie.Y };
		iloscWolnych++;
	}
	if (aktualnePolozenie.Y < 18)
	{
		mozliwePola[iloscWolnych] = { aktualnePolozenie.X, aktualnePolozenie.Y + 2 };
		iloscWolnych++;
	}
	if (aktualnePolozenie.X > 1)
	{
		mozliwePola[iloscWolnych] = { aktualnePolozenie.X - 2, aktualnePolozenie.Y };
		iloscWolnych++;
	}
	int losowa = rand() % iloscWolnych;
	poruszSie(swiat, mozliwePola[losowa]);
}
void Antylopa::kolizja(world::Swiat* swiat)
{
	Organizm* drugi = swiat->getOrganizm(aktualnePolozenie, this);
	if (drugi != NULL)
	{
		if (drugi->getTyp() == typ)
		{
			rozmnazajSie(swiat);
		}
		else {
			drugi->walcz(swiat, this);
		}
	}
}
Lis::Lis(int x, int y)
{
	sila = 3;
	inicjatywa = 7;
	wiek = 0;
	aktualnePolozenie.X = poprzedniePolozenie.X = x;
	aktualnePolozenie.Y = poprzedniePolozenie.Y = y;
	wyglad = 'L';
	typ = LIS;
}
Lis::Lis(COORD aktualne, COORD poprzednie, int sila, int wiek)
{
	this->sila = sila;
	inicjatywa = 5;
	this->wiek = wiek;
	aktualnePolozenie = aktualne;
	poprzedniePolozenie = poprzednie;
	wyglad = 'L';
	typ = LIS;
}
Lis::~Lis()
{

}
void Lis::akcja(world::Swiat* swiat)
{
	COORD nowe_pole = wylosujSasiedniePole();
	if (swiat->getPole(nowe_pole.X, nowe_pole.Y) != PUSTE)
	{
		Organizm* naDocelowym = swiat->getOrganizm(nowe_pole);
		if (naDocelowym->getSila() > sila) return;
	}
	poruszSie(swiat, nowe_pole);
}
void Lis::kolizja(world::Swiat* swiat)
{
	Organizm* drugi = swiat->getOrganizm(aktualnePolozenie, this);
	if (drugi != NULL)
	{
		if (drugi->getTyp() == typ)
		{
			rozmnazajSie(swiat);
		}
		else {
			drugi->walcz(swiat, this);
		}
	}
}
Czlowiek::Czlowiek(int x, int y)
{
	pozostalyCooldown = 0;
	sila = 5;
	inicjatywa = 4;
	wiek = 0;
	aktualnePolozenie.X = poprzedniePolozenie.X = x;
	aktualnePolozenie.Y = poprzedniePolozenie.Y = y;
	wyglad = 'C';
	typ = CZLOWIEK;
}
Czlowiek::Czlowiek(COORD aktualne, COORD poprzednie, int sila, int wiek, int pozostalyCooldown)
{
	this->sila = sila;
	inicjatywa = 5;
	this->wiek = wiek;
	this->pozostalyCooldown = pozostalyCooldown;
	aktualnePolozenie = aktualne;
	poprzedniePolozenie = poprzednie;
	wyglad = 'C';
	typ = CZLOWIEK;
}
Czlowiek::~Czlowiek()
{

}
bool Czlowiek::poprawneWprowadzenie(WCISNIETY_KLAWISZ klawisz)
{
	try
	{
		if (klawisz == ABILITY)
		{
			if (pozostalyCooldown > 0)throw new WyjatekUmiejetnoscNieaktywna(pozostalyCooldown);
			else return true;
		}
		switch (klawisz)
		{
		case ARROW_UP:
			if (aktualnePolozenie.Y > 0)return true;
			else throw new WyjatekWejscieNaSciane(aktualnePolozenie);
			return false;
		case ARROW_DOWN:
			if (aktualnePolozenie.Y < 19) return true;
			else throw new WyjatekWejscieNaSciane(aktualnePolozenie);
			return false;
		case ARROW_LEFT:
			if (aktualnePolozenie.X > 0) return true;
			else throw new WyjatekWejscieNaSciane(aktualnePolozenie);
			return false;
		case ARROW_RIGHT:
			if (aktualnePolozenie.X < 19) return true;
			else throw new WyjatekWejscieNaSciane(aktualnePolozenie);
			return false;
		}
	}
	catch (WyjatekWprowadzenie* w)
	{
		w->wypiszKomunikat();
		return false;
	}
	
}

void Czlowiek::wyswietlAnimacjeUmiejetnosci()
{
	char losowy;
	COORD centralne = aktualnePolozenie;
	centralne.Y++;
	centralne.X++;
	for (int i = 0; i < 20; i++)
	{
		losowy = rand() % 127 + 33; //<33;126> - przedzial bez bialych znakow i podobnych
		ObslugaKonsoli::gotoxy(centralne.X - 1, centralne.Y - 1);
		cout << losowy;
		ObslugaKonsoli::gotoxy(centralne.X, centralne.Y - 1);
		cout << losowy;
		ObslugaKonsoli::gotoxy(centralne.X + 1, centralne.Y - 1);
		cout << losowy;
		ObslugaKonsoli::gotoxy(centralne.X + 1, centralne.Y);
		cout << losowy;
		ObslugaKonsoli::gotoxy(centralne.X + 1, centralne.Y + 1);
		cout << losowy;
		ObslugaKonsoli::gotoxy(centralne.X, centralne.Y + 1);
		cout << losowy;
		ObslugaKonsoli::gotoxy(centralne.X - 1, centralne.Y + 1);
		cout << losowy;
		ObslugaKonsoli::gotoxy(centralne.X - 1, centralne.Y);
		cout << losowy;
		Sleep(50);
	}
}

void Czlowiek::Umiejetnosc(world::Swiat* swiat)
{
	pozostalyCooldown = 5;
	COORD sasiedniePola[8];
	Organizm* doZniszczenia;
	sasiedniePola[0] = { aktualnePolozenie.X - 1, aktualnePolozenie.Y - 1 };
	sasiedniePola[1] = { aktualnePolozenie.X, aktualnePolozenie.Y - 1 };
	sasiedniePola[2] = { aktualnePolozenie.X + 1, aktualnePolozenie.Y - 1 };
	sasiedniePola[3] = { aktualnePolozenie.X + 1, aktualnePolozenie.Y };
	sasiedniePola[4] = { aktualnePolozenie.X + 1, aktualnePolozenie.Y + 1 };
	sasiedniePola[5] = { aktualnePolozenie.X, aktualnePolozenie.Y + 1 };
	sasiedniePola[6] = { aktualnePolozenie.X - 1, aktualnePolozenie.Y + 1 };
	sasiedniePola[7] = { aktualnePolozenie.X - 1, aktualnePolozenie.Y };
	for (int i = 0; i < 8; i++)
	{
		if (sasiedniePola[i].X >= 0 && sasiedniePola[i].X < 20 && sasiedniePola[i].Y >= 0 && sasiedniePola[i].Y < 20)
		{
			if (swiat->getPole(sasiedniePola[i].X, sasiedniePola[i].Y) != PUSTE)
			{
				doZniszczenia = swiat->getOrganizm(sasiedniePola[i]);
				swiat->getDoUsuniecia()->dodajOrganizm(doZniszczenia);
				swiat->setPole(sasiedniePola[i], PUSTE);
			}
		}
	}
	wyswietlAnimacjeUmiejetnosci();
}

void Czlowiek::akcja(world::Swiat* swiat)
{
	bool poprawnyKlawisz;
	if (pozostalyCooldown > 0) pozostalyCooldown--;
	WCISNIETY_KLAWISZ wprowadzenie;
	do
	{
		poprawnyKlawisz = false;
		wprowadzenie = ObslugaKonsoli::pobierzWprowadzenie();
		poprawnyKlawisz = poprawneWprowadzenie(wprowadzenie);
		if (wprowadzenie == SAVE) swiat->zapiszStanSwiata();
	} while (!poprawneWprowadzenie(wprowadzenie) || wprowadzenie == SAVE);
	if (wprowadzenie == QUIT) swiat->zakoncz();
	COORD nowePole;
	switch (wprowadzenie)
	{
	case ABILITY:
		Umiejetnosc(swiat);
		break;
	case ARROW_DOWN:
		nowePole = { aktualnePolozenie.X, aktualnePolozenie.Y + 1 };
		break;
	case ARROW_UP:
		nowePole = { aktualnePolozenie.X, aktualnePolozenie.Y - 1 };
		break;
	case ARROW_LEFT:
		nowePole = { aktualnePolozenie.X - 1, aktualnePolozenie.Y };
		break;
	case ARROW_RIGHT:
		nowePole = { aktualnePolozenie.X + 1, aktualnePolozenie.Y };
		break;
	case LOAD:
		swiat->wczytajStanSwiata();
		break;
	}
	
	if (wprowadzenie != ABILITY && wprowadzenie != LOAD && wprowadzenie != QUIT) poruszSie(swiat, nowePole);
}
void Czlowiek::kolizja(world::Swiat* swiat)
{
	Organizm* drugi = swiat->getOrganizm(aktualnePolozenie, this);
	if (drugi != NULL)
	{
		if (drugi->getTyp() == typ)
		{
			rozmnazajSie(swiat);
		}
		else {
			drugi->walcz(swiat, this);
		}
	}
}

string Czlowiek::toString()
{
	string opis;
	opis = typJakoString() + " " + to_string(sila) + " " + to_string(wiek) + " " + to_string(aktualnePolozenie.X) + " "
		+ to_string(aktualnePolozenie.Y) + " " + to_string(poprzedniePolozenie.X) + " " + to_string(poprzedniePolozenie.Y)
		+ " " + to_string(pozostalyCooldown) + "\n";
	return opis;
}