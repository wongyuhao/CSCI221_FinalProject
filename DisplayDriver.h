#ifndef DISPLAYDRIVER_H
#define DISPLAYDRIVER_H

#include <iostream>
#include <vector>
#include "Player.h"
#include "Building.h"

using namespace std;

#define MAPSIZE 30

class DisplayDriver
{

private:
	static char map[MAPSIZE][MAPSIZE*2] ;
	void initMap(vector<class Building>,vector<class Player>);
public:
	DisplayDriver(vector<class Building> buildingList,vector<class Player> playerList) {
		initMap(buildingList,playerList);
		printMap();
	}
	void printMap()const;

};

#endif

