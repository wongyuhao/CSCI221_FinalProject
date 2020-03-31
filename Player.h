#pragma once
#include <iostream>
#include <ctime>
#include <random>
using namespace std;



class Player
{
private:
	struct pos {
		int x;
		int y;
		pos(int a, int b){
			this->x = a;
			this->y = b;
		}
	};
	static int playerCount;

	

	char playerID;

	int healthStat;
	int attackStat;

public:
	Player(int healthStat= 100 , int attackStat = 10 );

	static int getPlayerCount();

	int doDamage(int);
	void takeDamage(int);

	

	char getPlayerID() {
		return playerID;
	}
};

