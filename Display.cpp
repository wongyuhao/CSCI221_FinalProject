#include "Display.h"
#include "Resource.h"

vector<Player> playerList = {};

void Display::printMap() const { 
	cout << "Printing Map..." << endl;
	for (int col = 0; col < MAPHEIGHT; col++) {
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
				else {

					//populate buildings
					for (int i = 0; i < buildingList.size(); i++) {
						gameMap[buildingList[i].getPosY()][buildingList[i].getPosX()] = &buildingList[i];
					}

					//populate players
					for (int i = 0; i < playerList.size(); i++) {
						if (gameMap[playerList[i].getPosY()][playerList[i].getPosX()]->getID() == ' ') {
							gameMap[playerList[i].getPosY()][playerList[i].getPosX()] = &playerList[i];
						}
						else {
							int move = playerList[i].getPosX();
							playerList[i].setPosX(move++);
							gameMap[playerList[i].getPosY()][playerList[i].getPosX()] = &playerList[i];

						}
					}
				}


				
			}

		}

	}
	cout << "Initialization Complete!" << endl;

}

void Display::playerMenu() {
	Player* currentPlayer = &playerList[currentTurn];
	cout << "Player " << currentPlayer->getID()<< "'s Turn:" << endl;
	cout <<"[" <<0 <<"] " << "MOVE" << endl;
	cout <<"[" <<1<<"] " << "ATTACK"<< endl;
	cout <<"[" <<2 <<"] " <<"INTERACT" << endl;
	cout <<"[" <<3<<"] " <<"END TURN"<< endl;
	cout << "CHOOSE AN ACTION: ";
	int options;
	cin >> options;
	cout << endl;
	switch (options) {
		case 0 :
			cout << "Enter Target Coordinates (Press Enter After Each Coordinate): "<<endl;
			
			int tgtX, tgtY;
			while (true) {
				cin >> tgtY >> tgtX;
				if ((tgtX >= MAPHEIGHT - 1) || (tgtX <= 0 )|| (tgtY >= MAPWIDTH - 1) || (tgtY <= 0) ){
					cout << "Invalid Coordinates. Try again.\n";
					continue;
				}
				else { break; }
			}
			
			currentPlayer->move(tgtX, tgtY, gameMap); 

			break;
			
		case 1 :
			break;
			
		case 2 :
			//interact
			incrementCurrentTurn(currentPlayer);
			break;
			
		case 3 :
			//end turn
			incrementCurrentTurn(currentPlayer);
			
			break;
			
		default:
			//defaults to end turn
			incrementCurrentTurn(currentPlayer);
			
			break;
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
