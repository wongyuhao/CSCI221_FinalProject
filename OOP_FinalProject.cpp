#include <iostream>
#include <fstream>
#include <cassert>
#include <random>
#include <ctime>

#define _WIN32_WINNT 0x0500
#include <windows.h>

#include "Building.h"
#include "Player.h"
#include "Display.h"
#include "DataFetcher.h"
#include "UI.h"

using namespace std;

void maximizeWindow()
{
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_SHOWMAXIMIZED);
}

int main() {
	maximizeWindow();
	
	cout << "Enter number of players: ";
	int playerCount = UI::readInt(2,10);
	
	DataFetcher::fetchPlayers(playerCount);
	DataFetcher::fetchItems();
	
	Display display;
	
	//first turn
	playerList[currentTurn].beginTurn();
	
	while (aliveCount > 1) {
		display.playerMenu();
		system("pause");
	}
	
	while(playerList[currentTurn].getHealthStat() <= 0) {
		currentTurn = (currentTurn + 1) % playerList.size();
	}
	
	cout << endl << string(10, '=') << " GAME END " << string(10, '=') << endl;
	cout << "Player " << playerList[currentTurn].getID() << " wins!" << endl;
}
