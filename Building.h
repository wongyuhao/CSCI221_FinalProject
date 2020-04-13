#ifndef BUILDING_H
#define BUILDING_H

#include "Entity.h"

// define constant locations of specific buildings


class Building: public Entity
{
public:
	//constructor passes arguments to Entity constrcuctor
	Building(char id, int x, int y) :Entity(id, x, y) {};

};

#endif

