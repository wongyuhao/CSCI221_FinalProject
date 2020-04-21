#include <iostream>
#include <fstream>
#include <cassert>
#include <random>
#include <ctime>

#define _WIN32_WINNT 0x0500
#include <windows.h>

#include "Player.h"
#include "Display.h"
#include "DataFetcher.h"
#include "UI.h"
#include "Config.h"

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
	
	//fetch players and items
	DataFetcher::fetchPlayers(playerCount);
	DataFetcher::fetchItems();
	
	Display display;
	
	//first turn
	playerList[currentTurn].beginTurn();
	
	//display menu while game doesn't end
	while(roundCounter <= ROUND_LIMIT && aliveCount > 1) {
		display.playerMenu();
		if(roundCounter <= ROUND_LIMIT) system("pause");
	}
	
	//game ends
	system("cls");
	display.printMap();
	
	cout << endl << string(10, '=') << " GAME END " << string(10, '=') << endl;
	vector<const Player*> leaderboard = display.printLeaderboard();	
	cout << "Player " << leaderboard[0]->getID() << " wins!" << endl << endl;
	
	UI::promptYN("End game?");
}
