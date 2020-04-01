#include <iostream>
#include "DisplayDriver.h"
#include "Player.h"
using namespace std;

int main() {
	srand(time(NULL));
	int input;
	cout << "Enter number of players:";
	cin >> input;
	vector <Player> playerList;

	for (int i = 0; i < input && i<10; i++) {
		playerList.push_back(Player());
	}

	DisplayDriver map(playerList);





}