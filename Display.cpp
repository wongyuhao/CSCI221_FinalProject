#include <iomanip>
#include <typeinfo>

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
			cout<< gameMap[row][col]->getID();
		}
		cout << " " << row;
		cout << endl;
	}
}

void Display::initMap() {
	for (int row = 0; row < MAPHEIGHT; row++) {
		for (int col = 0; col < MAPWIDTH; col++) {
			gameMap[row][col] = new Entity(' ', row, col);
		}
	}

	for (int row = 0; row < MAPHEIGHT; row++) {

		if (row == 0 || row == MAPHEIGHT-1) { //print borders

			for (int col = 0; col < MAPWIDTH; col++) {
				gameMap[row][col] = new Entity('#',row,col);//print borders
			}

		}
		else {  
			for (int col = 0; col < MAPWIDTH; col++) {
				if (col == 0 || col == MAPWIDTH - 1) {
					gameMap[row][col] = new Entity('#', row, col);//print borders
				}
			}
		}
	}
	
	//populate buildings
	for (int i = 0; i < buildingList.size(); i++) {
		gameMap[buildingList[i].getPosX()][buildingList[i].getPosY()] = &buildingList[i];
	}

	//populate players
	for (int i = 0; i < playerList.size(); i++) {
		if (gameMap[playerList[i].getPosX()][playerList[i].getPosY()]->getID() == ' ') {
			gameMap[playerList[i].getPosX()][playerList[i].getPosY()] = &playerList[i];
		}
		else {
			playerList[i] = Player(playerList[i].getID());
			gameMap[playerList[i].getPosX()][playerList[i].getPosY()] = &playerList[i];

		}
	}
}

void Display::printPlayerStat(Player* player, bool active) const {
	cout << string(30, '=') << endl;		
	if(!active) {
		cout << "PLAYER " << player->getID() << "'s turn" << endl << endl;
		cout << "HP: " << player->getHealthStat() << endl;
		cout << "Current coordinate: (" << player->getPosY() << ", " << player->getPosX() << ")" << endl;
		cout << string(30, '=') << endl;
	}
	else {
		cout << "Player " << player->getID() << "'s turn" << endl << endl;
		cout << "HP: " << player->getHealthStat() << " | ATK: " << player->getAttackStat() << " | MAX MOVES: " << player->getEnergyStat() << endl;
		cout << "Currency: " << player->getCurrency() << endl;
		cout << "Remaining moves: " << player->getRemainingMoves() << endl;
		cout << "Current coordinate: (" << player->getPosY() << ", " << player->getPosX() << ")" << endl;
		cout << string(30, '=') << endl;
	}
}

void Display::removeDeadPlayers(const vector<int>& deadPlayers) {
	for(int playerIndex: deadPlayers) {
		const Player& player = playerList[playerIndex];
		gameMap[player.getPosX()][player.getPosY()]->setID(' ');
	}
}

