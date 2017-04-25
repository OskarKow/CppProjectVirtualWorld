#include "Swiat.h"
#include "Organizm.h"
#include "ObslugaKonsoli.h"
#include "Zwierzeta.h"
#include "Rosliny.h"
#include <windows.h>
#include <conio.h>
#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>
using namespace world;
using namespace std;
using namespace console;
using namespace organism;
using namespace animal;
using namespace plant;
using namespace informations;

Swiat::Swiat()
{
	oknoInformacji = new OknoInformacji();
	numerTury = 0;
	symulacjaTrwa = true;
	srand(time(NULL));
	plansza = new TYP_ORGANIZMU*[20];
	for (int i = 0; i < 20; i++)
	{
		plansza[i] = new TYP_ORGANIZMU[20];
	}
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			plansza[i][j] = PUSTE;
		}
	}
	kontener = new KontenerOrganizmow();
	doDodania = new KontenerOrganizmow();
	doUsuniecia = new KontenerOrganizmow();
	TYP_ORGANIZMU typy[10] = { WILK, OWCA, ZOLW, ANTYLOPA, LIS, TRAWA, MLECZ, GUARANA, JAGODY, CZLOWIEK };
	COORD wspolrzedne[19];
	bool powtarzaSie = false;
	SHORT randX, randY;
	for (int i = 0; i < 19; i++)
	{
		do
		{
			randX = rand() % 20;
			randY = rand() % 20;
			wspolrzedne[i] = { randX, randY };
			for (int j = 0; j < i; j++)
			{
				if (wspolrzedne[i].X == wspolrzedne[j].X && wspolrzedne[i].Y == wspolrzedne[j].Y)
				{
					powtarzaSie = true;
					break;
				}
				if (j == i - 1) powtarzaSie = false;
			}
		} while (powtarzaSie);
		doDodania->dodajOrganizm(stworzOrganizm(randX, randY, typy[i / 2]));
	}
}
Swiat::~Swiat()
{
	delete oknoInformacji;
	delete kontener;
	delete doUsuniecia;
	delete doDodania;
}
organism::Organizm* Swiat::getOrganizm(COORD wspolrzedne)
{
	Organizm* aktualny = NULL;
	for (int i = 0; i < kontener->getIloscOrganizmow(); i++)
	{
		aktualny = kontener->getOrganizm(i);
		if (aktualny->getAktualnePolozenie().X == wspolrzedne.X && aktualny->getAktualnePolozenie().Y == wspolrzedne.Y)
		{
			if (!doUsuniecia->czyZawiera(aktualny)) return aktualny;
		}
	}
}

organism::Organizm* Swiat::getOrganizm(COORD wspolrzedne, organism::Organizm* do_pominiecia)
{
	Organizm* aktualny = NULL;
	for (int i = 0; i < kontener->getIloscOrganizmow(); i++)
	{
		aktualny = kontener->getOrganizm(i);
		if (aktualny->getAktualnePolozenie().X == wspolrzedne.X && aktualny->getAktualnePolozenie().Y == wspolrzedne.Y)
		{
			if (aktualny != do_pominiecia)
			{
				if(!doUsuniecia->czyZawiera(aktualny)) return aktualny;
			}
		}
	}
	return NULL;
}

void Swiat::rysujSwiat()
{
	system("cls");
	ObslugaKonsoli::gotoxy(0, 0);
	for (int i = 0; i < 22; i++)
	{
		if (i == 0 || i == 21) cout << " --------------------\n";
		else cout << "|                    |\n";
	}
	for (int i = 0; i < kontener->getIloscOrganizmow(); i++)
	{
		kontener->getOrganizm(i)->rysuj();
	}
	oknoInformacji->wyswietlKomunikaty();
}

