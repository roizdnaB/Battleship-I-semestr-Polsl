#include "pch.h"
#include "Structures.h"
#include "Functions.h"

#include <iostream>
#include <conio.h>
#include <string>
#include <Windows.h>

using namespace std;

HANDLE hhConsole = GetStdHandle(STD_OUTPUT_HANDLE);

const string GIsClear = "   ";
const string GIsHit = " X ";
const string GIsShipOn = " O ";
const string GIsMissed = " + ";

void Battlefield::setPlayerName()
{
	while (true)
	{
		system("cls");

		SetConsoleTextAttribute(hhConsole, yellow);
		cout << "\n\n\t < ";
		
		SetConsoleTextAttribute(hhConsole, green);
		cout << "GRACZ ";

		SetConsoleTextAttribute(hhConsole, red);
		cout << playerNumber;

		SetConsoleTextAttribute(hhConsole, yellow);
		cout << " > ";

		SetConsoleTextAttribute(hhConsole, defaultColor);
		cout << "Prosze podac imie (max 15 znakow): ";

		SetConsoleTextAttribute(hhConsole, purple);
		getline(cin, playerName);
		if (playerName.size() > 15)
		{
			SetConsoleTextAttribute(hhConsole, yellow);
			cout << "\n\t < ";

			SetConsoleTextAttribute(hhConsole, red);
			cout << "KOMUNIKAT ";

			SetConsoleTextAttribute(hhConsole, yellow);
			cout << "> ";

			SetConsoleTextAttribute(hhConsole, defaultColor);
			cout << "Twoja nazwa jest za dluga!";
			
			SetConsoleTextAttribute(hhConsole, yellow);
			cout << "\n\t < ";

			SetConsoleTextAttribute(hhConsole, red);
			cout << "KOMUNIKAT ";

			SetConsoleTextAttribute(hhConsole, yellow);
			cout << "> ";

			SetConsoleTextAttribute(hhConsole, defaultColor);
			cout << "Nacisnij dowolny klawisz...";

			_getch();	
			continue;
		}
		break;
	}
}

void Battlefield::setDefaultFields()
{
	for (short i = 0; i < 10; i++)
		for (short j = 0; j < 10; j++)
		{
			field[i][j].isClear = true;
			field[i][j].isHit = false;
			field[i][j].isShipOn = false;
			field[i][j].graphicRep = GIsClear;
			field[i][j].graphicRepColorID = defaultColor;
		}
}

