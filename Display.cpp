#include <iomanip>

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
			gameMap[row][col] = '.';
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
	for (int i = 0; i < buildingList.size(); i++) {
		gameMap[buildingList[i].getPosX()][buildingList[i].getPosY()] = buildingList[i].getID();
	}

	//populate players
	for (int i = 0; i < playerList.size(); i++) {
		while (gameMap[playerList[i].getPosX()][playerList[i].getPosY()] != BLANK) {
			playerList[i] = Player(playerList[i].getID());
		}
		gameMap[playerList[i].getPosX()][playerList[i].getPosY()] = playerList[i].getID();
	}
}

void Display::printPlayerStat(Player* const player, bool active) const {
	cout << string(30, '=') << endl;
	
	//called in "PLAYERS" menu
	if(!active) {
		cout << "PLAYER " << player->getID() << endl << endl;
		cout << "HP: " << player->getHealthStat() << endl;
		if(player->getHealthStat() <= 0) {
			cout << "[DEAD]" << endl;
		}
		else {
			cout << "Current coordinate: (" << player->getPosY() << ", " << player->getPosX() << ")" << endl;
		}
		cout << string(30, '=') << endl;
	}
	
	//called in main menu
	else {
		cout << "Player " << player->getID() << "'s turn" << endl << endl;
		cout << "HP: " << player->getHealthStat();
		cout << " | ATK: " << player->getAttackStat();
		if(player->getEquippedWeaponItem().first >= 0 && player->getEquippedWeaponItem().first < itemList.size()) {
			const Item* const item = itemList[player->getEquippedWeaponItem().first];
			if(item->getType() == "Weapon (Splash)") cout << " (radius: " << item->getRadius() << ")";
		}
		cout << " | MAX ENERGY: " << player->getEnergyStat();
		cout << endl;
		
		cout << "Currency: " << player->getCurrency() << endl;
		cout << "Energy left: " << player->getRemainingMoves() << endl;
		cout << "Current coordinate: (" << player->getPosY() << ", " << player->getPosX() << ")" << endl;
		cout << string(30, '=') << endl;
	}
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
	printPlayerStat(currentPlayer);
	
	cout <<"[0] MOVE" << endl;
	cout <<"[1] ATTACK"<< endl;
	cout <<"[2] INVENTORY" << endl;
	cout <<"[3] SHOP" << endl;
	cout <<"[4] PLAYERS" << endl;
	cout <<"[5] END TURN"<< endl << endl;
	
	cout << "CHOOSE AN ACTION: ";
	
	while(true) {
		int option;
		cin >> option;
		cout << endl;
		switch (option) {
			//move
			case 0 : {
				cout << "Enter Target Coordinates (Press Enter After Each Coordinate): "<<endl;
				
				int tgtX, tgtY;
				while (true) {
					cin >> tgtY >> tgtX;					
					if (tgtX >= MAPHEIGHT - 1 || tgtX <= 0 || tgtY >= MAPWIDTH - 1 || tgtY <= 0){
						cout << "Invalid Coordinates. Try again.\n";
						continue;
					}
					else { break; }
				}
				
				currentPlayer->move(tgtX, tgtY, gameMap); 
				
				system("pause"); return;
			}
			
			//attack
			case 1 : {				
				//has weapon; use weapon
				if(currentPlayer->getEquippedWeaponItem().first != -1) {
					const Item *item = itemList[currentPlayer->getEquippedWeaponItem().first];
					vector<int> deadPlayers = item->use(currentPlayer, playerList);
					removeDeadPlayers(deadPlayers);
					currentPlayer->addEquippedItem(item->getID(), item->getType(), item->getStat(), -1);
					currentPlayer->addRemainingMoves(-item->getEnergyCost());
					system("pause"); return;
				}
				
				//no weapon; default attack
				currentPlayer->defaultAttack(playerList);
				
				system("pause"); return;
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
				
				int option;
				cin >> option;
				
				//check that item ID is within range, or return if asked
				while(option < 0 || option >= itemList.size()) {
					if(option == -1) return;
					cout << "Invalid item ID. Try again." << endl;
					cin >> option;
				}
				
				const Item *item = itemList[option];
				
				//user can only use healing items as other items are applied automatically when bought
				if(item->getType() != "healing") {
					cout << "This item is not usable." << endl;
					system("pause"); return;
				}
				
				//check that user has the item
				if(equippedHealingItems.find(option) == equippedHealingItems.end()) {
					cout << "Item not found in inventory." << endl;
					system("pause"); return;
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
				
				int option;
				cin >> option;
				
				//check that item ID is within range, or return if asked
				while(option < 0 || option >= itemList.size()) {
					if(option == -1) return;
					cout << "Invalid item ID. Try again." << endl;
					cin >> option;
				}
				
				const Item *item = itemList[option];
				
				//add item to user, deduct currency
				item->buyItem(currentPlayer);
				system("pause"); return;
			}
			
			//check players' status: only shows HP and current coordinates
			case 4 : {
				cout << "PLAYER STATS" << endl << endl;
				for (player: playerList) {
					printPlayerStat(&player, 0);
				}
				cout << endl;
				system("pause"); return;
				
			}
			
			//end turn
			case 5 : {
				incrementCurrentTurn();
				system("cls");
				cout << "Pass the device to Player " << char('A'+currentTurn) << "." << endl;
				system("pause");
				return;
			}
			
			//invalid choice; prompts error message
			default: {
				cout << "Invalid choice. Try again." << endl;
			}
		}
	}
}
