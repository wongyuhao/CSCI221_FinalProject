#include "Player.h"
#include "Config.h"

int Player::playerCount = 0;

int Player::getPlayerCount()  {
	return playerCount;
}


Player::Player(int healthStat, int attackStat, int movementStat):
	Entity(
		static_cast<char>(Player::playerCount + 65),
		((rand() % (MAPSIZE * 2 - 2)) + 1),
		((rand() % (MAPSIZE - 2)) + 1)
	),
	healthStat(healthStat),
	attackStat(attackStat),
	movementStat(movementStat),
	remainingMoves(0)
	
{
	Player::playerCount++;	
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
}

void Player::dead() {
	
}
