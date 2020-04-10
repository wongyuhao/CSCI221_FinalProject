#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <vector>

#include "Player.h"
#include "Building.h"
#include "Resource.h"

using namespace std;

class Display
{
private:
	int currentTurn = 0;
	int roundCounter = 1;
	int playerCount = 0;
	
	Entity* gameMap[MAPSIZE][MAPSIZE * 2];
	
	void initMap();
	
public:
	Display()
	{
		
		playerCount = playerList.size();
		initMap();
		printMap();
	}
	void printMap() const;
	void playerMenu();
	inline void bumpConsole() {
		for (int i = 0; i < MAPSIZE; i++) {
			cout << endl;
		}
	}
	
	inline void incrementCurrentTurn(){
		currentTurn++; currentTurn %= playerCount;
	}
	
	bool promptYN(string) const;
};

#endif
