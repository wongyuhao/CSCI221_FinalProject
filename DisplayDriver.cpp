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



void DisplayDriver::initMap(vector<class Player> playerList) {

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
		else {  //print map
			for (int col = 0; col < MAPSIZE*2; col++) {
				if (col == 0 || col == MAPSIZE*2 - 1) {
					map[row][col] = '#';//print borders
				}else{
					for (int i = 0; i < playerList.size(); i++) {
						if (playerList[i].getPosX() == col && playerList[i].getPosY() == row){
							map[row][col] = playerList[i].getID();
						}
					}


				}
			}

		}

	}
	cout << "Initialization Complete!" << endl;

}