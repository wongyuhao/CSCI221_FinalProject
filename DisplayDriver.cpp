#include "DisplayDriver.h"

void DisplayDriver::printMap()
{
	for (int row = 0; row < ROWSIZE; row++) {

		if (row == 0 || row == ROWSIZE - 1) {
			for (int col = 0; col < COLSIZE; col++) {
				if (col == 0 || col == COLSIZE - 1) {
					cout << "@";
				}
				else { cout << "#"; }
			}
			cout << endl;
		}
		else {
			for (int col = 0; col < COLSIZE; col++) {
				if (col == 0 || col == COLSIZE - 1) {
					cout << "#";
				}
				else { cout << " "; }
			}
			cout << endl;
		}
		
	}
}
