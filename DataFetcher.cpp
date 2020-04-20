#include "DataFetcher.h"

void DataFetcher::fetchPlayers(const int playerCount) {
	for (int i = 0; i < playerCount && i < 10; i++) {
		char playerID = i+65;
		playerList.push_back(Player(playerID));
	}
}

void DataFetcher::fetchItems() {
	ifstream fin("Items.txt");
	assert(fin);

	int currentID = 0;
	string name, type;
	int cost, energyCost, stat, durability, range, radius;

	while(getline(fin, name)) {
		fin >> type;
		if(type == "weaponP") {
			fin >> cost >> energyCost >> stat >> durability >> range;
			itemList.push_back(new PlayerWeaponItem(currentID, name, cost, energyCost, stat, durability, range));
		}
		else if(type == "weaponS") {
			fin >> cost >> energyCost >> stat >> durability >> range >> radius;
			itemList.push_back(new CubeWeaponItem(currentID, name, cost, energyCost, stat, durability, range, radius));
		}
		else if(type == "healing") {
			fin >> cost >> stat;
			itemList.push_back(new HealingItem(currentID, name, cost, stat));
		}
		else if(type == "energy") {
			fin >> cost >> stat >> durability;
			itemList.push_back(new EnergyItem(currentID, name, cost, stat, durability));
		}
		else {
			cout << "Error when reading Items.txt: Invalid item type. Type received: " << type << endl;
			assert(0);
		}
		
		currentID++;
		fin.ignore(2);
	}

	fin.close();
}
