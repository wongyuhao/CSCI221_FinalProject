#include <queue>
#include <cassert>
#include <algorithm>

#include "Player.h"

const int INF = int(1e9);
const int dx[4] = {0, 0, -1, 1};
const int dy[4] = {-1, 1, 0, 0};

//check whether coordinates is within the map boundaries (EXCLUDING the borders)
bool outOfBounds(int X, int Y, char gameMap[MAPHEIGHT][MAPWIDTH]) {
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
int Player::getKillCount() const {
	return killCount;
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
void Player::setEnergyStat(const int _energy) {
	energyStat = _energy;
}
void Player::addCurrency(const int _currency) {
	currency += _currency;
}
void Player::addRemainingMoves(const int _moves) {
	remainingMoves += _moves;
}
void Player::addKillCount(const int _killCount) {
	killCount += _killCount;
}
void Player::addEquippedItem(const int itemID, const string itemType, const int itemStat, const int addCount) {
	switch (itemType[0]) {
		//Weapon
		case 'W': {
			assert(equippedWeaponItem.second + addCount >= 0);
			
			//if we're adding weapons, it will be replacing the current weapon
			if(addCount > 0) {
				equippedWeaponItem.first = itemID;
				equippedWeaponItem.second = addCount;
				attackStat = itemStat;
			}
			
			else {
				equippedWeaponItem.second += addCount;
				
				//if item is exhausted, reset attack stat to default
				if(equippedWeaponItem.second == 0) {
					equippedWeaponItem = pair<int,int>(-1,-1);
					attackStat = DEFAULT_ATTACK_DAMAGE;
				}
			}
			
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
			//if we're adding energy items, it will be replacing the current weapon
			if(addCount > 0) {
				equippedEnergyItem.first = itemID;
				equippedEnergyItem.second = addCount;
				energyStat = itemStat;
			}
			
			else {
				equippedEnergyItem.second += addCount;
				
				//if item is exhausted, reset energy stat to default
				if(equippedEnergyItem.second == 0) {
					equippedEnergyItem = pair<int,int>(-1,-1);
					energyStat = DEFAULT_ENERGY;
				}
			}
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
	killCount(0),
	Entity(
		ID,
		uniform_int_distribution<int>(1, MAPHEIGHT - 2)(rng),
		uniform_int_distribution<int>(1, MAPWIDTH - 2)(rng)
	),
	equippedWeaponItem(pair<int,int>(-1,-1)),
	equippedEnergyItem(pair<int,int>(-1,-1))
	
{
	equippedHealingItems.clear();
	//cout <<": Spawning Player "<< getID()<<" at [ " << getPosX()<<" ,"<< getPosY()<<" ]"<<endl;
}

//Move function

//Breadth-first-search to find shortest distance with map obstacles in mind
void BFS(const int sourceX, const int sourceY, int dist[MAPHEIGHT][MAPWIDTH], char gameMap[MAPHEIGHT][MAPWIDTH]);

void Player::move(const int targetX, const int targetY, char gameMap[MAPHEIGHT][MAPWIDTH]) {
	int currentX = getPosX();
	int currentY = getPosY();
	int dist[MAPHEIGHT][MAPWIDTH];
	BFS(currentX, currentY, dist, gameMap);
	
	if(gameMap[targetX][targetY] != BLANK) {
		cout << "Target space is not empty." << endl << endl;
		return;
	}
	
	if(remainingMoves < dist[targetX][targetY]){
		cout << "Insufficient energy." << endl << endl;
		return;
	}
	
	setPosX(targetX);
	setPosY(targetY);
	remainingMoves -= dist[targetX][targetY];
	
	//update gameMap
	gameMap[currentX][currentY] = BLANK;
	gameMap[targetX][targetY] = getID();
	
	cout << "Moved to (" << getPosY() << ", " << getPosX() << ")." << endl << endl;
}

//Default attack function
vector<int> Player::defaultAttack(vector<Player>& playerList) {
	cout << "Select target (X to go back): ";
	char targetID = UI::readChar();
	int targetIndex = toupper(targetID) - 'A';
	
	while (true) {
		//go back
		if(targetID == 'X') {
			cout << "Crisis averted." << endl;
			return vector<int>();
		}
		
		//check range
		if(targetIndex < 0 || targetIndex >= playerList.size()) {
			cout << "Invalid player. Try again." << endl;
			targetID = UI::readChar();
			targetIndex = toupper(targetID) - 'A';
			continue;
		}
		
		//check that target is alive
		if(playerList[targetIndex].getHealthStat() <= 0) {
			cout << "Target player is dead. Try again." << endl;
			targetID = UI::readChar();
			targetIndex = toupper(targetID) - 'A';
			continue;
		}
		
		//warn the player if they are attacking themselves
		if(targetID == getID()) {
			if(!UI::promptYN("Are you sure that you want to target yourself?")) {
				cout << "Crisis averted." << endl;
				return vector<int>();
			}
			else {
				cout << "You punch yourself in the face." << endl;
			}
		}
		
		//All checks passed
		break;
	}
	
	Player& target = playerList[targetIndex];
	int dist = abs(getPosX() - target.getPosX()) + abs(getPosY() - target.getPosY());
	if(dist > DEFAULT_ATTACK_RANGE) {
		cout << "The target is not in range." << endl;
		return vector<int>();
	}
	
	int oldHP = target.getHealthStat();
	target.addHealthStat(-min(oldHP, DEFAULT_ATTACK_DAMAGE));
	remainingMoves -= DEFAULT_ATTACK_ENERGY_COST;
	
	vector<int> deadPlayers;
	cout << attackStat << " damage dealt to Player " << target.getID() << " (" << oldHP << "->" << target.getHealthStat() << ")" << endl;
	if(target.getHealthStat() <= 0) {
		cout << "Player " << target.getID() << " has been slain by Player " << getID() << "!" << endl;
		deadPlayers.push_back(target.getID() - 'A');
	}
	
	return deadPlayers;
}

//BFS definition
void BFS(const int sourceX, const int sourceY, int dist[MAPHEIGHT][MAPWIDTH], char gameMap[MAPHEIGHT][MAPWIDTH]) {
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
			if(gameMap[nextX][nextY] != BLANK) continue;
			
			dist[nextX][nextY] = dist[x][y] + 1;
			vst[nextX][nextY] = true;
			q.push({nextX, nextY});
		}
	}
}