void Battlefield::setShips()
{
	bool goodLocation = true;

	for (short i = 0; i < 5; i++)
	{
		while (true)
		{
			goodLocation = true;

			getBattlefield();

			ship[i].lengthOfShip = 1 + i;

			SetConsoleTextAttribute(hhConsole, yellow);
			cout << "\n\n\t < ";

			SetConsoleTextAttribute(hhConsole, green);
			cout << "STATEK ";

			SetConsoleTextAttribute(hhConsole, red);
			cout << ship[i].lengthOfShip;

			SetConsoleTextAttribute(hhConsole, green);
			cout << "-ELEMENTOWY";

			SetConsoleTextAttribute(hhConsole, yellow);
			cout << " > ";

			SetConsoleTextAttribute(hhConsole, yellow);
			cout << "\n\n\t < ";

			SetConsoleTextAttribute(hhConsole, blue);
			cout << "WYBOR";

			SetConsoleTextAttribute(hhConsole, yellow);
			cout << " > ";

			SetConsoleTextAttribute(hhConsole, defaultColor);
			cout << "Podaj koordynaty statku (np. A1): ";

			SetConsoleTextAttribute(hhConsole, purple);
			setCoords(ship[i].coordX1, ship[i].coordY1);
			SetConsoleTextAttribute(hhConsole, defaultColor);


			if (ship[i].coordY1 == 0)
			{
				if (!field[ship[i].coordY1][ship[i].coordX1 + 1].isClear || !field[ship[i].coordY1][ship[i].coordX1 - 1].isClear || !field[ship[i].coordY1 + 1][ship[i].coordX1].isClear)
				{
					SetConsoleTextAttribute(hhConsole, yellow);
					cout << "\n\t < ";

					SetConsoleTextAttribute(hhConsole, red);
					cout << "KOMUNIKAT ";

					SetConsoleTextAttribute(hhConsole, yellow);
					cout << "> ";

					SetConsoleTextAttribute(hhConsole, defaultColor);
					cout << "Nie mozesz tutaj postawic statku! Sasiaduje on z innym!";

					SetConsoleTextAttribute(hhConsole, yellow);
					cout << "\n\t < ";

					SetConsoleTextAttribute(hhConsole, red);
					cout << "KOMUNIKAT ";

					SetConsoleTextAttribute(hhConsole, yellow);
					cout << "> ";

					SetConsoleTextAttribute(hhConsole, defaultColor);
					cout << "Nacisnij dowolny klawisz...";
					
					_getch();

					cin.sync();
					cin.clear();

					system("cls");
					continue;
				}

			}
			else
			{
				if (!field[ship[i].coordY1 + 1][ship[i].coordX1].isClear || !field[ship[i].coordY1 - 1][ship[i].coordX1].isClear || !field[ship[i].coordY1][ship[i].coordX1 + 1].isClear || !field[ship[i].coordY1][ship[i].coordX1 - 1].isClear || !field[ship[i].coordY1][ship[i].coordX1].isClear || !field[ship[i].coordY1 + 1][ship[i].coordX1 + 1].isClear || !field[ship[i].coordY1 + 1][ship[i].coordX1 - 1].isClear || !field[ship[i].coordY1 - 1][ship[i].coordX1 - 1].isClear || !field[ship[i].coordY1 - 1][ship[i].coordX1 + 1].isClear)
				{
					SetConsoleTextAttribute(hhConsole, yellow);
					cout << "\n\t < ";

					SetConsoleTextAttribute(hhConsole, red);
					cout << "KOMUNIKAT ";

					SetConsoleTextAttribute(hhConsole, yellow);
					cout << "> ";

					SetConsoleTextAttribute(hhConsole, defaultColor);
					cout << "Nie mozesz tutaj postawic statku! Sasiaduje on z innym!";

					SetConsoleTextAttribute(hhConsole, yellow);
					cout << "\n\t < ";

					SetConsoleTextAttribute(hhConsole, red);
					cout << "KOMUNIKAT ";

					SetConsoleTextAttribute(hhConsole, yellow);
					cout << "> ";

					SetConsoleTextAttribute(hhConsole, defaultColor);
					cout << "Nacisnij dowolny klawisz...";

					_getch();

					cin.sync();
					cin.clear();

					system("cls");
					continue;
				}
			}


			if (i == 0)
			{
				field[ship[i].coordY1][ship[i].coordX1].isClear = false;
				field[ship[i].coordY1][ship[i].coordX1].isShipOn = true;

				updateFields();
				system("cls");
			}
			else
			{
				SetConsoleTextAttribute(hhConsole, yellow);
				cout << "\n\t < ";

				SetConsoleTextAttribute(hhConsole, blue);
				cout << "WYBOR ";

				SetConsoleTextAttribute(hhConsole, yellow);
				cout << "> ";

				SetConsoleTextAttribute(hhConsole, defaultColor);
				cout << "Nacisnij 'H', jesli chcesz ustawic statek poziomo";

				SetConsoleTextAttribute(hhConsole, yellow);
				cout << "\n\t < ";

				SetConsoleTextAttribute(hhConsole, blue);
				cout << "WYBOR ";

				SetConsoleTextAttribute(hhConsole, yellow);
				cout << "> ";

				SetConsoleTextAttribute(hhConsole, defaultColor);
				cout << "Nacisnij 'V', jesli chcesz ustawic statek pionowo";

				char choice = '0';

				while (choice != 'h' && choice != 'H' && choice != 'v' && choice != 'V')
					choice = _getch();

				if (toupper(choice) == 'H')
				{
					if (ship[i].coordX1 + ship[i].lengthOfShip > 9)
					{
						SetConsoleTextAttribute(hhConsole, yellow);
						cout << "\n\n\t < ";

						SetConsoleTextAttribute(hhConsole, red);
						cout << "KOMUNIKAT ";

						SetConsoleTextAttribute(hhConsole, yellow);
						cout << "> ";

						SetConsoleTextAttribute(hhConsole, defaultColor);
						cout << "Nie mozesz tutaj postawic statku! Wychodzi poza plansze!";

						SetConsoleTextAttribute(hhConsole, yellow);
						cout << "\n\t < ";

						SetConsoleTextAttribute(hhConsole, red);
						cout << "KOMUNIKAT ";

						SetConsoleTextAttribute(hhConsole, yellow);
						cout << "> ";

						SetConsoleTextAttribute(hhConsole, defaultColor);
						cout << "Nacisnij dowolny klawisz...";
						_getch();

						cin.sync();
						cin.clear();

						system("cls");
						continue;
					}

					if (ship[i].coordY1 == 0)
					{
						for (short j = 0; j < ship[i].lengthOfShip; j++)
							if (!field[ship[i].coordY1][ship[i].coordX1 + j].isClear || !field[ship[i].coordY1][ship[i].coordX1 + j + 1].isClear || !field[ship[i].coordY1][ship[i].coordX1 + j - 1].isClear || !field[ship[i].coordY1 + 1][ship[i].coordX1 + j].isClear || !field[ship[i].coordY1 + 1][ship[i].coordX1 + j + 1].isClear || !field[ship[i].coordY1 + 1][ship[i].coordX1 + j - 1].isClear)
								goodLocation = false;
					}
					else
					{
						for (short j = 0; j < ship[i].lengthOfShip; j++)
							if (!field[ship[i].coordY1][ship[i].coordX1 + j].isClear || !field[ship[i].coordY1 + 1][ship[i].coordX1 + j].isClear || !field[ship[i].coordY1 - 1][ship[i].coordX1 + j].isClear || !field[ship[i].coordY1][ship[i].coordX1 + j + 1].isClear || !field[ship[i].coordY1][ship[i].coordX1 + j - 1].isClear || !field[ship[i].coordY1 + 1][ship[i].coordX1 + j + 1].isClear || !field[ship[i].coordY1 + 1][ship[i].coordX1 + j - 1].isClear || !field[ship[i].coordY1 - 1][ship[i].coordX1 + j - 1].isClear || !field[ship[i].coordY1 - 1][ship[i].coordX1 + j + 1].isClear)
								goodLocation = false;
					}
						
								

					if (!goodLocation)
					{
						SetConsoleTextAttribute(hhConsole, yellow);
						cout << "\n\n\t < ";

						SetConsoleTextAttribute(hhConsole, red);
						cout << "KOMUNIKAT ";

						SetConsoleTextAttribute(hhConsole, yellow);
						cout << "> ";

						SetConsoleTextAttribute(hhConsole, defaultColor);
						cout << "Nie mozesz tutaj postawic statku! Nachodzi on na inny!";

						SetConsoleTextAttribute(hhConsole, yellow);
						cout << "\n\t < ";

						SetConsoleTextAttribute(hhConsole, red);
						cout << "KOMUNIKAT ";

						SetConsoleTextAttribute(hhConsole, yellow);
						cout << "> ";

						SetConsoleTextAttribute(hhConsole, defaultColor);
						cout << "Nacisnij dowolny klawisz...";
						_getch();

						cin.sync();
						cin.clear();

						system("cls");
						continue;
					}

					for (short j = 0; j < ship[i].lengthOfShip; j++)
					{
						field[ship[i].coordY1][ship[i].coordX1 + j].isClear = false;
						field[ship[i].coordY1][ship[i].coordX1 + j].isShipOn = true;

					}
				}
				else if (toupper(choice) == 'V')
				{
					if (ship[i].coordY1 + ship[i].lengthOfShip > 9)
					{
						SetConsoleTextAttribute(hhConsole, yellow);
						cout << "\n\n\t < ";

						SetConsoleTextAttribute(hhConsole, red);
						cout << "KOMUNIKAT ";

						SetConsoleTextAttribute(hhConsole, yellow);
						cout << "> ";

						SetConsoleTextAttribute(hhConsole, defaultColor);
						cout << "Nie mozesz tutaj postawic statku! Wychodzi poza plansze!";

						SetConsoleTextAttribute(hhConsole, yellow);
						cout << "\n\t < ";

						SetConsoleTextAttribute(hhConsole, red);
						cout << "KOMUNIKAT ";

						SetConsoleTextAttribute(hhConsole, yellow);
						cout << "> ";

						SetConsoleTextAttribute(hhConsole, defaultColor);
						cout << "Nacisnij dowolny klawisz...";

						_getch();

						cin.sync();
						cin.clear();

						system("cls");
						continue;
					}

					if (ship[i].coordY1 == 0)
					{
						for (short j = 0; j < ship[i].lengthOfShip; j++)
							if (!field[ship[i].coordY1 + j][ship[i].coordX1].isClear || !field[ship[i].coordY1 + j][ship[i].coordX1 + 1].isClear || !field[ship[i].coordY1 + j][ship[i].coordX1 - 1].isClear || !field[ship[i].coordY1 + j + 1][ship[i].coordX1].isClear || !field[ship[i].coordY1 + j + 1][ship[i].coordX1 + 1].isClear || !field[ship[i].coordY1 + j + 1][ship[i].coordX1 - 1].isClear)
								goodLocation = false;
					}
					else
					{
						for (short j = 0; j < ship[i].lengthOfShip; j++)
							if (!field[ship[i].coordY1 + j][ship[i].coordX1].isClear || !field[ship[i].coordY1 + j + 1][ship[i].coordX1].isClear || !field[ship[i].coordY1 + j - 1][ship[i].coordX1].isClear || !field[ship[i].coordY1 + j][ship[i].coordX1 + 1].isClear || !field[ship[i].coordY1 + j][ship[i].coordX1 - 1].isClear || !field[ship[i].coordY1 + j + 1][ship[i].coordX1 + 1].isClear || !field[ship[i].coordY1 + j + 1][ship[i].coordX1 - 1].isClear || !field[ship[i].coordY1 + j - 1][ship[i].coordX1 - 1].isClear || !field[ship[i].coordY1 + j - 1][ship[i].coordX1 + 1].isClear)
								goodLocation = false;
					}
					
				
					if (!goodLocation)
					{
						SetConsoleTextAttribute(hhConsole, yellow);
						cout << "\n\n\t < ";

						SetConsoleTextAttribute(hhConsole, red);
						cout << "KOMUNIKAT ";

						SetConsoleTextAttribute(hhConsole, yellow);
						cout << "> ";

						SetConsoleTextAttribute(hhConsole, defaultColor);
						cout << "Nie mozesz tutaj postawic statku! Nachodzi on na inny!";

						SetConsoleTextAttribute(hhConsole, yellow);
						cout << "\n\t < ";

						SetConsoleTextAttribute(hhConsole, red);
						cout << "KOMUNIKAT ";

						SetConsoleTextAttribute(hhConsole, yellow);
						cout << "> ";

						SetConsoleTextAttribute(hhConsole, defaultColor);
						cout << "Nacisnij dowolny klawisz...";

						_getch();

						cin.sync();
						cin.clear();

						system("cls");
						continue;
					}

					for (short j = 0; j < ship[i].lengthOfShip; j++)
					{
						field[ship[i].coordY1 + j][ship[i].coordX1].isClear = false;
						field[ship[i].coordY1 + j][ship[i].coordX1].isShipOn = true;
					}
				}

				updateFields();
				system("cls");
			}

			break;
		}
	}

	getBattlefield();

	SetConsoleTextAttribute(hhConsole, yellow);
	cout << "\n\n\t < ";

	SetConsoleTextAttribute(hhConsole, red);
	cout << "KOMUNIKAT ";

	SetConsoleTextAttribute(hhConsole, yellow);
	cout << "> ";

	SetConsoleTextAttribute(hhConsole, defaultColor);
	cout << "Tak prezentuje sie Twoje pole bitwy!";

	SetConsoleTextAttribute(hhConsole, yellow);
	cout << "\n\t < ";

	SetConsoleTextAttribute(hhConsole, red);
	cout << "KOMUNIKAT ";

	SetConsoleTextAttribute(hhConsole, yellow);
	cout << "> ";

	SetConsoleTextAttribute(hhConsole, defaultColor);
	cout << "Nacisnij dowolny klawisz...";
	_getch();

	system("cls");
}

