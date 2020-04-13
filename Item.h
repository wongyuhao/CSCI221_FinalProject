#ifndef ITEM_H
#define ITEM_H

#include "Type.h"
#include "Player.h"
#include "Config.h"
#include <string>

using namespace std;

class Item: public Type {
protected:
	string name; //name of the object
	int cost; //monetary cost of the object
	int stat; // damage/heal/extra movement, depending on the type of item
	
public:
	Item(): Type(), name(""), cost(0), stat(0) {} //default constructor for testing
	Item(int id, string name, int cost, int stat) //constructor 
	: Type(id), name(name), cost(cost), stat(stat) {}
	
	//accessor functions
	string getName() const;
	int getCost() const;
	int getStat() const;
	void buyItem(Player& player) const;
	virtual vector<int> use(Player* const user, vector<Player>& playerList) const = 0; //return value: dead players indices caused by item use
};


class WeaponItem: public Item {
protected:
	int range;
	
public:
	WeaponItem(): range(0) {}
	WeaponItem(int id, string name, int cost, int stat, int range): Item(id, name, cost, stat), range(range) {}
	
	int getRange() const;
};

class PlayerWeaponItem: public WeaponItem {
public:
	PlayerWeaponItem(){}
	PlayerWeaponItem(int id, string name, int cost, int stat, int range): WeaponItem(id, name, cost, stat, range) {}
	
	vector<int> use(Player* const user, vector<Player>& playerList) const override;
};

class CubeWeaponItem: public WeaponItem {
private:
	int radius;
	
public:
	CubeWeaponItem(): radius(0) {}
	CubeWeaponItem(int id, string name, int cost, int stat, int range, int radius): WeaponItem(id, name, cost, stat, range), radius(radius) {}
	
	int getRadius() const;
	
	vector<int> use(Player* const, vector<Player>& playerList) const override;
};


class HealingItem: public Item {
public:
	HealingItem(){}
	HealingItem(int id, string name, int cost, int stat): Item(id, name, cost, stat) {}
	
	vector<int> use(Player* const user, vector<Player>& playerList) const override;
};


class MovementItem: public Item {
public:
	MovementItem(){}
	MovementItem(int id, string name, int cost, int stat): Item(id, name, cost, stat) {}
	
	vector<int> use(Player* const user, vector<Player>& playerList) const override;
};

#endif
