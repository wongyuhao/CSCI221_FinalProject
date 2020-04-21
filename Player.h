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

class Player: public Entity
{
private:
	int healthStat; //current HP
	int attackStat; //current damage the player can inflict
	int energyStat; //max energy of the player; player's energy is reset to this at the beginning of his turn
	int currency; //player's money
	int remainingMoves; //current remaining energy
	int killCount; //player's kill count
	pair<int,int> equippedWeaponItem; //Item ID, current durability
	map<int,int> equippedHealingItems; //Item ID -> count
	pair<int,int> equippedEnergyItem; //Item ID, currnet durability
	
public:
	Player(char ID, int healthStat = DEFAULT_HP, int attackStat = DEFAULT_ATTACK_DAMAGE, int energyStat = DEFAULT_ENERGY, int currency = DEFAULT_CURRENCY);
	
	int getHealthStat() const; //returns remaining health
	int getAttackStat() const; //returns damage that player can inflict
	int getEnergyStat() const; //returns the player's max energy
	int getCurrency() const; //returns value of player's money
	int getRemainingMoves() const; //returns remaining energy
	int getKillCount() const; //returns kill count of player
	//returns player's weapons/healing items/energy items, respectively. (key, value)/(first, second) = (item ID, durability/count left)
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
	
	//begin/end turn functions, called during beginning/end of turn
	inline void beginTurn() {
		remainingMoves = energyStat;
	}
	inline void endTurn() {
		remainingMoves = 0;
		currency += PASSIVE_INCOME;
	}
	
	//move function
	void move(const int targetY, const int targetX, char gameMap[MAPHEIGHT][MAPWIDTH]);
	//default attack; called when attacking without a weapon
	vector<int> defaultAttack(vector<Player>& playerList);
};

#endif