void Battlefield::updateFields()
{
	for (short i = 0; i < 9; i++)
		for (short j = 0; j < 9; j++)
		{
			if (field[i][j].isClear)
			{
				if (field[i][j].isHit)
				{
					field[i][j].graphicRep = GIsMissed;
					field[i][j].graphicRepColorID = blue;
				}
		
				else
				{
					field[i][j].graphicRep = GIsClear;
					field[i][j].graphicRepColorID = defaultColor;
				}	
			}


			else if (field[i][j].isShipOn)
			{
				if (field[i][j].isHit)
				{
					field[i][j].graphicRep = GIsHit;
					field[i][j].graphicRepColorID = red;
				}
					
				else
				{
					field[i][j].graphicRep = GIsShipOn;
					field[i][j].graphicRepColorID = green;
				}
			}
		}
}

void Battlefield::updateEnemyFields()
{
	for (short i = 0; i < 9; i++)
		for (short j = 0; j < 9; j++)
		{
			if (field[i][j].isClear)
			{
				if (field[i][j].isHit)
				{
					field[i][j].graphicRep = GIsMissed;
					field[i][j].graphicRepColorID = blue;
				}
					
				else
				{
					field[i][j].graphicRep = GIsClear;
					field[i][j].graphicRepColorID = defaultColor;
				}
					
			}


			else if (field[i][j].isShipOn)
			{
				if (field[i][j].isHit)
				{
					field[i][j].graphicRep = GIsHit;
					field[i][j].graphicRepColorID = red;
				}
					
				else
				{
					field[i][j].graphicRep = GIsClear;
					field[i][j].graphicRepColorID = defaultColor;
				}
					
			}
		}
}