COORD Swiat::wylosujWolnePole(COORD centralne)
{
	int iloscWolnych = 0;
	COORD wolne[4];
	
	if (centralne.Y > 0 && plansza[centralne.Y - 1][centralne.X] == PUSTE)
	{
		wolne[iloscWolnych].X = centralne.X;
		wolne[iloscWolnych].Y = centralne.Y - 1;
		iloscWolnych++;
	}
	if (centralne.X < 19 && plansza[centralne.Y][centralne.X + 1] == PUSTE)
	{
		wolne[iloscWolnych].X = centralne.X + 1;
		wolne[iloscWolnych].Y = centralne.Y;
		iloscWolnych++;
	}
	if (centralne.Y < 19 && plansza[centralne.Y + 1][centralne.X] == PUSTE)
	{
		wolne[iloscWolnych].X = centralne.X;
		wolne[iloscWolnych].Y = centralne.Y + 1;
		iloscWolnych++;
	}
	if (centralne.X > 0 && plansza[centralne.Y][centralne.X - 1] == PUSTE)
	{
		wolne[iloscWolnych].X = centralne.X - 1;
		wolne[iloscWolnych].Y = centralne.Y;
		iloscWolnych++;
	}
	//zwracamy flage -1, -1 gdy nie znaleziono wolnego pola
	if (iloscWolnych == 0)
	{
		wolne[0] = { -1,-1 };
		return wolne[0];
	}
	int indeks = rand() % iloscWolnych;
	return wolne[indeks];
}

organism::Organizm* Swiat::stworzOrganizm(int x, int y, TYP_ORGANIZMU typ)
{
	switch (typ)
	{
	case WILK:
		return new Wilk(x, y);
	case ANTYLOPA:
		return new Antylopa(x, y);
	case OWCA:
		return new Owca(x, y);
	case LIS:
		return new Lis(x, y);
	case ZOLW:
		return new Zolw(x, y);
	case CZLOWIEK:
		return new Czlowiek(x, y);
	case TRAWA:
		return new Trawa(x, y);
	case MLECZ:
		return new Mlecz(x, y);
	case GUARANA:
		return new Guarana(x, y);
	case JAGODY:
		return new WilczeJagody(x, y);
	}
}

organism::Organizm* Swiat::stworzOrganizm(COORD aktualne, COORD poprzednie, int sila, int wiek, TYP_ORGANIZMU typ, int pozostalyCooldown)
{
	switch (typ)
	{
	case WILK:
		return new Wilk(aktualne, poprzednie, sila, wiek);
	case ANTYLOPA:
		return new Antylopa(aktualne, poprzednie, sila, wiek);
	case OWCA:
		return new Owca(aktualne, poprzednie, sila, wiek);
	case LIS:
		return new Lis(aktualne, poprzednie, sila, wiek);
	case ZOLW:
		return new Zolw(aktualne, poprzednie, sila, wiek);
	case CZLOWIEK:
		return new Czlowiek(aktualne, poprzednie, sila, wiek, pozostalyCooldown);
	case TRAWA:
		return new Trawa(aktualne, poprzednie, sila, wiek);
	case MLECZ:
		return new Mlecz(aktualne, poprzednie, sila, wiek);
	case GUARANA:
		return new Guarana(aktualne, poprzednie, sila, wiek);
	case JAGODY:
		return new WilczeJagody(aktualne, poprzednie, sila, wiek);
	}
}

void Swiat::uruchom()
{
	przepiszDoDodania();
	usunDoUsuniecia();
	while (symulacjaTrwa)
	{
		rysujSwiat();
		rysujSterowanie();
		wykonajTure();
		for (int i = 0; i < kontener->getIloscOrganizmow(); i++)
		{
			kontener->getOrganizm(i)->zwiekszWiek();
		}
	}
}

void Swiat::wykonajTure()
{
	numerTury++;
	Organizm* aktualny = NULL;
	for (int i = 0; i < kontener->getIloscOrganizmow(); i++)
	{
		aktualny = kontener->getOrganizm(i);
		if (!doUsuniecia->czyZawiera(aktualny))
		{
			aktualny->akcja(this);
		}
	}
	przepiszDoDodania();
	usunDoUsuniecia();
}

