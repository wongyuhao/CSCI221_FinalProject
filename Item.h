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
	string type; //type of the object (weapon/healing/energy)
	int cost; //monetary cost of the object
	int energyCost; //energy cost of the object
	int stat; // damage/heal/max energy, depending on the type of item
	
public:
	Item(): Type(), name(""), type(), cost(0), energyCost(0), stat(0) {} //default constructor for testing
	Item(int id, string name, string type, int cost, int energyCost, int stat) //constructor 
	: Type(id), name(name), type(type), cost(cost), energyCost(energyCost), stat(stat) {}
	
	//accessor functions
	inline string getName() const {
		return name;
	}
	inline string getType() const {
		return type;
	}
	inline int getCost() const {
		return cost;
	}
	inline int getEnergyCost() const {
		return energyCost;
	}
	inline int getStat() const {
		return stat;
	}
	
	void buyItem(Player& player) const;
	virtual vector<int> use(Player* const user, vector<Player>& playerList) const = 0; //return value: dead players indices caused by item use
};


class WeaponItem: public Item {
protected:
	int range;
	
public:
	WeaponItem(): range(0) {}
	WeaponItem(int id, string name, int cost, int energyCost, int stat, int range): Item(id, name, string("Weapon"), cost, energyCost, stat), range(range) {}
	
	int getRange() const;
};

class PlayerWeaponItem: public WeaponItem {
public:
	PlayerWeaponItem(){}
	PlayerWeaponItem(int id, string name, int cost, int energyCost, int stat, int range): WeaponItem(id, name, cost, energyCost, stat, range) {}
	
	vector<int> use(Player* const user, vector<Player>& playerList) const override;
};

class CubeWeaponItem: public WeaponItem {
private:
	int radius;
	
public:
	CubeWeaponItem(): radius(0) {}
	CubeWeaponItem(int id, string name, int cost, int energyCost, int stat, int range, int radius): WeaponItem(id, name, cost, energyCost, stat, range), radius(radius) {}
	
	int getRadius() const;
	
	vector<int> use(Player* const, vector<Player>& playerList) const override;
};


class HealingItem: public Item {
public:
	HealingItem(){}
	HealingItem(int id, string name, int cost, int energyCost, int stat): Item(id, name, "Healing", cost, energyCost, stat) {}
	
	vector<int> use(Player* const user, vector<Player>& playerList) const override;
};


class EnergyItem: public Item {
public:
	EnergyItem(){}
	EnergyItem(int id, string name, int cost, int energyCost, int stat): Item(id, name, "Energy", cost, energyCost, stat) {}
	
	vector<int> use(Player* const user, vector<Player>& playerList) const override;
};

#endif
