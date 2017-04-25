#pragma once
#include <windows.h>
#include "Organizm.h"
#include <string>

namespace world
{
	class Swiat;
}
enum WCISNIETY_KLAWISZ;

namespace animal
{
	class Zwierze : public organism::Organizm
	{
	protected:
		COORD wylosujSasiedniePole();
	public:
		virtual void kolizja(world::Swiat* swiat) = 0; //zdarzenie podczas wejscia na pole zajete przez inny organizm
		virtual void poruszSie(world::Swiat* swiat, COORD docelowe);
		virtual void rozmnazajSie(world::Swiat* swiat);
		virtual void walcz(world::Swiat* swiat, organism::Organizm* napastnik);
		virtual bool wygranaWalka(organism::Organizm* przeciwnik);//Zwraca true gdy organizm wygra walke z organizmem podanym jako argument
		virtual ~Zwierze() {};
	};
	class Wilk : public Zwierze
	{
	public:
		Wilk(int x, int y);
		Wilk(COORD aktualne, COORD poprzednie, int sila, int wiek);
		~Wilk();
		void akcja(world::Swiat* swiat);
		void kolizja(world::Swiat* swiat);
		std::string typJakoString() { return "Wilk"; }
	};
	class Owca : public Zwierze
	{
	public:
		Owca(int x, int y);
		Owca(COORD aktualne, COORD poprzednie, int sila, int wiek);
		~Owca();
		void akcja(world::Swiat* swiat);
		void kolizja(world::Swiat* swiat);
		std::string typJakoString() { return "Owca"; }
	};
	class Lis : public Zwierze
	{
	public:
		Lis(int x, int y);
		Lis(COORD aktualne, COORD poprzednie, int sila, int wiek);
		~Lis();
		void akcja(world::Swiat* swiat);
		void kolizja(world::Swiat* swiat);
		std::string typJakoString() { return "Lis"; }
	};
	class Zolw : public Zwierze
	{
	public:
		Zolw(int x, int y);
		Zolw(COORD aktualne, COORD poprzednie, int sila, int wiek);
		~Zolw();
		void walcz(world::Swiat* swiat, organism::Organizm* napastnik);
		void akcja(world::Swiat* swiat);
		void kolizja(world::Swiat* swiat);
		std::string typJakoString() { return "Zolw"; }
	};
	class Antylopa : public Zwierze
	{
	public:
		Antylopa(int x, int y);
		Antylopa(COORD aktualne, COORD poprzednie, int sila, int wiek);
		~Antylopa();
		void walcz(world::Swiat* swiat, organism::Organizm* napastnik);
		void akcja(world::Swiat* swiat);
		void kolizja(world::Swiat* swiat);
		std::string typJakoString() { return "Antylopa"; }
	};
	class Czlowiek : public Zwierze
	{
	private:
		int pozostalyCooldown;
		void Umiejetnosc(world::Swiat* swiat);
		void wyswietlAnimacjeUmiejetnosci();
	public:
		Czlowiek(int x, int y);
		Czlowiek(COORD aktualne, COORD poprzednie, int sila, int wiek, int pozostalyCooldown);
		~Czlowiek();
		void akcja(world::Swiat* swiat);
		void kolizja(world::Swiat* swiat);
		std::string typJakoString() { return "Czlowiek"; }
		bool poprawneWprowadzenie(WCISNIETY_KLAWISZ klawisz);
		std::string toString();
	};
}