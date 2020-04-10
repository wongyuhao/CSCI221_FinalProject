#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <vector>

#include "Player.h"
#include "Building.h"
#include "Resource.h"

using namespace std;
extern vector <Player> playerList;
class Display
{
private:
	
	
	
	
	
	void initMap();
	
public:
	Entity* gameMap[MAPSIZE][MAPSIZE * 2];
	Display()
	{
		
		
		initMap();
		
	}
	void printMap() const;
	void playerMenu();
	inline void bumpConsole() {
		for (int i = 0; i < MAPSIZE; i++) {
			cout << endl;
		}
	}
	
	inline void incrementCurrentTurn(){
		currentTurn++; currentTurn %= playerList.size();
	}
	
	bool promptYN(string) const;
};

#endif
