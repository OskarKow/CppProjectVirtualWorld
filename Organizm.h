#pragma once
#include "Swiat.h"
#include <windows.h>
#include <string>

enum TYP_ORGANIZMU//przechowuje stan pola
{
	WILK,
	ANTYLOPA,
	OWCA,
	LIS,
	ZOLW,
	CZLOWIEK,
	TRAWA,
	GUARANA,
	MLECZ,
	JAGODY,
	PUSTE
};

namespace world
{
	class Swiat;
}

namespace organism
{
	class Organizm
	{
	protected:
		int sila;
		int inicjatywa;
		int wiek;
		COORD aktualnePolozenie;
		COORD poprzedniePolozenie;
		char wyglad;
		TYP_ORGANIZMU typ;
	public:
		virtual void akcja(world::Swiat* swiat) = 0; //akcja wywo³ywana na pocz¹tku tury(poruszanie)
		virtual void rysuj(); //rysowanie reprezentacji organizmu
		virtual void walcz(world::Swiat* swiat, organism::Organizm* napastnik) = 0;//okresla zachowanie organizmu, gdy jest zaatakowany
		virtual std::string typJakoString()=0; //zwraca ciag znakow reprezentujacy typ organizmu
		virtual ~Organizm() {};
		int getSila() { return sila; }
		void zwiekszSile(int oIle) { sila += oIle; }
		int getInicjatywa() { return inicjatywa; }
		COORD getAktualnePolozenie() { return aktualnePolozenie; }
		void setAktualnePolozenie(COORD nowe) { aktualnePolozenie = nowe; }
		COORD getPoprzedniePolozenie() { return poprzedniePolozenie; }
		void setPoprzedniePolozenie(COORD nowe) { poprzedniePolozenie = nowe; }
		int getWiek() { return wiek; }
		void zwiekszWiek() { wiek++; }
		TYP_ORGANIZMU getTyp() { return typ; }
		virtual std::string toString();
		static TYP_ORGANIZMU stringToTyp(std::string typ);
	};

	class KontenerOrganizmow
	{
	private:
		int iloscOrganizmow;
		Organizm** organizmy;
		//zwraca true gdy A jest wiekszy lub rowny B, false w przeciwnym wypadku
		bool porownajOrganizmy(Organizm* organizmA, Organizm* organizmB);
		void posortujOrganizmy();
	public:
		KontenerOrganizmow();
		~KontenerOrganizmow();
		void dodajOrganizm(Organizm *organizm);
		void usunOrganizm(Organizm *organizm);
		int getIloscOrganizmow() { return iloscOrganizmow; }
		Organizm* getOrganizm(int indeks)
		{
			return organizmy[indeks];
		}
		void wyczysc(); //usuwa cala zawartosc kontenera
		bool czyZawiera(organism::Organizm* organizm);
		std::string toString();
	};
}