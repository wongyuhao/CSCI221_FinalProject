#ifndef DATAFETCHER_H
#define DATAFETCHER_H

#include <fstream>
#include <cassert>

#include "Display.h" //player list
#include "Resource.h" //item list

using namespace std;

/* This file fetches items from Items.txt and appends players to playerList */

class DataFetcher {
private:
	const int INF = int(1e9);
	
public:
	static void fetchPlayers(const int playerCount); //append [playerCount] players to playerList (in Display.h)
	static void fetchItems(); //fetch items from Items.txt and append items to itemList (in Resource.h)
};

#endif
