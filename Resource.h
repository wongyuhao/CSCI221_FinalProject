#ifndef RESOURCE_H
#define RESOURCE_H

#include "Item.h"
#include <vector>

using namespace std;

extern int currentTurn; //current player index [0..playerList.size()-1]
extern int roundCounter; //current round counter

extern vector<Item*> itemList; //list of items; fetched from Items.txt before the game starts

#endif
