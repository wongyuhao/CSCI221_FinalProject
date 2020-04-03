#include <iostream>
#include<random>
#include<ctime>


#include "Building.h"
#include "Player.h"
#include "DisplayDriver.h"

using namespace std;

int main() {
	srand(time(NULL));


	int input;
	cout << "Enter number of players:";
	cin >> input;

	
	vector <Player> playerList;
	vector<Building> buildingList;
	
	buildingList.push_back(Building(SHOP1));
	buildingList.push_back(Building(SHOP2));
	buildingList.push_back(Building(SHOP3));
	buildingList.push_back(Building(SHOP4));


	for (int i = 0; i < input && i<10; i++) {
		playerList.push_back(Player());
	}

	

	DisplayDriver map(buildingList , playerList);





}