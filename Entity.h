#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
private:
	char ID; // ID of the object that is displayed in the console
	int posX; //stores horizontal coordinates of the object
	int posY; //stores vertical coordinates of the object

public:
	Entity(char id, int x, int y):
	ID(id),
	posX(x),
	posY(y)
	{
		
	}

	Entity(): //default constructor used for testing
	ID(' '),
	posX(-1),
	posY(-1)
	{
	
	}

	inline void setPosX(int x) { //mutator function
		posX = x;
	}

	inline int getPosX() const { //accessor function
		return posX;
	}

	inline void setPosY(int y) { //mutator function
		posY = y;
	}

	inline int getPosY()const { //accessor function
		return posY;
	}

	inline void setID(char id) { //mutator function
		this->ID = id;
	}
	inline char getID()const { //accessor function
		return ID;
	}

};

#endif
