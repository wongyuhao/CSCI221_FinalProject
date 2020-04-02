#include "Player.h"

 int Player::playerCount = 0;

 int Player::getPlayerCount()  {
	 return playerCount;
 }


 Player::Player(int healthStat,int attackStat):
	healthStat(healthStat),
	attackStat(attackStat),
	 Entity(
		 static_cast<char>(Player::playerCount + 64),
		 ((rand() % (MAPSIZE * 2 - 2)) + 1),
		 ((rand() % (MAPSIZE - 2)) + 1)
		 )
{
	Player::playerCount++;	
	cout << getPlayerCount()
		<<". Creating Player "<< getID()<<" at [ " << getPosX()<<" ,"<< getPosY()<<" ]"<<endl;
}


