#include <iostream>
#pragma once
using namespace std;

class Square{
        char content;
        public:
            Square(char c);
            Square();
            ~Square();
            void operator=(const char c);
            char getContent(){
                return this->content;
            }
            void setContent(char c){
                this->content = c;
            }
};