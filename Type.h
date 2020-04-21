#ifndef TYPE_H
#define TYPE_H

class Type {
private:
	int ID; //ID of the Type

public:
	Type(int id): ID(id) {}

	Type():	ID(0) {}
	
	//mutator/accessor functions
	inline void setID(int id) {
		this->ID = id;
	}
	inline int getID() const {
		return ID;
	}
};

#endif
