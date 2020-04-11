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
	
	
	
	Entity* gameMap[MAPHEIGHT][MAPWIDTH]; //2D array of all entity objects used in the game
	
	void initMap(); //initializes the gameMap with objects from building, player, and Entity vectors in Resource.h
	
public:

	Display() //constructor 
	{
		initMap(); 
		printMap();
	}
	void printMap() const; //iterates through the gameMap array to print every element in a grid
	void playerMenu(); //switch menu to prompt specific player for action during their turn
	inline void bumpConsole() { //prints newlines to push the old map out of view
		for (int i = 0; i < MAPHEIGHT; i++) {
			cout << endl;
		}
	}
	
	inline void incrementCurrentTurn(Player* pl){ //increments to next turn or loops back to first player's turn
		pl->endTurn();
		currentTurn++; currentTurn %= playerList.size();
	}
	
	bool promptYN(string) const; //prompts the user for yes/no answer and returns boolean value
};

#endif
