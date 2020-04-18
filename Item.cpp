#include <algorithm>
#include "Item.h"

//function to check for out of bounds
bool outOfBounds(int X, int Y) {
	return (X <= 0 || X >= MAPHEIGHT-1 || Y <= 0 || Y >=MAPWIDTH-1);
}

//buy function
void Item::buyItem(Player* const player) const {
	//check that user has enough currency
	if(player->getCurrency() < getCost()) {
		cout << "Insufficient currency." << endl;
		system("pause"); return;
	}
	
	//if the selected item will overwrite the user's weapon/energy item, warn the user
	if((getType()[0] == 'W' && player->getEquippedWeaponItem().first != -1) ||
	   (getType()[0] == 'E' && player->getEquippedEnergyItem().first != -1)
	)
	{
		string itemType = getType();
		itemType[0] = tolower(itemType[0]);
		if(!UI::promptYN("This will replace your current " + itemType + " item. Proceed?")) return;
	}
	
	player->addCurrency(-cost);
	player->addEquippedItem(getID(), getType(), getStat(), getDurability());
	cout << endl << "Successfully purchased the item \"" << getName() << "\"." << endl;
}

//use functions
vector<int> PlayerWeaponItem::use(Player* const user, vector<Player>& playerList) const {
	cout << "Enter target player: ";
	char targetID = UI::readChar();
	int targetIndex = toupper(targetID) - 'A';
	
	while (true) {
		//check range
		if(targetIndex < 0 || targetIndex >= playerList.size()) {
			cout << "Invalid player. Try again." << endl;
			targetID = UI::readChar();
			targetIndex = toupper(targetID) - 'A';
			continue;
		}
		
		//check that target is alive
		if(playerList[targetIndex].getHealthStat() <= 0) {
			cout << "Target player is dead. Try again." << endl;
			targetID = UI::readChar();
			targetIndex = toupper(targetID) - 'A';
			continue;
		}
		
		//All checks passed
		break;
	}
	
	vector<int> deadPlayers;
	Player& target = playerList[targetIndex];
	
	//warn the player if they are attacking themselves
	if(target.getID() == user->getID()) {
		if(!UI::promptYN("Are you sure that you want to target yourself?")) {
			cout << "Why not?" << endl;
			return vector<int>();
		}
		else {
			cout << "You use the weapon on yourself. Ouch." << endl;
		}
	}
	
	const int oldHP = target.getHealthStat();
	target.addHealthStat(-min(oldHP, stat));
	cout << stat << " damage dealt to Player " << targetID << " (" << oldHP << " -> " << target.getHealthStat() << ")" << endl;
	if(target.getHealthStat() <= 0) {
		cout << "Player " << targetID << " has been slained by Player " << user->getID() << "!" << endl;
		deadPlayers.push_back(targetID - 'A');
	}
	
	return deadPlayers;
}

vector<int> CubeWeaponItem::use(Player* const user, vector<Player>& playerList) const {
	cout << "Enter target x-coordinate: ";
	int tgtY = UI::readInt(1, MAPWIDTH-2);
	cout << "Enter target y-coordinate: ";
	int tgtX = UI::readInt(1, MAPHEIGHT-2);
	
	vector<int> deadPlayers;
	int hitCount = 0;
	
	for (Player& target: playerList) {
		if(target.getHealthStat() <= 0) continue;
		if(target.getID() == user->getID()) continue;
		if(max(abs(tgtX - target.getPosX()), abs(tgtY - target.getPosY())) >= radius) continue;
		
		hitCount++;
		const char targetID = target.getID();
		const int oldHP = target.getHealthStat();
		
		target.addHealthStat(-min(oldHP, stat));
		cout << stat << " damage dealt to Player " << targetID << " (" << oldHP << " -> " << target.getHealthStat() << ")" << endl;
		if(target.getHealthStat() <= 0) {
			cout << "Player " << targetID << " has been slained by Player " << user->getID() << "!" << endl;
			deadPlayers.push_back(targetID - 'A');
		}
	}
	
	if(hitCount == 0) {
		cout << "You hit nobody, not even yourself (since you are immune to it)." << endl;
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
	user->setEnergyStat(DEFAULT_ENERGY + stat);
	cout << "Max energy increased by " << stat << " (" << oldEnergy << " -> " << user->getEnergyStat() << endl;
	return vector<int>();
}
