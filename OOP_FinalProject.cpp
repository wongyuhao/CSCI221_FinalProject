#include <iostream>
#include <random>
#include <ctime>

#include "Building.h"
#include "Player.h"
#include "Display.h"

using namespace std;

int main() {
	srand(time(NULL));
	
	cout << "Enter number of players: ";
	int playerCount;
	cin >> playerCount;
	Display display;
	for (int i = 0; i < playerCount && i < 10; i++) {
		playerList.push_back(Player());
	}
	
	display.printMap();
	
	buildingList.push_back(Building(SHOP1));
	buildingList.push_back(Building(SHOP2));
	buildingList.push_back(Building(SHOP3));
	buildingList.push_back(Building(SHOP4));

	while (playerList.size() > 1) {
		display.playerMenu();
	}
	

	

	
}
