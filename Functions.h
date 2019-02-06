#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Structures.h"

#include <string>
#include <Windows.h>


constexpr int blue = 9;
constexpr int yellow = 14;
constexpr int defaultColor = 15;
constexpr int purple = 13;
constexpr int green = 10;
constexpr int sky = 11;
constexpr int red = 12;

void mainMenu();
void mainMusicStart();
void mainMusicStop();
void soundEffect(short);
void windowSize(int, int);
void hidePointer();
void removeScrollbar();
void getGUIOfMenu();
void setChoiceInMainMenu(char&);
void startGame();
void startBattle(Battlefield, Battlefield);
bool isShipNearby(Battlefield, short, short);
void playerTurn(Battlefield&, Battlefield&);
void setCoords(short&, short&);
bool areCoordsCorrect(std::string);

#endif
