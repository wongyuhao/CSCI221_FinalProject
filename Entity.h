#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
private:
	int posX;
	int posY;
	char ID;

public:
	Entity( int x, int y, char id):
	posX(x),
	posY(y),
	ID(id)
	{
		
	}

	Entity():
	posX(-1),
	posY(-1),
	ID(' ')
	{
	
	}

	inline void setPosX(int x) {
		posX = x;
	}

	inline int getPosX() const {
		return posX;
	}

	inline void setPosY(int y) {
		posY = y;
	}

	inline int getPosY()const {
		return posY;
	}

	inline void setID(char id) {
		this->ID = id;
	}
	inline char getID()const {
		return ID;
	}

};

#endif
