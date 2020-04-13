#include <iomanip>
#include <typeinfo>

#include "Display.h"
#include "Resource.h"

vector<Player> playerList = {};
int aliveCount = 0;

void Display::printMap() const { 
	cout << "Printing Map..." << endl;
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
	cout << "Printing Complete!" << endl;
}

void Display::initMap() {

	cout << "Initializing map..." << endl;

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
	
	cout << "Initialization Complete!" << endl;

}

void Display::printPlayerStat(Player* player, bool active) const {
	cout << string(30, '=') << endl;		
	if(!active) {
		cout << "Player " << player->getID() << "'s turn" << endl << endl;
		cout << "HP: " << player->getHealthStat() << endl;
		cout << "Current coordinate: (" << player->getPosY() << ", " << player->getPosX() << ")" << endl;
		cout << string(30, '=') << endl;
	}
	else {
		cout << "PLAYER " << player->getID() << endl << endl;
		cout << "HP: " << player->getHealthStat() << " | ATK: " << player->getAttackStat() << " | MAX MOVES: " << player->getMovementStat() << endl;
		cout << "Currency: " << player->getCurrency() << endl;
		cout << "Remaining moves: " << player->getRemainingMoves() << endl;
		cout << "Current coordinate: (" << player->getPosY() << ", " << player->getPosX() << ")" << endl;
		cout << string(30, '=') << endl;
	}
}

void Display::removeDeadPlayers(const vector<int>& deadPlayers) {
	for(int playerIndex: deadPlayers) {
		const Player& player = playerList[playerIndex];
		delete gameMap[player.getPosX()][player.getPosY()];
		gameMap[player.getPosX()][player.getPosY()] = new Entity(' ', player.getPosX(), player.getPosY());
	}
}

void Display::playerMenu() {
	Player* currentPlayer = &playerList[currentTurn];
	printPlayerStat(currentPlayer);
	
	cout <<"[0] MOVE" << endl;
	cout <<"[1] ATTACK"<< endl;
	cout <<"[2] ITEMS" << endl;
	cout <<"[3] SHOP" << endl;
	cout <<"[4] PLAYERS" << endl;
	cout <<"[5] MAP" << endl;
	cout <<"[6] END TURN"<< endl;
	cout << "CHOOSE AN ACTION: ";
	
	while(true) {
		int option;
		cin >> option;
		cout << endl;
		switch (option) {
			case 0 : {
				//move
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

				return;
			}
			
			case 1 : {
				// attack
				cout << "Select target: ";
				char targetID;
				cin >> targetID;
				int targetIndex = toupper(targetID) - 'A';
				
				while (true) {
					//check range
					if(targetIndex < 0 || targetIndex >= playerList.size()) {
						cout << "Invalid player. Try again." << endl;
						cin >> targetIndex;
						continue;
					}
					
					//check that target is alive
					if(playerList[targetIndex].getHealthStat() <= 0) {
						cout << "Target player is dead. Try again." << endl;
						cin >> targetIndex;
						continue;
					}
					
					//All checks passed
					break;
				}
				
				currentPlayer->attack(playerList[targetID]);
				
				return;
			}
			
			case 2 : {
				//show/use items
				cout << setw(3) << "ID" << setw(10) << "Name" << setw(5) << "Count" << endl;
				
				const map<int,int>& currentEquippedItems = currentPlayer->getEquippedItems();
				for (pair<int,int> itemPair: currentEquippedItems) {
					const Item& item = itemList[itemPair.first];
					cout << setw(3) << item.getID() << setw(10) << item.getName() << setw(5) << itemPair.second << endl;
				}
				
				cout << "[-1] BACK" << endl
					 << "[ITEM ID] USE ITEM" << endl << endl
					 
					 << "CHOOSE AN OPTION: ";
				
				cin >> option;
				
				if(option == -1) return;
				
				if(currentEquippedItems.find(option) == currentEquippedItems.end()) {
					cout << "Item not found in inventory." << endl;
					return;
				}
				
				const Item& item = itemList[option];
				
				vector<int> deadPlayers = item.use(currentPlayer, playerList);
				removeDeadPlayers(deadPlayers);
				currentPlayer->addEquippedItem(item.getID(), -1);
				
				return;
			}
			
			case 3 : {
				//shop
				
				/*for (const Item& item: itemList) {
					
				}*/
				
				return;
			}
			
			case 4 : {
				//check players' status
				cout << "PLAYER STATS" << endl << endl;
				for (player: playerList) {
					printPlayerStat(&player, 0);
				}
				cout << endl;
				return;
				
			}
			
			case 5 : {
				//map
				printMap();
				return;
			}
			
			case 6 : {
				//end turn
				incrementCurrentTurn();
				return;
			}
			
			default: {
				//prompts error message
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
