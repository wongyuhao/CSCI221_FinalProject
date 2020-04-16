#include <iostream>
#include <fstream>
#include <cassert>
#include <random>
#include <ctime>

#include "Building.h"
#include "Player.h"
#include "Display.h"

using namespace std;

int main() {
	cout << "Maximize the window for the full experience." << endl << endl;
	
	cout << "Enter number of players: ";
	int playerCount;
	cin >> playerCount;
	
	//initialize Player objects
	for (int i = 0; i < playerCount && i < 10; i++) {
		char playerID = i+65;
		playerList.push_back(Player(playerID));
	}
	
	//DEBUGGING CODE: delete this before final release
	/*playerList[0].setPosX(15); playerList[0].setPosY(15);
	playerList[1].setPosX(15); playerList[1].setPosY(16);*/
	
	//create file stream to read item file
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
			cout << "Error when reading Items.txt: Invalid item type." << endl;
			return 0;
		}
		
		currentID++;
		fin.ignore(2);
	}
	
	fin.close();
	
	Display display;
	
	//first turn
	playerList[currentTurn].beginTurn();
	
	while (aliveCount > 1) {
		display.playerMenu();
	}
	
	while(playerList[currentTurn].getHealthStat() <= 0) {
		currentTurn = (currentTurn + 1) % playerList.size();
	}
	
	cout << endl << string(10, '=') << " GAME END " << string(10, '=') << endl;
	cout << "Player " << playerList[currentTurn].getID() << " wins!" << endl;
}
