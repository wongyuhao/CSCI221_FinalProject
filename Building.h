
#ifndef BUILDING_H
#define BUILDING_H

#include "Entity.h"

#define SHOP1 '$',8,4
#define SHOP2 '$',52,4
#define SHOP3 '$',8,26
#define SHOP4 '$',52,26



class Building: public Entity
{
private:
	
public:
	const Building(char id, int x, int y) :Entity(id, x, y) {};

};

#endif

