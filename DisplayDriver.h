#ifndef DISPLAYDRIVER_H
#define DISPLAYDRIVER_H

#include <iostream>
#include <vector>

using namespace std;

#define ROWSIZE 30
#define COLSIZE 60

struct pos;

class DisplayDriver
{
friend class Player;
private:
	
public:

	

	DisplayDriver() {
		cout << "Initializing map..." << endl;
	}
	void printMap();

	
	
};

#endif

