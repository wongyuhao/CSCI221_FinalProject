#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <ctime>
#include <random>
#include <vector>
#include <map>

#include "Entity.h"
#include "Config.h"

using namespace std;

class Player: public Entity
{

private:
	static int uniquePlayers;

	int healthStat;
	int attackStat;
	int movementStat;
	int currency;
	int remainingMoves;
	map<int,int> equippedItems; //Item ID -> count
	
public:
	Player(int healthStat = 100, int attackStat = 10, int movementStat = 10, int currency = 0);
	static int getPlayerCount();
	
	int getHealthStat() const;
	int getAttackStat() const;
	int getMovementStat() const;
	int getCurrency() const;
	int getRemainingMoves() const;
	map<int,int>& getEquippedItems();
	
	void addHealthStat(const int _health);
	void addAttackStat(const int _attack);
	void addMovementStat(const int _movement);
	void addCurrency(const int _currency);
	
	
	void beginTurn();
	
	void move(const int targetX, const int targetY, Entity* gameMap[MAPSIZE][MAPSIZE*2]);
	void attack(Player& target);

	void endTurn(int &currentTurn, int &roundCounter);
	
	void dead();
};

#endif
