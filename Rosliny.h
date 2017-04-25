#pragma once
#include "Organizm.h"
#include <string>

#define SZANSA_ZASIANIA 3 //[%]

namespace plant
{
	class Roslina : public organism::Organizm
	{
	public:
		void rozprzestrzeniajSie(world::Swiat* swiat);
		virtual void walcz(world::Swiat* swiat, organism::Organizm* napastnik);
	};

	class Trawa : public Roslina
	{
	public:
		Trawa(int x, int y);
		Trawa(COORD aktualne, COORD poprzednie, int sila, int wiek);
		~Trawa();
		void akcja(world::Swiat* swiat);
		std::string typJakoString() { return "Trawa"; }
	};
	class Mlecz : public Roslina
	{
	public:
		Mlecz(int x, int y);
		Mlecz(COORD aktualne, COORD poprzednie, int sila, int wiek);
		~Mlecz();
		void akcja(world::Swiat* swiat);
		std::string typJakoString() { return "Mlecz"; }
	};
	class Guarana : public Roslina
	{
	public:
		Guarana(int x, int y);
		Guarana(COORD aktualne, COORD poprzednie, int sila, int wiek);
		~Guarana();
		void walcz(world::Swiat* swiat, organism::Organizm* napastnik);
		void akcja(world::Swiat* swiat);
		std::string typJakoString() { return "Guarana"; }
	};
	class WilczeJagody : public Roslina
	{
	public:
		WilczeJagody(int x, int y);
		WilczeJagody(COORD aktualne, COORD poprzednie, int sila, int wiek);
		~WilczeJagody();
		void akcja(world::Swiat* swiat);
		void walcz(world::Swiat* swiat, organism::Organizm* napastnik);
		std::string typJakoString() { return "Jagody"; }
	};
}
