#include "DisplayDriver.h"

vector <class Building> DisplayDriver::local_BL;
vector <class Player> DisplayDriver::local_PL;

char DisplayDriver::map[MAPSIZE][MAPSIZE*2];

void DisplayDriver::printMap() const {
	cout << "Printing Map..." << endl;
	for (int row = 0; row < MAPSIZE ; row++) {
		for (int col = 0; col < MAPSIZE*2; col++) {
			cout<< map[row][col];
		}
		cout << endl;
	}
	cout << "Printing Complete!" << endl;
}

void DisplayDriver::initMap() {

	cout << "Initializing map..." << endl;

	

	for (int row = 0; row < MAPSIZE; row++) {
		for (int col = 0; col < MAPSIZE*2; col++) {
			map[row][col] = ' ';
		}
	}



	for (int row = 0; row < MAPSIZE; row++) {

		if (row == 0 || row == MAPSIZE-1) { //print borders

			for (int col = 0; col < MAPSIZE*2; col++) {
				map[row][col] = '#';//print borders
			}

		}
		else {  
			for (int col = 0; col < MAPSIZE*2; col++) {
				if (col == 0 || col == MAPSIZE*2 - 1) {
					map[row][col] = '#';//print borders
				}
				else {

					//populate buildings
					for (int i = 0; i < local_BL.size(); i++) {
						map[local_BL[i].getPosY()][local_BL[i].getPosX()] = local_BL[i].getID();
					}

					//populate players
					for (int i = 0; i < local_PL.size(); i++) {
						if (map[local_PL[i].getPosY()][local_PL[i].getPosX()] == ' ') {
							map[local_PL[i].getPosY()][local_PL[i].getPosX()] = local_PL[i].getID();
						}
						else {
							int move = local_PL[i].getPosX();
							local_PL[i].setPosX(move++);
							map[local_PL[i].getPosY()][local_PL[i].getPosX()] = local_PL[i].getID();

						}
					}
				}


				
			}

		}

	}
	cout << "Initialization Complete!" << endl;

}

void DisplayDriver::playerMenu() {
	cout << "Player " << local_PL[currentTurn].getID()<< "'s Turn:" << endl;
	/*
	
	Menu of actions here
	
	*/
	
	local_PL[currentTurn].endTurn();

	
}