#pragma once

enum WCISNIETY_KLAWISZ
{
	ABILITY,
	SAVE,
	LOAD,
	QUIT,
	ARROW_UP,
	ARROW_DOWN,
	ARROW_LEFT,
	ARROW_RIGHT
};

#define GORA 0x48
#define DOL 0x50
#define LEWO 0x4b
#define PRAWO 0x4d

namespace console
{
	class ObslugaKonsoli
	{
	public:
		static void gotoxy(int x, int y);
		static WCISNIETY_KLAWISZ pobierzWprowadzenie();
	};
}
