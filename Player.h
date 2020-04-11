#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <ctime>
#include <random>
#include <chrono>
#include <vector>
#include <map>

#include "Entity.h"
#include "Config.h"


using namespace std;

namespace{
	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
}

class Player: public Entity
{

private:
	

	int healthStat;
	int attackStat;
	int movementStat;
	int currency;
	int remainingMoves;
	map<int,int> equippedItems; //Item ID -> count
	
public:
	Player(char ID,int healthStat = 100, int attackStat = 10, int movementStat = 10, int currency = 0);
	
	
	int getHealthStat() const; //returns remaining health
	int getAttackStat() const; //returns damage that player can inflict
	int getMovementStat() const; //returns distance that player can move in 1 turn
	int getCurrency() const; //returns value of player's money
	int getRemainingMoves() const; //returns remaining moves in the turn
	map<int,int>& getEquippedItems();
	
	void addHealthStat(const int _health); 
	void addAttackStat(const int _attack);
	void addMovementStat(const int _movement);
	void addCurrency(const int _currency);
	
	
	void beginTurn();
	
	void move(const int targetY, const int targetX, Entity* gameMap[MAPHEIGHT][MAPWIDTH]);
	void attack(Player& target);

	void endTurn();
	
	void dead();
};

#endif
