#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <ctime>
#include <random>
#include "DisplayDriver.h"
#include "Entity.h"

using namespace std;



class Player: public Entity
{

private:
	static int playerCount;
	

	int healthStat;
	int attackStat;	
	
public:
	Player(int healthStat= 100 , int attackStat = 10 );
	static int getPlayerCount() ;
	

	


};

#endif