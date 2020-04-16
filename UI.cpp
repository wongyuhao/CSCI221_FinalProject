#include "UI.h"

string UI::readInput(const string &prompt) {
	if(!prompt.empty()) cout << prompt << endl;
	
	string input;
	while(input.empty()) getline(cin, input);
	return input;
}

int UI::toInt(const string &s) {
	int sign = 1;
	int ans = 0;
	
	for(int i = 0; i < s.length(); i++) {
		ans *= 10;
		
		if(i==0 && s[i]=='-') {
			sign = -1;
			continue;
		}
		
		if(!isdigit(s[i])) return -INF;
		if(ans*10LL > INT_MAX) return -INF;
		
		ans += s[i]-'0';
	}
	
	return sign*ans;
}

int UI::readInt(const int L, const int R) {
	string input = readInput();
	int res = toInt(input);
	
	while(res < L || res > R) {
		cout << "Invalid input. Please enter a number within the interval [" << L << ", " << R << "]." << endl;
		input = readInput();
		res = toInt(input);
	}
	
	return res;
}

char UI::readChar(){
	string input = readInput();
	while(input.length() != 1 || !isalpha(input[0])) {
		cout << "Invalid input. Please enter an alphabet: " << endl;
		input = readInput();
	}
	
	return input[0];
}

bool UI::promptYN(const string &prompt) {
	cout << prompt << " (Y/N)" << endl;
	
	string input = readInput();
	
	while(input.length() != 1 || (tolower(input[0]) != 'y' && tolower(input[0]) != 'n')){
		cout << "Invalid response. Please try again. (Y/N)" << endl;
		input = readInput();
	}
	
	return (tolower(input[0]) == 'y');
}
