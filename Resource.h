#ifndef RESOURCE_H
#define RESOURCE_H

#include "Item.h"
#include "Building.h"
#include <vector>

using namespace std;

extern int currentTurn;
extern int roundCounter;

extern vector<Building> buildingList;
extern vector<Item*> itemList;

#endif
