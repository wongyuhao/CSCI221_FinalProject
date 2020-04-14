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
extern int aliveCount;

class Display
{
private:
	Entity* gameMap[MAPHEIGHT][MAPWIDTH]; //2D array of all entity objects used in the game
	
	void initMap(); //initializes the gameMap with objects from building, player, and Entity vectors in Resource.h
	
public:

	Display() //constructor 
	{
		aliveCount = playerList.size();
		initMap();
	}
	void printMap() const; //iterates through the gameMap array to print every element in a grid
	void printPlayerStat(Player* player, bool active = true) const;
	void removeDeadPlayers(const vector<int>& deadPlayers); //removes dead players from map
	void playerMenu(); //switch menu to prompt specific player for action during their turn
	
	inline void incrementCurrentTurn(){ //increments to next turn or loops back to first player's turn
		playerList[currentTurn].endTurn();
		currentTurn++; currentTurn %= playerList.size();
		playerList[currentTurn].beginTurn();
	}
	
	bool promptYN(string) const; //prompts the user for yes/no answer and returns boolean value
};

#endif
