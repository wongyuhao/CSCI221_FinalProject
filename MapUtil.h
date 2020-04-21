#ifndef MAP_UTIL
#define MAP_UTIL

#include "Config.h"

#include <cassert>
#include <algorithm>
using namespace std;

//All printX() functions assigns the character c[0]/c[1] alternatively to gameMap[][] in the...

class MapUtil {
private:
	//returns whether the coordinates is within the map boundaries (including the borders)
	static bool outOfBounds(const int X, const int Y);
public:
	//add buildings into gameMap using the print functions below
	static void addBuildings(char gameMap[MAPHEIGHT][MAPWIDTH]);
	
	//horizontal line (x, y1..y2)
	static void printHorizontalLine(char gameMap[MAPHEIGHT][MAPWIDTH], const int x, const int y1, const int y2, const char c[3]);
	//vertical line (x1..x2, y)
	static void printVerticalLine(char gameMap[MAPHEIGHT][MAPWIDTH], const int y, const int x1, const int x2, const char c[3]);

	//rectangle (x1..x2, y1..y2)
	static void printRectangle(char gameMap[MAPHEIGHT][MAPWIDTH], const int x1, const int y1, const int x2, const int y2, const char c[3]);
};

#endif
