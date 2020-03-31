#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <ctime>
#include <random>
#include "DisplayDriver.h"

using namespace std;

struct pos {
	int x;
	int y;
	char ID;
	pos() {
		x = -1;
		y = -1;
		ID = -1;
	}
};

class Player
{

private:
	static int playerCount;
	char playerID;

	int healthStat;
	int attackStat;

	
	friend vector<struct pos> DisplayDriver::copyCoord(Player& obj);
public:
	Player(int healthStat= 100 , int attackStat = 10 );

	static vector <struct pos> coordinates;
	struct pos myPos;
	static int getPlayerCount();

	int doDamage(int);
	void takeDamage(int);

	
	void setPlayerID(char id) {
		playerID = id;
	}
	char getPlayerID() {
		return playerID;
	}
};

#endif