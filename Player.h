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
	
	vector <Player> pListPtr;
	int healthStat;
	int attackStat;
	int movementStat;
	int currency;
	int remainingMoves;
	map<int,int> equippedItems; //Item ID -> count
	
public:
	Player(
		vector <Player>& playerList,
		int posX,
		int posY,
		char ID,
		int healthStat = 100,
		int attackStat = 10,
		int movementStat = 10,
		int currency = 0
	);
	
	
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
	
	void move(const int targetY, const int targetX, Entity* gameMap[MAPHEIGHT][MAPWIDTH]);
	void attack(Player& target);
	void endTurn(int &currentTurn, int &roundCounter);
	void dead();
};

#endif
