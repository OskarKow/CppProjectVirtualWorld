#include <windows.h>
#include <conio.h>
#include "ObslugaKonsoli.h"
using namespace console;

void ObslugaKonsoli::gotoxy(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

WCISNIETY_KLAWISZ ObslugaKonsoli::pobierzWprowadzenie()
{
	int klawisz;
	do
	{
		klawisz = _getch();
	} while (klawisz != 'u' && klawisz != 'z' && klawisz != 224 && klawisz != 'w' && klawisz != 'q');
	if (klawisz == 'u') return ABILITY;
	if (klawisz == 'z') return SAVE;
	if (klawisz == 'w') return LOAD;
	if (klawisz == 'q') return QUIT;
	klawisz = _getch();

	switch (klawisz)
	{
	case GORA:
		return ARROW_UP;
		break;
	case DOL:
		return ARROW_DOWN;
		break;
	case LEWO:
		return ARROW_LEFT;
		break;
	case PRAWO:
		return ARROW_RIGHT;
		break;
	}
}