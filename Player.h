#pragma once

#define BASIC_HEALTH 100;
#define BASIC_ATTACK 10;
class Player
{
private:
	static int playerCount;

	int x_location;
	int y_location;

	int healthStat;
	int attackStat;

public:
	static int getPlayerCount;

	Player();
	int doDamage(int);
	void takeDamage(int);
};

