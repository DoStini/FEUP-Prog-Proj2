//
// Created by morei on 4/25/2020.
//

#ifndef SCRABBLEJUNIOR_BOARD_H
#define SCRABBLEJUNIOR_BOARD_H

#include <iostream>
#include "Word.h"

using std::string;
using std::vector;

class Board {
public:
    Board();
    Board(string fileName);
    ~Board();                                   // Using malloc for array of char

    void readBoard(string fileName);
    void showBoard();
    void initArray();
    void writeOnArray(string word, bool vertical, unsigned short int vIdx, unsigned short int hIdx);
    void initWordVectors();
    char getTile(unsigned short int *pos);
    unsigned short int getHSize();
    unsigned short int getVSize();
private:
    vector<vector<Word>> hWords;
    vector<vector<Word>> vWords;
    unsigned short int hSize;
    unsigned short int vSize;
    char **letters;
};


#endif //SCRABBLEJUNIOR_BOARD_H
