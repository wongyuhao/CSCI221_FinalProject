#include <iostream>
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
	
	//initialize items
	for (int i = 0; i < itemList.size(); i++) {
		itemList[i].setID(i);
	}
	
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
