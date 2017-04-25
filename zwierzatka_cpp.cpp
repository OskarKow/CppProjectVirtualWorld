
#include "stdafx.h"
#include "Swiat.h"
#include "Organizm.h"
#include "Zwierzeta.h"
#include "Rosliny.h"
#include "ObslugaKonsoli.h"
#include <windows.h>
using namespace world;

int main()
{
	SetConsoleTitle(_T("Oskar Kowalewski 160359"));
	Swiat* swiat = new Swiat();
	swiat->uruchom();
	delete swiat;
    return 0;
}

