#include "Player.h"

 int Player::playerCount = 0;

 int Player::getPlayerCount() {
	 return playerCount;
 }

 vector <struct pos> Player::coordinates = {};

 Player::Player(int healthStat,int attackStat):
	healthStat(healthStat),
	attackStat(attackStat)
{
	
	myPos.x = (rand() % 58) + 1;
	myPos.y = (rand() % 28) + 1;
	Player::playerCount++;
	setPlayerID(static_cast<char>(Player::playerCount + 64));
	myPos.ID = getPlayerID();

	cout << "Creating Player "<< getPlayerID()<<" at x = " << myPos.x<<", y = "<< myPos.y<<endl;
	
	cout << "Total players created: " << getPlayerCount() << endl;

	coordinates.push_back(myPos);
}


