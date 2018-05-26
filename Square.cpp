using namespace std;
#include "Square.h"
#include "IllegalCharException.h"

Square::Square(){
    // cout << "Square default c-tor"<< endl;
     content = '.';  // initialize array to all .
} 
 
Square::~Square(){}

Square::Square(char c){
     content = c;  // initialize array to all c (X or O)
}

void Square::operator=(const char c){
    if(c=='.' || c=='X' || c=='O')
        this->content = c;
    else
        throw  IllegalCharException(c);
} 