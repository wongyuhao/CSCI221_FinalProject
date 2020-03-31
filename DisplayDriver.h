#ifndef DISPLAYDRIVER_H
#define DISPLAYDRIVER_H

#include <iostream>
#include <vector>
#include "Player.h"

using namespace std;

#define ROWSIZE 30
#define COLSIZE 60

struct pos;

class DisplayDriver
{

private:
	static vector <struct pos> coordinates;
public:
	DisplayDriver() {
		cout << "Initializing map..." << endl;
		Player x;
		coordinates = copyCoord(x);
	}
	void printMap();

	vector<struct pos> copyCoord(Player& obj);
	
};

#endif

