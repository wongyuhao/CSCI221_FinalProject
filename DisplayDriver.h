#ifndef DISPLAYDRIVER_H
#define DISPLAYDRIVER_H

#include <iostream>
using namespace std;

#define ROWSIZE 30
#define COLSIZE 60
class DisplayDriver
{
private:
	
public:
	DisplayDriver() {
		cout << "Initializing map..." << endl;
	}
	void printMap();
};

#endif

