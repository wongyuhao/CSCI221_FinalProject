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
		char code = 'a';
		playerList.push_back(
			Player(
				playerList, 
				code++, 
				((rand() % (MAPSIZE * 2 - 2)) + 1),
				((rand() % (MAPSIZE - 2)) + 1)
			)
		);
	}
	
	
	
	

	while (playerList.size() > 1) {
		display.printMap();
		display.playerMenu();
		
	}
	

	

	
}
