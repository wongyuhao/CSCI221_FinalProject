#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <ctime>
#include <random>

#include "Resource.h"

#include "Item.h"

using namespace std;

class Player: public Entity
{

private:
	static int uniquePlayers;

	int healthStat;
	int attackStat;
	int movementStat;
	int remainingMoves;
	Item equippedItem;
	
public:
	Player(int healthStat = 100 , int attackStat = 10, int movementStat = 10);
	static int getPlayerCount();
	
	void beginTurn();
	void move(const int targetX, const int targetY);
	//virtual void useItem(const Item& item);
	//void buyItem(const Item& item);

	void attack();
	
	
	void endTurn();
	
	void dead();


};

#endif
