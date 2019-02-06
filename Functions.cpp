#include "pch.h"
#include "Functions.h"
#include "Structures.h"

#include <iostream>
#include <conio.h>
#include <string>
#include <Windows.h>

#pragma comment(lib, "winmm.lib")

using namespace std;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void mainMenu()
{
	char choice;
	
	mainMusicStart();
	hidePointer();
	getGUIOfMenu();
	setChoiceInMainMenu(choice);

	if (choice == '1')
		startGame();
	else
		exit(0);
}

void mainMusicStart()
{
	PlaySound(TEXT("RETROGAMETHEMEWAV.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
}

void mainMusicStop()
{
	PlaySound(0, 0, 0);
}

void soundEffect(short id)
{
	if(id == 0)
		PlaySound(TEXT("splush.wav"), NULL, SND_FILENAME | SND_ASYNC);
	else if (id == 1)
		PlaySound(TEXT("boom.wav"), NULL, SND_FILENAME | SND_ASYNC);
	else if (id == 2)
		PlaySound(TEXT("victory.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void windowSize(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT ConsoleRect;
	GetWindowRect(console, &ConsoleRect);
	MoveWindow(console, ConsoleRect.left, ConsoleRect.top, width, height, TRUE);
}

void hidePointer()
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ccur;
	ccur.dwSize = sizeof(CONSOLE_CURSOR_INFO);
	ccur.bVisible = false;
	SetConsoleCursorInfo(hStdOut, &ccur);
}

void removeScrollbar()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handle, &info);
	COORD new_size =
	{
		info.srWindow.Right - info.srWindow.Left + 1,
		info.srWindow.Bottom - info.srWindow.Top + 1
	};
	SetConsoleScreenBufferSize(handle, new_size);
}

void getGUIOfMenu()
{
	SetConsoleTextAttribute(hConsole, sky);
	cout << endl << endl << "\t  __________         __    __  .__                .__    .__";
	cout << "\n\t  \\______   \\_____ _/  |__/  |_|  |   ____   _____|  |__ |__|_____";
	cout << "\n\t  |    |  _/\\__  \\\\   __\\   __\\  | _/ __ \\ /  ___/  |  \\|  \\____ \\";
	cout << "\n\t  |    |   \\ / __ \\|  |  |  | |  |_\\  ___/ \\___ \\|   Y  \\  |  |_> >";
	cout << "\n\t  |______  /(____  /__|  |__| |____/\\___  >____  >___|  /__|   __/";
	cout << "\n\t         \\/      \\/                     \\/     \\/     \\/   |__|";

	SetConsoleTextAttribute(hConsole, purple);
	cout << "\n\t\t\t\t\t\tby Daniel Jambor";

	SetConsoleTextAttribute(hConsole, green);
	cout << "\n\n\n\n\t\t\t\t     1.START";
	cout << "\n\n\t\t\t\t     2.WYJSCIE";

	SetConsoleTextAttribute(hConsole, defaultColor);
}

void setChoiceInMainMenu(char &x)
{
	while (true)
	{
		x = _getch();

		if (x == '1' || x == '2')
			break;
	}
}

void startGame()
{
	Battlefield player1Battlefield;
	Battlefield player2Battlefield;

	player1Battlefield.playerNumber = 1;
	player2Battlefield.playerNumber = 2;

	player1Battlefield.setPlayerName();
	player2Battlefield.setPlayerName();

	player1Battlefield.setDefaultFields();
	player2Battlefield.setDefaultFields();

	system("cls");

	player1Battlefield.setShips();
	player2Battlefield.setShips();

	mainMusicStop();

	startBattle(player1Battlefield, player2Battlefield);

	system("PAUSE");
	system("cls");
}

void startBattle(Battlefield x, Battlefield y)
{
	while (true)
	{
		playerTurn(x, y);
		playerTurn(y, x);
	}
}

bool isShipNearby(Battlefield x, short coordX, short coordY)
{
	if ((x.field[coordX + 1][coordY].isShipOn && !x.field[coordX + 1][coordY].isHit) || (x.field[coordX - 1][coordY].isShipOn && !x.field[coordX - 1][coordY].isHit) || (x.field[coordX][coordY + 1].isShipOn && !x.field[coordX][coordY + 1].isHit) || (x.field[coordX][coordY - 1].isShipOn && !x.field[coordX][coordY - 1].isHit))
		return false;

	return true;
}

void playerTurn(Battlefield &x, Battlefield &y)
{
	Battlefield xe = y;
	Battlefield ye = x;

	short firstCoord;
	short secondCoord;
	string tempCoords;

	xe.updateEnemyFields();
	ye.updateEnemyFields();

	system("cls");

	SetConsoleTextAttribute(hConsole, yellow);
	cout << "\n\n\t < ";

	SetConsoleTextAttribute(hConsole, green);
	cout << "TURA ";

	SetConsoleTextAttribute(hConsole, yellow);
	cout << "> ";

	SetConsoleTextAttribute(hConsole, defaultColor);
	cout << "Teraz nastapi tura gracza ";

	SetConsoleTextAttribute(hConsole, purple);
	cout << x.playerName;
	SetConsoleTextAttribute(hConsole, defaultColor);
	
	SetConsoleTextAttribute(hConsole, yellow);
	cout << "\n\n\t < ";

	SetConsoleTextAttribute(hConsole, red);
	cout << "KOMUNIKAT ";

	SetConsoleTextAttribute(hConsole, yellow);
	cout << "> ";

	SetConsoleTextAttribute(hConsole, defaultColor);
	cout << "Nacisnij dowolny klawisz...";

	_getch();
	
	while (true)
	{
		system("cls");

		xe.getBattlefield();
		x.getBattlefield();

		SetConsoleTextAttribute(hConsole, yellow);
		cout << "\n\t < ";

		SetConsoleTextAttribute(hConsole, green);
		cout << "TURA GRACZA ";

		SetConsoleTextAttribute(hConsole, purple);
		cout << x.playerName;

		SetConsoleTextAttribute(hConsole, yellow);
		cout << "> ";

		SetConsoleTextAttribute(hConsole, yellow);
		cout << "\n\n\t < ";

		SetConsoleTextAttribute(hConsole, blue);
		cout << "WYBOR ";

		SetConsoleTextAttribute(hConsole, yellow);
		cout << "> ";

		SetConsoleTextAttribute(hConsole, defaultColor);
		cout << "Gdzie chcesz strzelic (np. A1): ";

		SetConsoleTextAttribute(hConsole, purple);
		
		while (true)
		{
			cin >> tempCoords;

			if (areCoordsCorrect(tempCoords))
			{
				secondCoord = (short)(toupper(tempCoords[0])) - 65;
				firstCoord = (short)(tempCoords[1]) - 49;

				break;
			}
			else
			{
				SetConsoleTextAttribute(hConsole, yellow);
				cout << "\n\t < ";

				SetConsoleTextAttribute(hConsole, red);
				cout << "KOMUNIKAT ";

				SetConsoleTextAttribute(hConsole, yellow);
				cout << "> ";

				SetConsoleTextAttribute(hConsole, defaultColor);
				cout << "Bledne Dane! Sprobuj jeszcze raz!";

				SetConsoleTextAttribute(hConsole, yellow);
				cout << "\n\t < ";

				SetConsoleTextAttribute(hConsole, blue);
				cout << "WYBOR ";

				SetConsoleTextAttribute(hConsole, yellow);
				cout << "> ";

				SetConsoleTextAttribute(hConsole, defaultColor);
				cout << "Gdzie chcesz strzelic (np. A1): ";

				SetConsoleTextAttribute(hConsole, purple);

				cin.sync();
				cin.clear();

				continue;
			}
		}

		if (y.field[firstCoord][secondCoord].isHit)
		{
			SetConsoleTextAttribute(hConsole, yellow);
			cout << "\n\t < ";

			SetConsoleTextAttribute(hConsole, red);
			cout << "KOMUNIKAT ";

			SetConsoleTextAttribute(hConsole, yellow);
			cout << "> ";

			SetConsoleTextAttribute(hConsole, defaultColor);
			cout << "Juz tutaj strzelales!";

			SetConsoleTextAttribute(hConsole, yellow);
			cout << "\n\t < ";

			SetConsoleTextAttribute(hConsole, red);
			cout << "KOMUNIKAT ";

			SetConsoleTextAttribute(hConsole, yellow);
			cout << "> ";

			SetConsoleTextAttribute(hConsole, defaultColor);
			cout << "Nacisnij dowolny klawisz...";
			
			_getch();

			cin.sync();
			cin.clear();

			continue;
		}
		
		y.field[firstCoord][secondCoord].isHit = true;
		xe.field[firstCoord][secondCoord].isHit = true;

		y.updateFields();
		xe.updateEnemyFields();

		system("cls");

		xe.getBattlefield();
		x.getBattlefield();

		SetConsoleTextAttribute(hConsole, yellow);
		cout << "\n\t < ";

		SetConsoleTextAttribute(hConsole, green);
		cout << "TURA GRACZA ";

		SetConsoleTextAttribute(hConsole, purple);
		cout << x.playerName;

		SetConsoleTextAttribute(hConsole, yellow);
		cout << "> ";

		if (y.field[firstCoord][secondCoord].isHit && y.field[firstCoord][secondCoord].isShipOn)
		{
			soundEffect(1);

			y.healthPoints--;
			if (y.healthPoints == 0)
				x.endGame();

			if (isShipNearby(y, firstCoord, secondCoord))
			{
				SetConsoleTextAttribute(hConsole, yellow);
				cout << "\n\n\t < ";

				SetConsoleTextAttribute(hConsole, red);
				cout << "KOMUNIKAT ";

				SetConsoleTextAttribute(hConsole, yellow);
				cout << "> ";

				SetConsoleTextAttribute(hConsole, defaultColor);
				cout << "Brawo! Trafiles oraz zatopiles statek!";
			}
				
			else
			{
				SetConsoleTextAttribute(hConsole, yellow);
				cout << "\n\n\t < ";

				SetConsoleTextAttribute(hConsole, red);
				cout << "KOMUNIKAT ";

				SetConsoleTextAttribute(hConsole, yellow);
				cout << "> ";

				SetConsoleTextAttribute(hConsole, defaultColor);
				cout << "Brawo! Trafies statek!";
			}
		
			SetConsoleTextAttribute(hConsole, yellow);
			cout << "\n\t < ";

			SetConsoleTextAttribute(hConsole, red);
			cout << "KOMUNIKAT ";

			SetConsoleTextAttribute(hConsole, yellow);
			cout << "> ";

			SetConsoleTextAttribute(hConsole, defaultColor);
			cout << "Nacisnij dowolny klawisz...";
			
			_getch();

			continue;
		
		}
		else
		{
			soundEffect(0);

			SetConsoleTextAttribute(hConsole, yellow);
			cout << "\n\n\t < ";

			SetConsoleTextAttribute(hConsole, red);
			cout << "KOMUNIKAT ";

			SetConsoleTextAttribute(hConsole, yellow);
			cout << "> ";

			SetConsoleTextAttribute(hConsole, defaultColor);
			cout << "Niestety, pudlujesz!";
		}

		SetConsoleTextAttribute(hConsole, yellow);
		cout << "\n\t < ";

		SetConsoleTextAttribute(hConsole, red);
		cout << "KOMUNIKAT ";

		SetConsoleTextAttribute(hConsole, yellow);
		cout << "> ";

		SetConsoleTextAttribute(hConsole, defaultColor);
		cout << "Nacisnij dowolny klawisz...";

		_getch();

		break;
	}
}

void setCoords(short &coordX, short &coordY)
{
	string tempCoords;

	while (true)
	{
		cin >> tempCoords;
		
		if (areCoordsCorrect(tempCoords))
		{
			coordX = (short)(toupper(tempCoords[0])) - 65;
			coordY = (short)(tempCoords[1]) - 49;

			break;
		}
		else
		{
			SetConsoleTextAttribute(hConsole, yellow);
			cout << "\n\t < ";

			SetConsoleTextAttribute(hConsole, red);
			cout << "KOMUNIKAT ";

			SetConsoleTextAttribute(hConsole, yellow);
			cout << "> ";

			SetConsoleTextAttribute(hConsole, defaultColor);
			cout << "Bledne Dane! Sprobuj jeszcze raz!";

			SetConsoleTextAttribute(hConsole, yellow);
			cout << "\n\t < ";

			SetConsoleTextAttribute(hConsole, blue);
			cout << "WYBOR ";

			SetConsoleTextAttribute(hConsole, yellow);
			cout << "> ";

			SetConsoleTextAttribute(hConsole, defaultColor);
			cout << "Podaj koordynaty statku (np. A1): ";
			
			SetConsoleTextAttribute(hConsole, purple);

			cin.sync();
			cin.clear();

			continue;
		}
	}
}

bool areCoordsCorrect(string coord)
{
	if (coord.size() == 2 && (toupper(coord[0]) >= 'A' && toupper(coord[0]) <= 'I') && (coord[1] >= '1' && coord[1] <= '9'))
		return true;

	return false;
}