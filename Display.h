#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <vector>

#include "Player.h"
#include "Building.h"
#include "Resource.h"
#include "Config.h"

using namespace std;
extern vector <Player> playerList;
class Display
{
private:
	
	
	

	Entity* gameMap[MAPHEIGHT][MAPWIDTH];

	
	void initMap();
	
public:
	
	Display()
	{
		
		
		initMap();
		
	}
	void printMap() const;
	void playerMenu();
	inline void bumpConsole() {
		for (int i = 0; i < MAPHEIGHT; i++) {
			cout << endl;
		}
	}
	
	inline void incrementCurrentTurn(){
		currentTurn++; currentTurn %= playerList.size();
	}
	
	bool promptYN(string) const;
};

#endif
