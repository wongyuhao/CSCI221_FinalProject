#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <ctime>
#include <random>
#include "DisplayDriver.h"

using namespace std;



class Player
{

private:
	static int playerCount;
	char playerID;

	int healthStat;
	int attackStat;



	
	
public:
	Player(int healthStat= 100 , int attackStat = 10 );

	static int getPlayerCount();

	int doDamage(int);
	void takeDamage(int);

	int posX;
	int posY;

	
	void setPlayerID(char id) {
		playerID = id;
	}
	char getPlayerID() {
		return playerID;
	}
};

#endif