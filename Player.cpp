#include "Player.h"

int Player::uniquePlayers = 0;

int Player::getPlayerCount()  {
	return uniquePlayers;
}


Player::Player(int healthStat, int attackStat, int movementStat):
	Entity(
		static_cast<char>(uniquePlayers + 65),
		((rand() % (MAPSIZE * 2 - 2)) + 1),
		((rand() % (MAPSIZE - 2)) + 1)
	),
	healthStat(healthStat),
	attackStat(attackStat),
	movementStat(movementStat),
	remainingMoves(0)
	
{
	Player::uniquePlayers++;	
	cout << getPlayerCount()
		<<": Spawning Player "<< getID()<<" at [ " << getPosX()<<" ,"<< getPosY()<<" ]"<<endl;
}

void Player::beginTurn() {
	remainingMoves = movementStat;
}

void Player::move(const int targetX, const int targetY) {
	int currentX = getPosX();
	int currentY = getPosY();
	
	int distance = abs(currentX - targetX) + abs(currentY - targetY); // Manhattan distance
	if(remainingMoves < distance){
		cout << "[Player " << getID() << "] You do not have enough remaining moves." << endl;
		return;
	}
	
	setPosX(targetX);
	setPosY(targetY);
	remainingMoves -= distance;
}

void useItem(const Item& item) {
	
}

void buyItem(const Item& item) {
	
}

void Player::endTurn() {
	remainingMoves = 0;
	cout << "Ending Turn..." << endl;
	if (currentTurn >= playerCount-1) {
		currentTurn = 0;
		roundCounter++;
		cout << "Moving to round " << roundCounter<<endl;
	}
	else {
		currentTurn++;

	}
}

void Player::dead() {
	
}
