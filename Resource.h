#ifndef RESOURCE_H
#define RESOURCE_H
#include "Entity.h"

constexpr int MAPSIZE = 30;
extern int currentTurn;
extern int roundCounter;
extern int playerCount;
extern  Entity* map[MAPSIZE][MAPSIZE * 2];
#endif
