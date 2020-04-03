#ifndef DISPLAYDRIVER_H
#define DISPLAYDRIVER_H

#include <iostream>
#include <vector>
#include "Player.h"
#include "Building.h"
#include "Resource.h"

using namespace std;

class DisplayDriver
{
	static vector <class Building> local_BL;
	static vector <class Player> local_PL;
private:
	static char map[MAPSIZE][MAPSIZE*2] ;
	void initMap();
public:
	DisplayDriver(vector<class Building> buildingList,vector<class Player> playerList)
	{
		local_BL = buildingList;
		local_PL = playerList;
		initMap();
		printMap();
	}
	void printMap()const;
	void playerMenu();

};

#endif

