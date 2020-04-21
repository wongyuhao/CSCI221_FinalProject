#ifndef ITEM_H
#define ITEM_H

#include "Type.h"
#include "Player.h"
#include "Config.h"
#include <string>

using namespace std;

// Usage: The effect when the use() function of an item is called

class Item: public Type {
protected:
	string name; //name of the object
	string type; //type of the object (Weapon (Player)/Weapon (Splash)/Healing/Energy)
	int cost; //monetary cost of the object
	int energyCost; //energy cost of the object
	int stat; //damage/heal/max energy, depending on the type of item
	int durability; //number of uses before the item expires
	
public:
	Item(): Type(), name(""), type(), cost(0), energyCost(0), stat(0), durability(0) {} //default constructor
	Item(int id, string name, string type, int cost, int energyCost, int stat, int durability)
	: Type(id), name(name), type(type), cost(cost), energyCost(energyCost), stat(stat), durability(durability) {}
	
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
	inline int getDurability() const {
		return durability;
	}
	inline virtual int getRange() const {
		return 0;
	}
	inline virtual int getRadius() const {
		return 0;
	}
	
	//adds the item to player
	void buyItem(Player* const player) const;
	//return value: dead players indices caused by item use
	virtual vector<int> use(Player* const user, vector<Player>& playerList) const = 0;
};


class WeaponItem: public Item {
protected:
	int range; //max Manhattan distance between the user and the selected target player/location
	
public:
	WeaponItem(): range(0) {}
	WeaponItem(int id, string name, string type, int cost, int energyCost, int stat, int durability, int range)
	: Item(id, name, type, cost, energyCost, stat, durability), range(range) {}
	
	inline int getRange() const override {
		return range;
	}
};

//Usage: Damages a single player by stat
class PlayerWeaponItem: public WeaponItem {
public:
	PlayerWeaponItem(){}
	PlayerWeaponItem(int id, string name, int cost, int energyCost, int stat, int durability, int range)
	: WeaponItem(id, name, string("Weapon (Player)"), cost, energyCost, stat, durability, range) {}
	
	vector<int> use(Player* const user, vector<Player>& playerList) const override;
};

//Usage: Damages all players within the area of effect
class CubeWeaponItem: public WeaponItem {
private:
	int radius; //area of effect: A square centered at selected coordinates with side length (2*radius-1)
	
public:
	CubeWeaponItem(): radius(0) {}
	CubeWeaponItem(int id, string name, int cost, int energyCost, int stat, int durability, int range, int radius)
	: WeaponItem(id, name, string("Weapon (Splash)"), cost, energyCost, stat, durability, range), radius(radius) {}
	
	inline int getRadius() const override {
		return radius;
	}
	
	vector<int> use(Player* const, vector<Player>& playerList) const override;
};

//Note: Healing and energy items have no energy cost

//Usage: Increases current HP by stat (max HP capped at DEFAULT_HP)
class HealingItem: public Item {
public:
	HealingItem(){}
	HealingItem(int id, string name, int cost, int stat)
	: Item(id, name, "Healing", cost, 0, stat, 1) {}
	
	vector<int> use(Player* const user, vector<Player>& playerList) const override;
};

//Usage: Increases current max energy by stat; can be stacked
class EnergyItem: public Item {
public:
	EnergyItem(){}
	EnergyItem(int id, string name, int cost, int stat, int durability)
	: Item(id, name, "Energy", cost, 0, stat, durability) {}
	
	vector<int> use(Player* const user, vector<Player>& playerList) const override;
};

#endif
