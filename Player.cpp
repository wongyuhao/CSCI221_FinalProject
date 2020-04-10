#include <queue>

#include "Player.h"
#include "Config.h"

const int INF = int(1e9);
const int dx[4] = {0, 0, -1, 1};
const int dy[4] = {-1, 1, 0, 0};

int Player::uniquePlayers = 0;

int Player::getPlayerCount()  {
	return uniquePlayers;
}

int Player::getHealthStat() const {
	return healthStat;
}
int Player::getAttackStat() const {
	return attackStat;
}
int Player::getMovementStat() const {
	return movementStat;
}
int Player::getCurrency() const {
	return currency;
}
int Player::getRemainingMoves() const {
	return remainingMoves;
}
map<int,int>& Player::getEquippedItems() {
	return equippedItems;
}


void Player::addHealthStat(const int _health) {
	healthStat += _health;
}
void Player::addAttackStat(const int _attack) {
	attackStat += _attack;
}
void Player::addMovementStat(const int _movement) {
	movementStat += _movement;
}
void Player::addCurrency(const int _currency) {
	currency += _currency;
}


Player::Player(int healthStat, int attackStat, int movementStat, int currency):
	Entity(
		static_cast<char>(uniquePlayers + 65),
		uniform_int_distribution<int>(1, MAPHEIGHT-1)(rng),
		uniform_int_distribution<int>(1, MAPWIDTH-1)(rng)
	),
	healthStat(healthStat),
	attackStat(attackStat),
	movementStat(movementStat),
	currency(currency),
	remainingMoves(0)
	
{
	Player::uniquePlayers++;	
	cout << getPlayerCount()
		<<": Spawning Player "<< getID()<<" at [ " << getPosX()<<" ,"<< getPosY()<<" ]"<<endl;
}

void Player::beginTurn() {
	remainingMoves = movementStat;
}

void BFS(const int sourceX, const int sourceY, int dist[MAPHEIGHT][MAPWIDTH], Entity* gameMap[MAPHEIGHT][MAPWIDTH]);

void Player::move(const int targetX, const int targetY, Entity* gameMap[MAPHEIGHT][MAPWIDTH]) {
	int currentX = getPosX();
	int currentY = getPosY();
	int dist[MAPHEIGHT][MAPWIDTH];
	BFS(currentX, currentY, dist, gameMap);
	
	if(remainingMoves < dist[targetX-1][targetY-1]){
		cout << "[Player " << getID() << "] You do not have enough remaining moves." << endl;
		return;
	}
	
	setPosX(targetX-1);
	setPosY(targetY-1);
	remainingMoves -= dist[targetX-1][targetY-1];
}

void Player::endTurn(int &currentTurn, int &roundCounter) {
	remainingMoves = 0;
	cout << "Ending Turn..." << endl;
	if (currentTurn >= uniquePlayers-1) {
		currentTurn = 0;
		roundCounter++;
		cout << "Moving to round " << roundCounter << endl;
	}
	else {
		currentTurn++;
	}
}

void Player::attack(Player& target) {
	int dist = abs(getPosX() - target.getPosX()) + abs(getPosY() - target.getPosY());
	if(dist > 1) {
		cout << "The target is not in range." << endl;
		return;
	}
	
	target.addHealthStat(-attackStat);
	if(target.getHealthStat() <= 0) target.dead();
}

void Player::dead() {
	uniquePlayers--;
	
}

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
