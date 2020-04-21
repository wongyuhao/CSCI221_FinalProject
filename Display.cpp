#include <iomanip>
#include <algorithm>

#include "Display.h"
#include "Resource.h"

vector<Player> playerList = {};
int aliveCount = 0;

void Display::printMap() const { 
	for (int col = 0; col < MAPWIDTH; col++) {
		if (col % 2 == 0) {
			cout << col % 10;
		}
		else cout << " ";
	}
	cout << endl;
	for (int row = 0; row < MAPHEIGHT; row++) {
		for (int col = 0; col < MAPWIDTH; col++) {
			cout<< gameMap[row][col];
		}
		cout << " " << row;
		cout << endl;
	}
}

void Display::initMap() {
	for (int row = 0; row < MAPHEIGHT; row++) {
		for (int col = 0; col < MAPWIDTH; col++) {
			gameMap[row][col] = BLANK;
		}
	}

	for (int row = 0; row < MAPHEIGHT; row++) {

		if (row == 0 || row == MAPHEIGHT-1) { //print borders

			for (int col = 0; col < MAPWIDTH; col++) {
				gameMap[row][col] = '#'; //print borders
			}

		}
		else {  
			for (int col = 0; col < MAPWIDTH; col++) {
				if (col == 0 || col == MAPWIDTH - 1) {
					gameMap[row][col] = '#'; //print borders
				}
			}
		}
	}
	
	//populate buildings
	MapUtil::addBuildings(gameMap);

	//populate players
	for (int i = 0; i < playerList.size(); i++) {
		while (gameMap[playerList[i].getPosX()][playerList[i].getPosY()] != BLANK) {
			playerList[i] = Player(playerList[i].getID());
		}
		gameMap[playerList[i].getPosX()][playerList[i].getPosY()] = playerList[i].getID();
	}
}

void Display::printPlayerStats(Player* const player) const {
	cout << string(30, '=') << endl;
	
	cout << "Player " << player->getID() << "'s turn" << endl;
	cout << "Round " << roundCounter << "/" << ROUND_LIMIT << endl << endl;
	
	cout << "HP: " << player->getHealthStat();
	cout << " | ATK: " << player->getAttackStat();
	if(player->getEquippedWeaponItem().first >= 0 && player->getEquippedWeaponItem().first < itemList.size()) {
		const Item* const item = itemList[player->getEquippedWeaponItem().first];
		if(item->getType() == "Weapon (Splash)") cout << " (radius: " << item->getRadius() << ")";
	}
	cout << " | ENERGY: " << player->getRemainingMoves() << "/" << player->getEnergyStat();
	cout << endl;
	
	cout << "Currency: " << player->getCurrency() << endl;
	cout << "Current coordinate: (" << player->getPosY() << ", " << player->getPosX() << ")" << endl;
	cout << string(30, '=') << endl;
}

bool Display::cmpKillCount(const Player* const p1, const Player* const p2) {
	const int hp1 = p1->getHealthStat();	const int hp2 = p2->getHealthStat();
	const int k1 = p1->getKillCount();		const int k2 = p2->getKillCount();
	const bool a1 = hp1>0;					const bool a2 = hp2>0;
	const char ID1 = -p1->getID();			const char ID2 = -p2->getID();
	
	return tie(a1, k1, hp1, ID1) > tie(a2, k2, hp2, ID2);
}

vector<const Player*> Display::printLeaderboard() const {
	vector<const Player*> leaderboard;
	for(int i = 0; i < playerList.size(); i++) {
		leaderboard.push_back(&playerList[i]);
	}
	
	sort(leaderboard.begin(), leaderboard.end(), cmpKillCount);
	
	const vector<string> labels = {"No", "Player    ", "Kills", "HP ", "Coordinates"};
	vector<int> colSize;
	int tableWidth = 0;
	for(string label: labels) {
		colSize.push_back(label.length() + 2);
		tableWidth += colSize.back();
	}
	
	//printing table header
	cout << string(tableWidth, '=') << endl;
	cout << "LEADERBOARD" << endl << endl;
	for(int i = 0; i < labels.size(); i++) {
		cout << left << setw(colSize[i]) << labels[i];
	}
	cout << endl << string(tableWidth, '-') << endl;
	
	for(int i = 0; i < leaderboard.size(); i++) {
		const Player* const player = leaderboard[i];
		ostringstream coordinates;
		coordinates << "(" << player->getPosY() << ", " << player->getPosX() << ")";
		cout<< left
			<< setw(colSize[0]) << i+1
			<< setw(colSize[1]) << string("Player ")+player->getID()
			<< setw(colSize[2]) << player->getKillCount()
			<< setw(colSize[3]) << player->getHealthStat()
			<< setw(colSize[4]) << coordinates.str()
			<< endl;
	}
	
	cout << string(tableWidth, '=') << endl << endl;
	
	return leaderboard;
}

