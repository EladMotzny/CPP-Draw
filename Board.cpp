#include <iostream>
#include "Square.h"
#include "Board.h"
#include "IllegalCharException.h"
#include <initializer_list>
#include <cassert>
#include <stdexcept>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include "BMPgenerator.h"

using namespace std;

Board::Board()
{
    // Board{4};
}

Board::Board(int n)
{
    //cout << "called c'tor" << endl;
    row = n;
    col = n;
    // cout << "in c'tor(int n)': " << " col is:" << col << endl;
    // cout << "in c'tor(int n)': " << " row is:" << row << endl;
    board = new Square *[col];
    for (int i = 0; i < col; i++)
    {
        // cout << "INIT: " <<i << endl;
        board[i] = new Square[row]; //new Square('.');
    }
    for (int i = 0; i < row; i++)
    {
        for (int j = 1; j < col; j++)
        {
            board[i][j].setContent('.');
        }
    }
}

Board::Board(const Board &other)
{
    
    // cout << "copy c'tor" << endl;
    row = other.row;
    col = other.col;
    board = new Square *[col];
    for (int i = 0; i < col; i++)
    {
        board[i] = new Square[row]; //new Square('.');
    }
    for (int i = 0; i < other.row; i++)
    {
        for (int j = 0; j < other.col; j++)
        {
            this->board[i][j] = other.board[i][j];
        }
    }
}

Board::~Board() //Destructor
{
    // cout << "D'tor" << endl;
    for (int i = 0; i < this->row; i++)
    {
        delete[] board[i];
    }
    //sagi hamudi
    delete[] board;
}

ostream &operator<<(ostream &out, Board &b)
{
    // cout << "in cout" << endl;
    for (int i = 0; i < b.getRow(); i++)
    {
        // cout << "PRINT: " << i;
        //out << "|";
        for (int j = 0; j < b.getCol(); j++)
        {
            // cout << j << endl;
            out << " " << b.board[i][j].getContent() << " |";
            // cout << b.board[i][j].getContent();
        }
        out << endl;
            //<< "________________" << endl;
    }
    return out;
}

Square &Board::operator[](initializer_list<int> coordinate)
{
    int *m_array = new int[2];
    copy(coordinate.begin(), coordinate.end(), m_array);
    if (sizeof(m_array) != sizeof(int) * 2 || m_array[0] > this->getRow() || m_array[1] > this->getCol())
        throw invalid_argument("Wrong cell input!");

    int x = m_array[0];
    int y = m_array[1];
    delete[] m_array;
    return this->board[x][y];
}

void Board::operator=(const char c)
{
    if (c == '.')
    {
        for (int i = 0; i < this->row; i++)
        {
            for (int j = 0; j < this->col; j++)
            {
                this->board[i][j] = c;
            }
        }
    }
    else
    {
        throw IllegalCharException(c);
    }
}

void Board::operator=(const Board &b)
{
    for (int i = 0; i < b.row; i++)
    {
        for (int j = 0; j < b.col; j++)
        {
            this->board[i][j] = b.board[i][j];
        }
    }
}

istream &operator>>(istream &is, Board &sqr)
{
    ///////////////////////////////////////
    cin.seekg (0, cin.end);
    // int length = cin.tellg();
    // cout << length << endl;
    // cin.seekg (0, cin.beg);
    // Board{(int)sqrt(length)}; //600
    // cout<< "at this point the board is gone" << endl;
    // cout << (int)sqrt(length) << endl;
    ////////////////////////////////////////////////////
    // cout << "in cin" << endl;
    string file;
    is.seekg(0, is.end);
    
    int length = is.tellg();
    sqr.row = (int)sqrt(length);
    sqr.col = (int)sqrt(length);
    //////try////
    sqr.board = new Square *[sqr.col];
    for (int i = 0; i < sqr.col; i++)
    {
        // cout << "INIT: " <<i << endl;
        sqr.board[i] = new Square[sqr.row]; //new Square('.');
    }
    for (int i = 0; i < sqr.row; i++)
    {
        for (int j = 1; j < sqr.col; j++)
        {
            sqr.board[i][j].setContent('.');
        }
    }
    ///////
    // cout << "in cin: " << " length is:" << length << endl;
    // cout << "in cin: " << " sqr.row is:" << sqr.getRow() << endl;
    // cout << "in cin: " << " sqr.col is:" << sqr.getCol() << endl;
    // cout << "in cin: " << " sqr.row is:" << length << endl;
    is.seekg(0, is.beg);
    int charCount = 0;
    int i = 0;

    is >> file;
    while (i < sqr.getRow())
    {
        for (int j = 0; j < file.length() && j < sqr.getCol(); j++)
        {
            if (file.at(j) != '\n')
                sqr.board[i][j] = file.at(j);
            charCount++;
        }
        charCount++;

        if (charCount >= length)
        {
            return is;
        }
        i++;
        is >> file;
    }
    return is;
}

string Board::draw(int n)
{ 
    int i, j;

    vector<vector<RGB_data>> buffer(n, vector<RGB_data>(n, {0xff, 0xff, 0xff}));

    int x = n - 35, y = 35;
    for (int i = 0; i < row; i++)
    {
        y = 35;
        for (int j = 0; j < col; j++)
        {
            if (board[i][j].getContent() == 'X')
            {
                drawX(buffer, x, y);
            }
            else if (board[i][j].getContent() == 'O')
            {
                drawO(buffer, x, y);
            }
            else if (board[i][j].getContent() == '.')
            {
                drawDot(buffer, x, y);
            }
            y = y + 35;
        }
        x = x - 35;
    }

    RGB_data a[n*n];

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            a[i*n+j] = buffer[i][j];
        }
    }

//     // std::chrono::high_resolution_clock::time_point t = std::chrono::high_resolution_clock::now();
//     // string time = t.time_since_epoch();
  time_t rawtime;
  struct tm * timeinfo;

  time (&rawtime);
  timeinfo = localtime (&rawtime);
  char t[80];
  strftime (t,80,"%F_%T",timeinfo); //HERE!!!!!!!!!!!!!!!!
  ///////////////////
   const std::clock_t start = std::clock() ;

    // const std::clock_t end = std::clock() ;

    const double elapsed_processor_time_millisecs = (start) * 1000.0 / CLOCKS_PER_SEC ;//end-

    cout << elapsed_processor_time_millisecs << endl;
 
    ostringstream ms;
    ms << elapsed_processor_time_millisecs;
    string str = ms.str();
    // double dbl = elapsed_processor_time_millisecs;
    const char *cstr = str.c_str();
  strcat(t,cstr);
  strcat(t,"_img.bmp");
  bmp_generator(t, n, n, (BYTE *)a);
  string s(t);
  return (s);
// return "End of DRAW";
}

