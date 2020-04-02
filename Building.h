
#ifndef BUILDING_H
#define BUILDING_H

#include "Entity.h"

#define SHOP1 '$',8,4
#define SHOP2 '$',



class Building: public Entity
{
private:
	
public:
	const Building(char id, int x, int y) :Entity(id, x, y) {};

};

#endif

