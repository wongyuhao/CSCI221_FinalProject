#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
private:
	int posX; //stores horizontal coordinates of the object
	int posY; //stores vertical coordinates of the object
	char ID; // ID of the object that is displayed in the console

public:
	Entity(char id, int x, int y):
	posX(x),
	posY(y),
	ID(id)
	{
		
	}

	Entity(): //default constructor used for testing
	posX(-1),
	posY(-1),
	ID(' ')
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
