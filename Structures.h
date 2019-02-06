#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <string>

struct Ship
{
	short coordX1;
	short coordY1;
	short lengthOfShip;
};

struct Field
{
	std::string graphicRep;
	int graphicRepColorID;
	bool isClear;
	bool isHit;
	bool isShipOn;
};

struct Battlefield
{
	std::string playerName;
	short playerNumber;
	Field field[10][10];
	Ship ship[5];
	short healthPoints = 15;

	void setPlayerName();
	void setDefaultFields();
	void setShips();
	void updateFields();
	void updateEnemyFields();
	void getBattlefield();
	void endGame();
};

#endif
