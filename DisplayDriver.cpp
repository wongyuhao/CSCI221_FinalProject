#include "DisplayDriver.h"

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



void DisplayDriver::initMap(vector<class Building> buildingList,vector<class Player> playerList) {

	cout << "Initializing map..." << endl;

	

	for (int row = 0; row < MAPSIZE; row++) {
		for (int col = 0; col < MAPSIZE*2; col++) {
			map[row][col] = ' ';
		}
	}



	for (int row = 0; row < MAPSIZE; row++) {

		if (row == 0 || row == MAPSIZE-1) { //print borders

			for (int col = 0; col < MAPSIZE*2; col++) {
				if (col == 0 || col == MAPSIZE*2 - 1) {
					map[row][col] = '@';	//print borders
				}
				else { map[row][col] = '#'; }//print borders
			}

		}
		else {  
			for (int col = 0; col < MAPSIZE*2; col++) {
				if (col == 0 || col == MAPSIZE*2 - 1) {
					map[row][col] = '#';//print borders
				}
				else {

					//populate buildings
					for (int i = 0; i < buildingList.size(); i++) {
						map[buildingList[i].getPosY()][buildingList[i].getPosX()] = buildingList[i].getID();
					}

					//populate players
					for (int i = 0; i < playerList.size(); i++) {
						if (map[playerList[i].getPosY()][playerList[i].getPosX()] == ' ') {
							map[playerList[i].getPosY()][playerList[i].getPosX()] = playerList[i].getID();
						}
						else {
							int move = playerList[i].getPosX();
							playerList[i].setPosX(move++);
							map[playerList[i].getPosY()][playerList[i].getPosX()] = playerList[i].getID();

						}
					}
				}


				
			}

		}

	}
	cout << "Initialization Complete!" << endl;

}