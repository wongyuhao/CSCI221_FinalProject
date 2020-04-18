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
#include "UI.h"

using namespace std;

namespace{
	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
}

constexpr int DEFAULT_ATTACK_DAMAGE = 10; //damage of the default attack
constexpr int DEFAULT_ATTACK_RANGE = 1; //range of the default attack
constexpr int DEFAULT_ATTACK_ENERGY_COST = 1; //energy cost of the default attack
constexpr int DEFAULT_ENERGY = 1; //energy cost of the default attack

class Player: public Entity
{
private:
	int healthStat;
	int attackStat;
	int energyStat;
	int currency;
	int remainingMoves;
	int killCount;
	pair<int,int> equippedWeaponItem; //Item ID, current durability
	map<int,int> equippedHealingItems; //Item ID -> count
	pair<int,int> equippedEnergyItem; //Item ID, currnet durability
	
public:
	Player(char ID, int healthStat = 100, int attackStat = 10, int energyStat = 10, int currency = 100);
	
	int getHealthStat() const; //returns remaining health
	int getAttackStat() const; //returns damage that player can inflict
	int getEnergyStat() const; //returns distance that player can move in 1 turn
	int getCurrency() const; //returns value of player's money
	int getRemainingMoves() const; //returns remaining moves in the turn
	int getKillCount() const; //returns kill count of player
	const pair<int,int>& getEquippedWeaponItem() const;
	const map<int,int>& getEquippedHealingItems() const;
	const pair<int,int>& getEquippedEnergyItem() const;
	
	//mutator functions
	void addHealthStat(const int _health); 
	void addAttackStat(const int _attack);
	void setEnergyStat(const int _energy);
	void addCurrency(const int _currency);
	void addRemainingMoves(const int _moves);
	void addKillCount(const int _killCount);
	void addEquippedItem(const int itemID, const string itemType, const int itemStat, const int addCount);
	
	//begin/end turn functions
	void beginTurn();
	void endTurn();
	
	//actions
	void move(const int targetY, const int targetX, char gameMap[MAPHEIGHT][MAPWIDTH]);
	vector<int> defaultAttack(vector<Player>& playerList);
};

#endif