void Battlefield::getBattlefield()
{
	SetConsoleTextAttribute(hhConsole, yellow);
	cout << "\n\n\t < ";

	SetConsoleTextAttribute(hhConsole, green);
	cout << "GRACZ";

	SetConsoleTextAttribute(hhConsole, yellow);
	cout << " > ";

	SetConsoleTextAttribute(hhConsole, purple);
	cout << playerName;

	SetConsoleTextAttribute(hhConsole, defaultColor);
	cout << "\n\n\n\t      ";

	SetConsoleTextAttribute(hhConsole, sky);
	for (short i = 0; i < 9; i++)
		cout << (char)(65 + i) << "   ";
	
	cout << "\n\n         ";

	for (short i = 0; i < 9; i++)
	{
		SetConsoleTextAttribute(hhConsole,sky);
		cout << i + 1 << "   ";

		SetConsoleTextAttribute(hhConsole, field[i][0].graphicRepColorID);
		cout << field[i][0].graphicRep;
		SetConsoleTextAttribute(hhConsole, defaultColor);
		cout << char(186);

		for (short j = 1; j < 9; j++)
		{
			if (j > 7)
			{
				SetConsoleTextAttribute(hhConsole, field[i][j].graphicRepColorID);
				cout << field[i][j].graphicRep;
				SetConsoleTextAttribute(hhConsole, defaultColor);
			}
				
			else
			{
				SetConsoleTextAttribute(hhConsole, field[i][j].graphicRepColorID);
				cout << field[i][j].graphicRep;
				SetConsoleTextAttribute(hhConsole, defaultColor);
				cout << char(186);
			}	
		}

		cout << "\n\t     ";
		
		if (i != 8)
		{
			for (short j = 0; j < 9; j++)
			{
				if (j == 8)
					cout << char(205) << char(205) << char(205);
				else
					cout << char(205) << char(205) << char(205) << char(206);
			}
		}
		

		cout << "\n\t ";
	}
}

