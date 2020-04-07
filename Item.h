#ifndef ITEM_H
#define ITEM_H

#include "Type.h"
#include "Player.h"
#include <string>

using namespace std;

class Item: public Type {
protected:
	string name;
	int cost;
	int stat; // damage/heal/extra movement, depending on the type of item
	
public:
	Item(): Type(), name(""), cost(0), stat(0) {}
	Item(int id, string name, int cost, int stat)
	: Type(id), name(name), cost(cost), stat(stat) {}
	
	string getName() const;
	int getCost() const;
	int getStat() const;
	void buyItem(Player& player) const;
	virtual void use(Player& target) = 0;
};


class WeaponItem: public Item {
protected:
	int range;
	
public:
	WeaponItem(): range(0) {}
	WeaponItem(int id, string name, int cost, int stat, int range): Item(id, name, cost, stat), range(range) {}
	
	int getRange() const;
	void use(Player& target);
};

class PlayerWeaponItem: public WeaponItem {
public:
	PlayerWeaponItem(){}
	PlayerWeaponItem(int id, string name, int cost, int stat, int range): WeaponItem(id, name, cost, stat, range) {}
};

class CubeWeaponItem: public WeaponItem {
private:
	int radius;
	
public:
	CubeWeaponItem(): radius(0) {}
	CubeWeaponItem(int id, string name, int cost, int stat, int range, int radius): WeaponItem(id, name, cost, stat, range), radius(radius) {}
	
	void use(const Entity& location, vector<Player>& playerList);
};


class HealingItem: public Item {
public:
	HealingItem(){}
	HealingItem(int id, string name, int cost, int stat): Item(id, name, cost, stat) {}
	void use(Player& target);
};


class MovementItem: public Item {
public:
	MovementItem(){}
	MovementItem(int id, string name, int cost, int stat): Item(id, name, cost, stat) {}
	void use(Player& target);
};

#endif
