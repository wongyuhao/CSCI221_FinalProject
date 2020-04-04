#include "Display.h"

vector < Building> Display::local_BL;
vector < Player> Display::local_PL;



void Display::printMap() const {
	cout << "Printing Map..." << endl;
	for (int col = 0; col < MAPSIZE * 2; col++) {
		if (col % 2 == 0) {
			cout << col % 10;
		}
		else cout << " ";
	}
	cout << endl;
	for (int row = 0; row < MAPSIZE ; row++) {
		for (int col = 0; col < MAPSIZE*2; col++) {
			cout<< map[row][col]->getID();
		}
		cout << " " << row;
		cout << endl;
	}
	cout << "Printing Complete!" << endl;
}

void Display::initMap() {

	cout << "Initializing map..." << endl;

	

	for (int row = 0; row < MAPSIZE; row++) {
		for (int col = 0; col < MAPSIZE*2; col++) {
			map[row][col] = new Entity(' ', row, col);
		}
	}



	for (int row = 0; row < MAPSIZE; row++) {

		if (row == 0 || row == MAPSIZE-1) { //print borders

			for (int col = 0; col < MAPSIZE*2; col++) {
				map[row][col] = new Entity('#',row,col);//print borders
			}

		}
		else {  
			for (int col = 0; col < MAPSIZE*2; col++) {
				if (col == 0 || col == MAPSIZE*2 - 1) {
					map[row][col] = new Entity('#', row, col);//print borders
				}
				else {

					//populate buildings
					for (int i = 0; i < local_BL.size(); i++) {
						map[local_BL[i].getPosY()][local_BL[i].getPosX()] = &local_BL[i];
					}

					//populate players
					for (int i = 0; i < local_PL.size(); i++) {
						if (map[local_PL[i].getPosY()][local_PL[i].getPosX()]->getID() == ' ') {
							map[local_PL[i].getPosY()][local_PL[i].getPosX()] = &local_PL[i];
						}
						else {
							int move = local_PL[i].getPosX();
							local_PL[i].setPosX(move++);
							map[local_PL[i].getPosY()][local_PL[i].getPosX()] = &local_PL[i];

						}
					}
				}


				
			}

		}

	}
	cout << "Initialization Complete!" << endl;

}

void Display::playerMenu() {
	Player* currentPlayer = &local_PL[currentTurn];
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
		{	cout << "Enter Target Coordinates (x,y): ";
			
			int tgtX, tgtY;
			while (true) {
				cin >> tgtX >> tgtY;
				if ((tgtX >= MAPSIZE * 2 - 1 || tgtX <= 0) && (tgtY >= MAPSIZE - 1 || tgtY <= 0)) {
					cout << "Invalid Coordinates. Try again.";
				}
				else { break; }
			}
			
			currentPlayer->move(tgtX, tgtY); 
		}
		case 1 :
		{

		}
		case 2 :
			//currentPlayer->interact();
		case 3 :
			currentPlayer->endTurn();
		default:
			currentPlayer->endTurn();

	}
	
	
	local_PL[currentTurn].endTurn();

	
}