void Battlefield::endGame()
{
	system("cls");	
	
	soundEffect(2);

	SetConsoleTextAttribute(hhConsole, blue);
	cout << "\n\n\tBrawo! Gracz " << playerName << " wygrywa gre!\n\n";

	SetConsoleTextAttribute(hhConsole, red);
	cout << "\n\t __          ____     __ _____  _____             _   _           ";
	cout << "\n\t \\ \\        / /\\ \\   / // ____||  __ \\     /\\    | \\ | |    /\\    ";
	cout << "\n\t  \\ \\  /\\  / /  \\ \\_/ /| |  __ | |__) |   /  \\   |  \\| |   /  \\   ";
	cout << "\n\t   \\ \\/  \\/ /    \\   / | | |_ ||  _  /   / /\\ \\  | . ` |  / /\\ \\  ";
	cout << "\n\t    \\  /\\  /      | |  | |__| || | \\ \\  / ____ \\ | |\\  | / ____ \\ ";
	cout << "\n\t     \\/  \\/       |_|   \\_____||_|  \\_\\/_/    \\_\\|_| \\_|/_/    \\_\\";

	SetConsoleTextAttribute(hhConsole, green);
	cout << "\n\n\n\tKliknij dowolny przycisk, aby powrocic do menu glownego...";
	_getch();

	system("cls");

	mainMenu();
}