void Display::playerMenu() {
	system("cls");
	printMap();
	
	Player* currentPlayer = &playerList[currentTurn];
	printPlayerStat(currentPlayer);
	
	cout <<"[0] MOVE" << endl;
	cout <<"[1] ATTACK"<< endl;
	cout <<"[2] ITEMS" << endl;
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
					const Item& item = itemList[currentPlayer->getEquippedWeaponItem().first];
					vector<int> deadPlayers = item.use(currentPlayer, playerList);
					removeDeadPlayers(deadPlayers);
					currentPlayer->addEquippedItem(item.getID(), item.getType(), -1);
					system("pause"); return;
				}
				
				//no weapon; default attack
				cout << "Select target: ";
				char targetID;
				cin >> targetID;
				int targetIndex = toupper(targetID) - 'A';
				
				while (true) {
					//check range
					if(targetIndex < 0 || targetIndex >= playerList.size()) {
						cout << "Invalid player. Try again." << endl;
						cin >> targetID;
						continue;
					}
					
					//check that target is alive
					if(playerList[targetIndex].getHealthStat() <= 0) {
						cout << "Target player is dead. Try again." << endl;
						cin >> targetID;
						continue;
					}
					
					//All checks passed
					break;
				}
				
				currentPlayer->attack(playerList[targetID]);
				
				system("pause"); return;
			}
			
			//show/use items
			case 2 : {
				cout << "PLAYER " << currentPlayer->getID() << "'s INVENTORY" << endl << endl;
				
				cout << setw(3) << "ID" << setw(10) << "Name" << setw(5) << "Count/Durability" << endl;
				cout << string(40,'-') << endl;
				
				//print weapon items
				const pair<int,int>& equippedWeaponItem = currentPlayer->getEquippedWeaponItem();
				if(equippedWeaponItem.first != -1) {
					const Item& item = itemList[equippedWeaponItem.first];
					cout << setw(3) << item.getID() << setw(10) << item.getName() << setw(5) << equippedWeaponItem.second << endl;
				}
				
				//print healing items
				const map<int,int>& equippedHealingItems = currentPlayer->getEquippedHealingItems();
				for (pair<int,int> itemPair: equippedHealingItems) {
					const Item& item = itemList[itemPair.first];
					cout << setw(3) << item.getID() << setw(10) << item.getName() << setw(5) << itemPair.second << endl;
				}
				
				//print energy items
				const pair<int,int>& equippedEnergyItem = currentPlayer->getEquippedEnergyItem();
				if(equippedEnergyItem.first != -1) {
					const Item& item = itemList[equippedEnergyItem.first];
					cout << setw(3) << item.getID() << setw(10) << item.getName() << setw(5) << equippedEnergyItem.second << endl;
				}
				
				//prompt user to choose item
				cout << "[-1] BACK" << endl
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
				
				const Item& item = itemList[option];
				
				//user can only use healing items as other items are applied automatically when bought
				if(item.getType() != "healing") {
					cout << "This item is not usable." << endl;
					system("pause"); return;
				}
				
				//check that user has the item
				if(equippedHealingItems.find(option) == equippedHealingItems.end()) {
					cout << "Item not found in inventory." << endl;
					system("pause"); return;
				}
				
				item.use(currentPlayer, playerList);
				currentPlayer->addEquippedItem(item.getID(), item.getType(), -1);
				
				return;
			}
			
			//shop
			case 3 : {
				cout << "SHOP" << endl << endl;
				
				cout << setw(3) << "ID" << setw(10) << "Name" << setw(5) << "Cost" << setw(5) << "Energy Cost" << endl;
				cout << string(40,'-') << endl;
				for (const Item& item: itemList) {
					cout << setw(3) << item.getID() << setw(10) << item.getName() << setw(5) << item.getCost() << setw(5) << item.getEnergyCost() << endl;
				}
				
				//prompt user to buy item/return			
				cout << "[-1] BACK" << endl
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
				
				const Item& item = itemList[option];
				
				//check that user has enough currency
				if(currentPlayer->getCurrency() < item.getCost()) {
					cout << "Insufficient currency." << endl;
					system("pause"); return;
				}
				
				//if the selected item will overwrite the user's weapon/energy item, warn the user
				if((item.getType()[0] == 'W' && currentPlayer->getEquippedWeaponItem().first != -1) ||
				   (item.getType()[0] == 'E' && currentPlayer->getEquippedEnergyItem().first != -1)
				)
				{
					string itemType = item.getType();
					tolower(itemType[0]);
					if(!promptYN("This will replace your current " + itemType + " item. Proceed?")) system("pause"); return;
				}
				
				//add item to user, deduct currency
				currentPlayer->addEquippedItem(item.getID(), item.getType(), 1);
				currentPlayer->addCurrency(-item.getCost());
				
				cout << "Item \"" << item.getName() << "\" purchased successfully." << endl;
				
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
				return;
			}
			
			//invalid choice; prompts error message
			default: {
				cout << "Invalid choice. Try again." << endl;
			}
		}
	}
}

//prompts user the string prompt, receives Y/N
bool Display::promptYN(string prompt) const {
	cout << prompt << " (Y/N)" << endl;
	
	string input;
	cin >> input;
	
	while(input.length() != 1 || (tolower(input[0]) != 'y' && tolower(input[0]) != 'n')){
		cout << "Invalid response. Please try again. (Y/N)" << endl;
		cin >> input;
	}
	
	return (tolower(input[0]) == 'y');
}
