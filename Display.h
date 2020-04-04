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
	static vector < Building> local_BL;
	static vector <  Player> local_PL;
private:
	void initMap();
public:
	Display(vector< Building> buildingList,vector<Player> playerList)
	{
		local_BL = buildingList;
		local_PL = playerList;
		initMap();
		printMap();
	}
	void printMap()const;
	void playerMenu();
	void bumpConsole() {
		for (int i = 0; i < MAPSIZE; i++) {
			cout << endl;
		}
	}
};

#endif

