#include "Board.h"
#include "Square.cpp"
#include "Board.cpp"
#include "IllegalCharException.h"


#include <iostream>
#include <string>
using namespace std;

int main() {
	cin.seekg (0, cin.end);//not in main
    int length = cin.tellg();//not in main
    cin.seekg (0, cin.beg);//not in main
	Board board{(int)sqrt(length)};//not in main (the sqrt)
	cin >> board;
	string filename = board.draw(600);
	cout << filename << endl;
}