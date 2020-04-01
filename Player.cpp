#include "Player.h"

 int Player::playerCount = 0;

 int Player::getPlayerCount()  {
	 return playerCount;
 }


 Player::Player(int healthStat,int attackStat):
	healthStat(healthStat),
	attackStat(attackStat)
{
	
	setPosX((rand() % (MAPSIZE*2-2)) + 1);
	setPosY((rand() % (MAPSIZE-2)) + 1);
	Player::playerCount++;
	setID(static_cast<char>(Player::playerCount + 64));
	

	cout << getPlayerCount()<<". Creating Player "<< getID()<<" at [ " << getPosX()<<" ,"<< getPosY()<<" ]"<<endl;
	

}


