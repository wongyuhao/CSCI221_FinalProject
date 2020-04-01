#ifndef DISPLAYDRIVER_H
#define DISPLAYDRIVER_H

#include <iostream>
#include <vector>
#include "Player.h"

using namespace std;

#define MAPSIZE 30

class DisplayDriver
{

private:
	static char map[MAPSIZE][MAPSIZE*2] ;
	void initMap(vector<class Player>);
public:
	DisplayDriver(vector<class Player> playerList) {
		initMap(playerList);
		printMap();
	}
	void printMap()const;

};

#endif