void Display::printItem(const Item* item, const vector<int>& colSize, const int type, const int count) const {
	//print in inventory
	if (type == 0) {
		cout<< right << setw(colSize[0]) << item->getID() << " "
			<< left << setw(colSize[1]) << item->getName()
			<< setw(colSize[2]) << item->getType()
			<< setw(colSize[3]) << item->getStat()
			<< setw(colSize[4]) << (item->getRange()==0 ? "-" : to_string(item->getRange()))
			<< setw(colSize[5]) << (item->getRadius()==0 ? "-" : to_string(item->getRadius()))
			<< setw(colSize[6]) << item->getEnergyCost()
			<< setw(colSize[7]) << count
			<< endl;
	}
	
	//print in shop
	else {
		cout<< right << setw(colSize[0]) << item->getID() << " "
			<< left << setw(colSize[1]) << item->getName()
			<< left << setw(colSize[2]) << item->getType()
			<< setw(colSize[3]) << item->getStat()
			<< setw(colSize[4]) << (item->getRange()==0 ? "-" : to_string(item->getRange()))
			<< setw(colSize[5]) << (item->getRadius()==0 ? "-" : to_string(item->getRadius()))
			<< setw(colSize[6]) << item->getCost()
			<< setw(colSize[7]) << item->getEnergyCost()
			<< setw(colSize[8]) << item->getDurability()
			<< endl;
	}
}

void Display::removeDeadPlayers(const vector<int>& deadPlayers) {
	for(int playerIndex: deadPlayers) {
		const Player& player = playerList[playerIndex];
		gameMap[player.getPosX()][player.getPosY()] = BLANK;
	}
	aliveCount -= deadPlayers.size();
}

