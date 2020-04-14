#include <algorithm>
#include "Item.h"

//function to check for out of bounds
bool outOfBounds(int X, int Y) {
	return (X <= 0 || X >= MAPHEIGHT-1 || Y <= 0 || Y >=MAPWIDTH-1);
}

//buy function
void Item::buyItem(Player& player) const {
	if(player.getCurrency() < cost){
		cout << "Not enough currency." << endl;
		return;
	}
	
	player.addCurrency(-cost);
	player.addEquippedItem(getID(), getType(), 1);
	cout << "Successfully bought a(n) " << name << endl;
}

//use functions
vector<int> PlayerWeaponItem::use(Player* const user, vector<Player>& playerList) const {
	cout << "Enter target player: ";
	char targetID;
	cin >> targetID;
	int targetIndex = toupper(targetID) - 'A';
	
	while (true) {
		//check range
		if(targetIndex < 0 || targetIndex >= playerList.size()) {
			cout << "Invalid player. Try again." << endl;
			cin >> targetIndex;
			continue;
		}
		
		//check that target is alive
		if(playerList[targetIndex].getHealthStat() <= 0) {
			cout << "Target player is dead. Try again." << endl;
			cin >> targetIndex;
			continue;
		}
		
		//All checks passed
		break;
	}
	
	vector<int> deadPlayers;
	
	Player& target = playerList[targetIndex];
	
	const int oldHP = target.getHealthStat();
	
	target.addHealthStat(-min(oldHP, stat));
	cout << stat << "damage dealt to Player " << targetID << " (" << oldHP << " -> " << target.getHealthStat() << ")" << endl;
	if(target.getHealthStat() <= 0) {
		cout << "Player " << user->getID() << " killed Player " << targetID << "!" << endl;
		deadPlayers.push_back(targetID - 'A');
	}
	
	return deadPlayers;
}

vector<int> CubeWeaponItem::use(Player* const user, vector<Player>& playerList) const {
	cout << "Enter target location: ";
	int tgtX, tgtY;
	cin >> tgtY >> tgtX;
	
	while(outOfBounds(tgtX, tgtY)) {
		cout << "Invalid coordinates. Try again." << endl;
		cin >> tgtY >> tgtX;
	}
	
	vector<int> deadPlayers;
	
	for (Player& target: playerList) {
		if(target.getHealthStat() <= 0) continue;
		if(abs(tgtX - target.getPosX()) + abs(tgtY - target.getPosY()) >= range) continue;
		
		const char targetID = target.getID();
		const int oldHP = target.getHealthStat();
		
		target.addHealthStat(-min(oldHP, stat));
		cout << stat << "damage dealt to Player " << targetID << " (" << oldHP << " -> " << target.getHealthStat() << ")" << endl;
		if(target.getHealthStat() <= 0) {
			cout << "Player " << targetID << " has been slained by Player " << user->getID() << "!" << endl;
			deadPlayers.push_back(targetID - 'A');
		}
	}
	
	return deadPlayers;
}

vector<int> HealingItem::use(Player* const user, vector<Player>& playerList) const {
	const int oldHP = user->getHealthStat();
	user->addHealthStat(stat);
	cout << "HP increased by " << stat << " (" << oldHP << " -> " << user->getHealthStat() << endl;
	return vector<int>();
}

vector<int> EnergyItem::use(Player* const user, vector<Player>& playerList) const {
	const int oldEnergy = user->getEnergyStat();
	user->addEnergyStat(stat);
	cout << "Max energy increased by " << stat << " (" << oldEnergy << " -> " << user->getEnergyStat() << endl;
	return vector<int>();
}
