#include "MapUtil.h"

bool MapUtil::outOfBounds(const int X, const int Y) {
	return (X < 0 || Y < 0 || X >= MAPHEIGHT || Y >= MAPWIDTH);
}

void MapUtil::printHorizontalLine(char gameMap[MAPHEIGHT][MAPWIDTH], const int x, const int y1, const int y2, const char c[3]) {
	assert(!outOfBounds(x,y1));
	assert(!outOfBounds(x,y2));
	
	for(int i = y1; i <= y2; i++) {
		gameMap[x][i] = c[(i-y1)%2];
	}
}

void MapUtil::printVerticalLine(char gameMap[MAPHEIGHT][MAPWIDTH], const int y, const int x1, const int x2, const char c[3]) {
	assert(!outOfBounds(x1,y));
	assert(!outOfBounds(x2,y));
	
	for(int i = x1; i <= x2; i++) {
		gameMap[i][y] = c[0];
	}
}

void MapUtil::printRectangle(char gameMap[MAPHEIGHT][MAPWIDTH], const int x1, const int x2, const int y1, const int y2, const char c[3]) {
	assert(!outOfBounds(x1,y1));
	assert(!outOfBounds(x1,y2));
	assert(!outOfBounds(x2,y1));
	assert(!outOfBounds(x2,y2));
	
	for(int i = x1; i <= x2; i++) {
		printHorizontalLine(gameMap, i, y1, y2, c);
	}
}

void MapUtil::addBuildings(char gameMap[MAPHEIGHT][MAPWIDTH]) {
	//TREES
	
	//Tree 1
	for(int i = 2; i <= 9; i++) {
		printHorizontalLine(gameMap,i,4,22-i*2,TREE);
	}
	
	//Tree 2
	printRectangle(gameMap,11,14,30,40,TREE);
	
	//Tree 3
	printHorizontalLine(gameMap,25,3,23,TREE);
	printHorizontalLine(gameMap,26,3,16,TREE);
	
	//Tree 4
	for(int i = 20; i <= 27; i++) {
		printHorizontalLine(gameMap,i,94-i*2,55,TREE);
	}
	
	
	//SWAMPS
	
	//Swamp 1
	printHorizontalLine(gameMap,8,38,42,SWAMP);
	printHorizontalLine(gameMap,9,37,43,SWAMP);
	printHorizontalLine(gameMap,10,38,42,SWAMP);
	
	//Swamp 2
	printHorizontalLine(gameMap,8,22,30,SWAMP);
	printHorizontalLine(gameMap,9,21,32,SWAMP);
	printHorizontalLine(gameMap,10,22,30,SWAMP);
	
	//Swamp 3
	printVerticalLine(gameMap,11,10,15,SWAMP);
	printVerticalLine(gameMap,12,9,16,SWAMP);
	printVerticalLine(gameMap,13,9,16,SWAMP);
	printVerticalLine(gameMap,14,10,15,SWAMP);
	
	//Swamp 4
	printHorizontalLine(gameMap,16,22,38,SWAMP);
	printHorizontalLine(gameMap,17,21,40,SWAMP);
	printHorizontalLine(gameMap,18,20,42,SWAMP);
	printHorizontalLine(gameMap,19,20,43,SWAMP);
	printHorizontalLine(gameMap,20,21,40,SWAMP);
	printHorizontalLine(gameMap,21,21,37,SWAMP);
	
	
	//CLIFFS
	
	//Cliff 1
	printRectangle(gameMap,1,4,42,56,CLIFF);
	printRectangle(gameMap,5,7,51,56,CLIFF);
	
	//Cliff 2
	printRectangle(gameMap,16,17,46,52,CLIFF);
	
	//Cliff 3
	printHorizontalLine(gameMap,18,43,44,CLIFF);
	printRectangle(gameMap,19,20,43,45,CLIFF);
	
	
	//BUSHES
	
	//Bush 1
	printVerticalLine(gameMap,17,17,23,BUSH);
	
	//Bush 2
	printHorizontalLine(gameMap,22,20,24,BUSH);
	
	//Bush 3
	printHorizontalLine(gameMap,23,25,28,BUSH);
	
	//Bush 4
	printHorizontalLine(gameMap,22,30,34,BUSH);
	
}
