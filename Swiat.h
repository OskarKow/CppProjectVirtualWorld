#pragma once
#include "Organizm.h"
#include "OknoInformacji.h"
#include <windows.h>

enum TYP_ORGANIZMU;
namespace organism
{
	class Organizm;
	class KontenerOrganizmow;
}
namespace informations
{
	class OknoInformacji;
}

namespace world
{
	class Swiat
	{
	private:
		informations::OknoInformacji* oknoInformacji;
		organism::KontenerOrganizmow* kontener; //organizmy na planszy
		organism::KontenerOrganizmow* doDodania; //organizmy ktore trzeba dodac do kontenera na koniec tury
		organism::KontenerOrganizmow* doUsuniecia; //organzmy ktore trzeba usunac z kontenera na koniec tury
		TYP_ORGANIZMU **plansza;
		int numerTury;
		void przepiszDoDodania();
		void usunDoUsuniecia();
		bool symulacjaTrwa;
	public:
		void uruchom();
		void wykonajTure();
		void rysujSwiat();
		void rysujSterowanie();
		void zapiszStanSwiata();
		void wczytajStanSwiata();
		void wyczyscStanSwiata();//ustawia swiat na pusty
		void zakoncz();
		Swiat();
		~Swiat();
		organism::Organizm* getOrganizm(COORD wspolrzedne);//zwraca organizm na podanych wspolrzednych
		organism::Organizm* getOrganizm(COORD wspolrzedne, organism::Organizm* do_pominiecia);//zwraca organizm na x,y pomijajac ten podany jako argument
		informations::OknoInformacji* getOknoInformacji() { return oknoInformacji; }
		TYP_ORGANIZMU getPole(int x, int y) { return plansza[y][x]; }
		void setPole(COORD pole, TYP_ORGANIZMU typ) { plansza[pole.Y][pole.X] = typ; }
		COORD wylosujWolnePole(COORD centralne); //losuje wolne pole sasiadujace z centralnym
		organism::Organizm* stworzOrganizm(int x, int y, TYP_ORGANIZMU typ);
		organism::Organizm* stworzOrganizm(COORD aktualne, COORD poprzednie, int sila, int wiek, TYP_ORGANIZMU typ, int pozostalyCooldown = 0);//do wczytywania
		organism::KontenerOrganizmow* getKontener() { return kontener; }
		int getNumerTury() { return numerTury; }
		organism::KontenerOrganizmow* getDoUsuniecia() { return doUsuniecia; }
		organism::KontenerOrganizmow* getDoDodania() { return doDodania; }
	};
}
