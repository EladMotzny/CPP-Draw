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
#include "BMPgenerator.h"

using namespace std;

Board::Board()
{
    Board{4};
}

Board::Board(int n)
{
    //cout << "called c'tor" << endl;
    row = n;
    col = n;
    board = new Square *[col];
    for (int i = 0; i < col; i++)
    {
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
    //cout << "copy c'tor" << endl;
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
    for (int i = 0; i < this->row; i++)
    {
        delete[] board[i];
    }
    //sagi hamudi
    delete[] board;
}

ostream &operator<<(ostream &out, Board &b)
{
    for (int i = 0; i < b.getRow(); i++)
    {
        //out << "|";
        for (int j = 0; j < b.getCol(); j++)
        {
            out << " " << b.board[i][j].getContent() << " |";
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

//this is how we insert the file name, exception comes here
istream &operator>>(istream &is, Board &sqr)
{
    string file;
    is.seekg(0, is.end);//'is' is the file name, exception goes here
    int length = is.tellg();
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

    // std::chrono::high_resolution_clock::time_point t = std::chrono::high_resolution_clock::now();
    // string time = t.time_since_epoch();
    
  time_t rawtime;
  struct tm * timeinfo;

  time (&rawtime);
  timeinfo = localtime (&rawtime);
  char* t;
  strftime (t,80,"%F_%T",timeinfo);
  strcat(t,"_img.bmp");
  cout << t << endl;
  bmp_generator(t, n, n, (BYTE *)a);

return (EXIT_SUCCESS);//need to return the name of the file which is in t so we need to return that (cast t to string and return it)
}

