#include "Board.h"
#include "Square.cpp"
#include "Board.cpp"
#include "IllegalCharException.h"


#include <iostream>
#include <string>
using namespace std;

int main() {
	// cin.seekg (0, cin.end);
    // int length = cin.tellg();
    // cin.seekg (0, cin.beg);
	// Board board{(int)sqrt(length)}; 
	Board board;
	cin >> board;
	cout << board;
	string filename = board.draw(600);
	cout << filename << endl;
}