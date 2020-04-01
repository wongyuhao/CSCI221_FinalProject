#include "Player.h"

 int Player::playerCount = 0;

 int Player::getPlayerCount() {
	 return playerCount;
 }





 Player::Player(int healthStat,int attackStat):
	healthStat(healthStat),
	attackStat(attackStat)
{
	
	posX = (rand() % (MAPSIZE*2-2)) + 1;
	posY = (rand() % (MAPSIZE-2)) + 1;
	Player::playerCount++;
	setPlayerID(static_cast<char>(Player::playerCount + 64));
	

	cout << "Creating Player "<< getPlayerID()<<" at x = " << posX<<", y = "<< posY<<endl;
	
	cout << "Total players created: " << getPlayerCount() << endl;

}


