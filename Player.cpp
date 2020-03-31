#include "Player.h"

 int Player::playerCount = 0;
 int Player::getPlayerCount() {
	 return playerCount;
 }

Player::Player(int healthStat,int attackStat):
	healthStat(healthStat),
	attackStat(attackStat)
{
	srand(time(NULL));
	pos myPos(((rand() % 58) + 1), ((rand() % 28) + 1));
	Player::playerCount++;
	playerID = static_cast<char>(Player::playerCount + 64);

	cout << "Creating Player "<< getPlayerID()<<" at x = " << myPos.x<<", y = "<< myPos.y<<endl;
	
	cout << "Total players created: " << getPlayerCount() << endl;

}


