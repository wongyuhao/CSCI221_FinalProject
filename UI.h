#ifndef UI_H
#define UI_H

#include <iostream>
using namespace std;

class UI {
private:
	static const int INF = int(1e9);
	
public:
	static string readInput(const string &prompt = ""); //prints the prompt and reads a string on a line
	
	static int toInt(const string &s); //converts string to int
	static int readInt(const int L, const int R); //reads a number within [L,R] (inclusive)
	static char readChar(); //reads a character
	
	static bool promptYN(const string &s); //prompts the user for Y/N
};

#endif
