#include <iostream>
#include <ctime>
#include <windows.h>
#include <stdlib.h>
#include "Organizm.h"
#include "ObslugaKonsoli.h"
using namespace organism;
using namespace console;
using namespace std;

void Organizm::rysuj()
{
	ObslugaKonsoli::gotoxy(aktualnePolozenie.X + 1, aktualnePolozenie.Y + 1);
	cout << wyglad;
}

string Organizm::toString()
{
	string opis;
	opis = typJakoString() + " " + to_string(sila) + " " + to_string(wiek) + " " + to_string(aktualnePolozenie.X) + " "
		+ to_string(aktualnePolozenie.Y) + " " + to_string(poprzedniePolozenie.X) + " " + to_string(poprzedniePolozenie.Y) + "\n";
	return opis;
}

TYP_ORGANIZMU Organizm::stringToTyp(string typ)
{
	if (typ == "Wilk") return WILK;
	if (typ == "Owca") return OWCA;
	if (typ == "Zolw") return ZOLW;
	if (typ == "Lis") return LIS;
	if (typ == "Antylopa") return ANTYLOPA;
	if (typ == "Czlowiek") return CZLOWIEK;
	if (typ == "Trawa") return TRAWA;
	if (typ == "Guarana") return GUARANA;
	if (typ == "Mlecz") return MLECZ;
	if (typ == "Jagody") return JAGODY;
}

KontenerOrganizmow::KontenerOrganizmow()
{
	iloscOrganizmow = 0;
	organizmy = NULL;
}
KontenerOrganizmow::~KontenerOrganizmow()
{
	delete[] organizmy;
}

void KontenerOrganizmow::dodajOrganizm(Organizm *nowy)
{
	iloscOrganizmow++;
	Organizm **nowa = new Organizm*[iloscOrganizmow];
	for (int i = 0; i < iloscOrganizmow - 1; i++)
	{
		nowa[i] = organizmy[i];
	}
	nowa[iloscOrganizmow - 1] = nowy;
	this->organizmy = nowa;
	posortujOrganizmy();
}

void KontenerOrganizmow::usunOrganizm(Organizm* doUsuniecia)
{
	if (iloscOrganizmow > 0)
	{
		iloscOrganizmow--;
		Organizm** nowa = new Organizm*[iloscOrganizmow];
		int iloscPrzepisanych = 0;
		for (int i = 0; i < iloscOrganizmow + 1; i++)
		{
			if (organizmy[i] != doUsuniecia)
			{
				nowa[iloscPrzepisanych] = organizmy[i];
				iloscPrzepisanych++;
			}
		}
		this->organizmy = nowa;
		posortujOrganizmy();
	}
	delete doUsuniecia;
}

bool KontenerOrganizmow::porownajOrganizmy(Organizm* organizmA, Organizm* organizmB)
{
	if (organizmA->getInicjatywa() > organizmB->getInicjatywa()) return true;
	if (organizmA->getInicjatywa() < organizmB->getInicjatywa()) return false;
	if (organizmA->getInicjatywa() == organizmB->getInicjatywa())
	{
		if (organizmA->getWiek() >= organizmB->getWiek()) return true;
		if (organizmA->getWiek() < organizmB->getWiek()) return false;
	}
}

void KontenerOrganizmow::posortujOrganizmy()
{
	Organizm* tmp = NULL;
	for (int i = 0; i < iloscOrganizmow - 1; i++)
	{
		for (int j = 0; j < iloscOrganizmow - 1; j++)
		{
			if (!porownajOrganizmy(organizmy[j], organizmy[j + 1]))
			{
				tmp = organizmy[j + 1];
				organizmy[j + 1] = organizmy[j];
				organizmy[j] = tmp;
			}
		}
	}
}

void KontenerOrganizmow::wyczysc()
{
	organizmy = NULL;
	iloscOrganizmow = 0;
}

bool KontenerOrganizmow::czyZawiera(organism::Organizm* organizm)
{
	for (int i = 0; i < iloscOrganizmow; i++)
	{
		if (organizmy[i] == organizm) return true;
	}
	return false;
}

string KontenerOrganizmow::toString()
{
	string wynik;
	wynik = to_string(iloscOrganizmow) + "\n";
	for (int i = 0; i < iloscOrganizmow; i++)
	{
		wynik += organizmy[i]->toString();
	}
	return wynik;
}