void Swiat::przepiszDoDodania()
{
	Organizm* current = NULL;
	COORD currentCoord;
	for (int i = 0; i < doDodania->getIloscOrganizmow(); i++)
	{
		current = doDodania->getOrganizm(i);
		currentCoord = current->getAktualnePolozenie();

		kontener->dodajOrganizm(current);
		plansza[currentCoord.Y][currentCoord.X] = current->getTyp();//ustawiam pole w planszy
	}
	doDodania->wyczysc();
}

void Swiat::usunDoUsuniecia()
{
	for (int i = 0; i < doUsuniecia->getIloscOrganizmow(); i++)
	{
		kontener->usunOrganizm(doUsuniecia->getOrganizm(i));
	}
	doUsuniecia->wyczysc();
}

void Swiat::rysujSterowanie()
{
	ObslugaKonsoli::gotoxy(0, 23);
	cout << (char)16 << (char)17 << (char)30 << (char)31 << " - PORUSZANIE              U - UMIEJETNOSC";
	ObslugaKonsoli::gotoxy(0, 24);
	cout << "Z - Zapisz stan swiata         W - Wczytaj ostatni zapis         Q - Zakoncz";
}

void Swiat::zapiszStanSwiata()
{
	/*
	nrTury
	kontener ogolny
	kontener doDodania
	kontenerDoUsuniecia
	oknoInformacji
	*/
	ofstream doZapisu;
	doZapisu.open("StanSwiata.txt");
	if (doZapisu.is_open())
	{
		doZapisu << numerTury << "\n";
		doZapisu << kontener->toString();
		doZapisu << doDodania->toString();
		doZapisu << doUsuniecia->toString();
		doZapisu << oknoInformacji->toString();
	}
	doZapisu.close();
}

void Swiat::wyczyscStanSwiata()
{
	numerTury = 0;
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			plansza[i][j] = PUSTE;
		}
	}
	delete oknoInformacji;
	delete kontener;
	delete doDodania;
	delete doUsuniecia;
	oknoInformacji = new OknoInformacji();
	kontener = new KontenerOrganizmow();
	doDodania = new KontenerOrganizmow();
	doUsuniecia = new KontenerOrganizmow();
}

void Swiat::wczytajStanSwiata()
{
	wyczyscStanSwiata();
	ifstream plik("StanSwiata.txt");
	int rozmiarKontener, iloscKomunikatow;
	string linia, stringTyp;
	stringstream *stream = NULL;
	int sila, wiek,pozostalyCooldown = 0;
	COORD aktualnePolozenie, poprzedniePolozenie;
	TYP_ORGANIZMU typ;
	if (plik.is_open())
	{
		plik >> numerTury;
		for (int j = 0; j < 3; j++) //3 kontenery
		{
			plik >> rozmiarKontener;
			getline(plik, linia);
			for (int i = 0; i < rozmiarKontener; i++)
			{
				getline(plik, linia);
				stream = new stringstream(linia);
				*stream >> stringTyp;
				typ = Organizm::stringToTyp(stringTyp);
				*stream >> sila;
				*stream >> wiek;
				*stream >> aktualnePolozenie.X;
				*stream >> aktualnePolozenie.Y;
				*stream >> poprzedniePolozenie.X;
				*stream >> poprzedniePolozenie.Y;
				if (typ == CZLOWIEK) *stream >> pozostalyCooldown;
				if (j < 2) doDodania->dodajOrganizm(stworzOrganizm(aktualnePolozenie, poprzedniePolozenie, sila, wiek, typ, pozostalyCooldown));
				else doUsuniecia->dodajOrganizm(stworzOrganizm(aktualnePolozenie, poprzedniePolozenie, sila, wiek, typ, pozostalyCooldown));
				delete stream;
			}
		}
		plik >> iloscKomunikatow;
		for (int i = 0; i < iloscKomunikatow; i++)
		{
			getline(plik, linia);
			oknoInformacji->dodajString(linia);
		}
	}
	plik.close();
	uruchom();
}

void Swiat::zakoncz()
{
	symulacjaTrwa = false;
}