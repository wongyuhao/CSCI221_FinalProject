#include <queue>

#include "Player.h"

const int INF = int(1e9);
const int dx[4] = {0, 0, -1, 1};
const int dy[4] = {-1, 1, 0, 0};

bool outOfBounds(int X, int Y, Entity* gameMap[MAPHEIGHT][MAPWIDTH]) {
	return (X <= 0 || X >= MAPHEIGHT-1 || Y <= 0 || Y >=MAPWIDTH-1);
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


Player::Player(
	char ID,
	int healthStat, 
	int attackStat, 
	int movementStat, 
	int currency):
	
	healthStat(healthStat),
	attackStat(attackStat),
	movementStat(movementStat),
	currency(currency),
	remainingMoves(0),
	Entity(
		ID,
		uniform_int_distribution<int>(1, MAPWIDTH - 2)(rng),
		uniform_int_distribution<int>(1, MAPHEIGHT - 2)(rng)
	)
	
{
	
	cout <<": Spawning Player "<< getID()<<" at [ " << getPosX()<<" ,"<< getPosY()<<" ]"<<endl;
}

void Player::beginTurn() {
	remainingMoves = movementStat;
}

// Note: source/target/current X/Y are the first/second indices of the array respectively (vertical/horizontal)

void BFS(const int sourceX, const int sourceY, int dist[MAPHEIGHT][MAPWIDTH], Entity* gameMap[MAPHEIGHT][MAPWIDTH]);

void Player::move(const int targetY, const int targetX, Entity* gameMap[MAPHEIGHT][MAPWIDTH]) {
	int currentY = getPosX();
	int currentX = getPosY();
	int dist[MAPHEIGHT][MAPWIDTH];
	BFS(currentX, currentY, dist, gameMap);
	
	if(remainingMoves < dist[targetX][targetY]){
		cout << "[Player " << getID() << "] You do not have enough remaining moves." << endl;
		return;
	}
	
	setPosX(targetX);
	setPosY(targetY);
	remainingMoves -= dist[targetX][targetY];
}

void Player::endTurn() {
	remainingMoves = 0;
	cout << "Ending Turn for Player " << getID() << "..." << endl;
	
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
