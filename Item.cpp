#include "Item.h"

string Item::getName() const {
	return name;
}

int Item::getCost() const {
	return cost;
}

int Item::getStat() const {
	return stat;
}

void Item::buyItem(Player& player) const {
	if(player.getCurrency() < cost){
		cout << "Not enough currency." << endl;
		return;
	}
	
	player.addCurrency(-cost);
	player.getEquippedItems()[getID()]++;
	cout << "Successfully bought a(n) " << name << endl;
}

int WeaponItem::getRange() const {
	return range;
}

void WeaponItem::use(Player& target) {
	target.addHealthStat(-stat);
}

void CubeWeaponItem::use(const Entity& location, vector<Player>& playerList) {
	for(Player player: playerList) {
		if(	location.getPosX() - radius < player.getPosX() && player.getPosX() < location.getPosX() + radius && 
			location.getPosY() - radius < player.getPosY() && player.getPosY() < location.getPosY() + radius)
		{
			player.addHealthStat(-stat);
		}
	}
}

void HealingItem::use(Player& target) {
	target.addHealthStat(stat);
}

void MovementItem::use(Player& target) {
	target.addMovementStat(stat);
}