void Display::playerMenu() {
	system("cls");
	printMap();
	
	Player* currentPlayer = &playerList[currentTurn];
	printPlayerStats(currentPlayer);
	
	cout <<"[0] MOVE" << endl;
	cout <<"[1] ATTACK"<< endl;
	cout <<"[2] INVENTORY" << endl;
	cout <<"[3] SHOP" << endl;
	cout <<"[4] LEADERBOARD" << endl;
	cout <<"[5] END TURN"<< endl << endl;
	
	cout << "CHOOSE AN ACTION: ";
	
	while(true) {
		int option = UI::readInt(0,5);
		cout << endl;
		switch (option) {
			//move
			case 0 : {
				cout << "Enter target x-coordinate: ";
				int tgtY = UI::readInt(1, MAPWIDTH-2);
				cout << "Enter target y-coordinate: ";
				int tgtX = UI::readInt(1, MAPHEIGHT-2);
				
				currentPlayer->move(tgtX, tgtY, gameMap); 
				
				return;
			}
			
			//attack
			case 1 : {				
				//has weapon; use weapon
				if(currentPlayer->getEquippedWeaponItem().first != -1) {
					const Item *item = itemList[currentPlayer->getEquippedWeaponItem().first];
					
					if(currentPlayer->getRemainingMoves() < item->getEnergyCost()) {
						cout << "Insufficient energy." << endl << endl;
						return;
					}
					
					vector<int> deadPlayers = item->use(currentPlayer, playerList);
					removeDeadPlayers(deadPlayers);
					
					currentPlayer->addKillCount(deadPlayers.size());
					currentPlayer->addEquippedItem(item->getID(), item->getType(), item->getStat(), -1);
					currentPlayer->addRemainingMoves(-item->getEnergyCost());
					
					if(currentPlayer->getHealthStat() <= 0) incrementCurrentTurn();
					return;
				}
				
				//no weapon; default attack
				if(currentPlayer->getRemainingMoves() < DEFAULT_ATTACK_ENERGY_COST) {
					cout << "Insufficient energy." << endl << endl;
					return;
				}
				
				vector<int> deadPlayers = currentPlayer->defaultAttack(playerList);
				removeDeadPlayers(deadPlayers);
				
				currentPlayer->addKillCount(deadPlayers.size());
				
				if(currentPlayer->getHealthStat() <= 0) incrementCurrentTurn();
				
				return;
			}
			
			//inventory: show/use items
			case 2 : {
				const vector<int> colSize = {3, 30, 17, 6, 7, 8, 13, 18};
				const vector<string> labels = {"ID ", "Name", "Type", "Stat", "Range", "Radius", "Energy cost", "Count/Durability"};
				int menuWidth = 0;
				for(int sz: colSize) menuWidth += sz;
				
				cout << "PLAYER " << currentPlayer->getID() << "'s INVENTORY" << endl << endl;
				
				for(int i = 0; i < labels.size(); i++) {
					if(i == 0) {
						cout << right << setw(colSize[i]-1) << labels[i];
					}
					else {
						cout << left << setw(colSize[i]) << labels[i];
					}
				}
				cout << endl;
				
				cout << string(menuWidth,'-') << endl;
				
				//print weapon items
				const pair<int,int>& equippedWeaponItem = currentPlayer->getEquippedWeaponItem();
				if(equippedWeaponItem.first != -1) {
					const Item *item = itemList[equippedWeaponItem.first];
					printItem(item, colSize, 0, equippedWeaponItem.second);
				}
				
				//print healing items
				const map<int,int>& equippedHealingItems = currentPlayer->getEquippedHealingItems();
				for (pair<int,int> itemPair: equippedHealingItems) {
					const Item *item = itemList[itemPair.first];
					printItem(item, colSize, 0, itemPair.second);
				}
				
				//print energy items
				const pair<int,int>& equippedEnergyItem = currentPlayer->getEquippedEnergyItem();
				if(equippedEnergyItem.first != -1) {
					const Item *item = itemList[equippedEnergyItem.first];
					printItem(item, colSize, 0, equippedEnergyItem.second);
				}
				
				//prompt user to choose item
				cout << endl
					 << "[-1] BACK" << endl
					 << "[ITEM ID] USE ITEM" << endl << endl
					 
					 << "CHOOSE AN OPTION: ";
				
				int option = UI::readInt(-1, itemList.size()-1);
				
				if(option == -1) return;
				
				const Item *item = itemList[option];
				
				//user can only use healing items as other items are applied automatically when bought
				if(item->getType() != "Healing") {
					cout << "This item is not usable." << endl;
					return;
				}
				
				//check that user has the item
				if(equippedHealingItems.find(option) == equippedHealingItems.end()) {
					cout << "Item not found in inventory." << endl;
					return;
				}
				
				item->use(currentPlayer, playerList);
				currentPlayer->addEquippedItem(item->getID(), item->getType(), item->getStat(), -1);
				currentPlayer->addRemainingMoves(-item->getEnergyCost());
				
				return;
			}
			
			//shop
			case 3 : {
				const vector<int> colSize = {3, 30, 17, 6, 7, 8, 6, 13, 13};
				const vector<string> labels = {"ID ", "Name", "Type", "Stat", "Range", "Radius", "Cost", "Energy cost", "Durability"};
				int menuWidth = 0;
				for(int sz: colSize) menuWidth += sz;
				
				cout << "SHOP" << endl << endl;
				
				for(int i = 0; i < labels.size(); i++) {
					if(i == 0) {
						cout << right << setw(colSize[i]-1) << labels[i];
					}
					else {
						cout << left << setw(colSize[i]) << labels[i];
					}
				}
				cout << endl;
				
				cout << string(menuWidth,'-') << endl;
				for (const Item* item: itemList) {
					printItem(item, colSize, 1);
				}
				
				//prompt user to buy item/return			
				cout << endl
					 << "[-1] BACK" << endl
					 << "[ITEM ID] BUY ITEM" << endl << endl
					 
					 << "CHOOSE AN OPTION: ";
				
				int option = UI::readInt(-1, itemList.size());
				
				if(option == -1) return;
				
				const Item *item = itemList[option];
				
				//add item to user, deduct currency
				item->buyItem(currentPlayer);
				return;
			}
			
			//leaderboard
			case 4 : {
				printLeaderboard();
				return;
			}
			
			//end turn
			case 5 : {
				incrementCurrentTurn();
				system("cls");
				if(roundCounter > ROUND_LIMIT) return;
				
				cout << "Pass the device to Player " << char('A'+currentTurn) << "." << endl;
				return;
			}
			
			//invalid choice; prompts error message
			default: {
				cout << "Invalid choice. Try again." << endl;
			}
		}
	}
}
