#include <queue>
#include <cassert>

#include "Player.h"

const int INF = int(1e9);
const int dx[4] = {0, 0, -1, 1};
const int dy[4] = {-1, 1, 0, 0};

bool outOfBounds(int X, int Y, Entity* gameMap[MAPHEIGHT][MAPWIDTH]) {
	return (X <= 0 || X >= MAPHEIGHT-1 || Y <= 0 || Y >=MAPWIDTH-1);
}

//Accessors
int Player::getHealthStat() const {
	return healthStat;
}
int Player::getAttackStat() const {
	return attackStat;
}
int Player::getEnergyStat() const {
	return energyStat;
}
int Player::getCurrency() const {
	return currency;
}
int Player::getRemainingMoves() const {
	return remainingMoves;
}
const pair<int,int>& Player::getEquippedWeaponItem() const {
	return equippedWeaponItem;
}
const map<int,int>& Player::getEquippedHealingItems() const {
	return equippedHealingItems;
}
const pair<int,int>& Player::getEquippedEnergyItem() const {
	return equippedEnergyItem;
}

//Mutators
void Player::addHealthStat(const int _health) {
	healthStat += _health;
}
void Player::addAttackStat(const int _attack) {
	attackStat += _attack;
}
void Player::addEnergyStat(const int _energy) {
	energyStat += _energy;
}
void Player::addCurrency(const int _currency) {
	currency += _currency;
}
void Player::addEquippedItem(const int itemID, const string itemType, const int addCount) {
	switch (itemType[0]) {
		//Weapon
		case 'W': {
			assert(equippedWeaponItem.second + addCount >= 0);
			equippedWeaponItem.second += addCount;
			if(equippedWeaponItem.second == 0) equippedWeaponItem.first = -1;
			return;
		}
		
		//Healing
		case 'H': {
			const int currentCount = (equippedHealingItems.find(itemID)==equippedHealingItems.end() ? 0 : equippedHealingItems[itemID]);
			assert(currentCount + addCount >= 0);
			
			equippedHealingItems[itemID] += addCount;
			if(equippedHealingItems[itemID] == 0){
				equippedHealingItems.erase(itemID);
			}
			return;
		}
		
		//Energy
		case 'E': {
			assert(equippedEnergyItem.second + addCount >= 0);
			equippedEnergyItem.second += addCount;
			if(equippedEnergyItem.second == 0) equippedEnergyItem.first = -1;
			return;
		}
		
		default: {
			cout << "Error at Player.cpp::addEquippedItem(): Invalid item type." << endl;
			return;
		}
	}
}


Player::Player(
	char ID,
	int healthStat, 
	int attackStat, 
	int energyStat, 
	int currency):
	
	healthStat(healthStat),
	attackStat(attackStat),
	energyStat(energyStat),
	currency(currency),
	remainingMoves(0),
	Entity(
		ID,
		uniform_int_distribution<int>(1, MAPHEIGHT - 2)(rng),
		uniform_int_distribution<int>(1, MAPWIDTH - 2)(rng)
	),
	equippedWeaponItem(pair<int,int>(-1,-1)),
	equippedEnergyItem(pair<int,int>(-1,-1))
	
{
	equippedHealingItems.clear();
	cout <<": Spawning Player "<< getID()<<" at [ " << getPosX()<<" ,"<< getPosY()<<" ]"<<endl;
}

//Begin/end turn functions, called during beginning/end of turn
void Player::beginTurn() {
	remainingMoves = energyStat;
}
void Player::endTurn() {
	remainingMoves = 0;
	currency += 50;
}

//Move function

//Breadth-first-search to find shortest distance with map obstacles in mind
void BFS(const int sourceX, const int sourceY, int dist[MAPHEIGHT][MAPWIDTH], Entity* gameMap[MAPHEIGHT][MAPWIDTH]);

void Player::move(const int targetX, const int targetY, Entity* gameMap[MAPHEIGHT][MAPWIDTH]) {
	int currentX = getPosX();
	int currentY = getPosY();
	int dist[MAPHEIGHT][MAPWIDTH];
	BFS(currentX, currentY, dist, gameMap);
	
	if(gameMap[targetX][targetY]->getID() != ' ') {
		cout << "Target space is not empty." << endl << endl;
		return;
	}
	
	if(remainingMoves < dist[targetX][targetY]){
		cout << "You do not have enough remaining moves." << endl << endl;
		return;
	}
	
	setPosX(targetX);
	setPosY(targetY);
	remainingMoves -= dist[targetX][targetY];
	
	//update gameMap
	gameMap[currentX][currentY]->setID(' ');
	gameMap[targetX][targetY]->setID(getID());
	
	cout << "Moved to (" << getPosY() << ", " << getPosX() << ")." << endl << endl;
}

constexpr int DEFAULT_ATTACK_RANGE = 1; //range of the default attack
constexpr int DEFAULT_ATTACK_ENERGY_COST = 1; //energy cost of the default attack

//Attack function
void Player::attack(Player& target) {
	int dist = abs(getPosX() - target.getPosX()) + abs(getPosY() - target.getPosY());
	if(dist > DEFAULT_ATTACK_RANGE) {
		cout << "The target is not in range." << endl;
		return;
	}
	
	target.addHealthStat(-attackStat);
	target.addEnergyStat(-DEFAULT_ATTACK_ENERGY_COST);
}

//BFS definition
void BFS(const int sourceX, const int sourceY, int dist[MAPHEIGHT][MAPWIDTH], Entity* gameMap[MAPHEIGHT][MAPWIDTH]) {
	for(int i = 0; i < MAPHEIGHT; i++){
		for(int j = 0; j < MAPWIDTH; j++){
			dist[i][j] = INF;
		}
	}
	
	dist[sourceX][sourceY] = 0;
	
	bool vst[MAPHEIGHT][MAPWIDTH]{};
	
	queue<pair<int,int>> q;
	q.push({sourceX, sourceY});
	
	while(!q.empty()){
		int x = q.front().first, y=q.front().second;
		q.pop();
		
		vst[x][y] = true;
		for(int i = 0; i < 4; i++){
			int nextX = x + dx[i], nextY = y + dy[i];
			if(outOfBounds(nextX, nextY, gameMap)) continue;
			if(vst[nextX][nextY]) continue;
			if(gameMap[nextX][nextY]->getID() != ' ') continue;
			
			dist[nextX][nextY] = dist[x][y] + 1;
			vst[nextX][nextY] = true;
			q.push({nextX, nextY});
		}
	}
}
