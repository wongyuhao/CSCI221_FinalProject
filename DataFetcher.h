#ifndef DATAFETCHER_H
#define DATAFETCHER_H

#include <fstream>
#include <cassert>

#include "Display.h" //player list
#include "Resource.h" //item list

using namespace std;

class DataFetcher {
private:
	const int INF = int(1e9);
	
public:
	static void fetchPlayers(const int playerCount);
	static void fetchItems();
};

#endif
