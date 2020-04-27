//
// Created by morei on 4/25/2020.
//

#ifndef SCRABBLEJUNIOR_BOARD_H
#define SCRABBLEJUNIOR_BOARD_H

#include <iostream>
#include "Word.h"

using std::string, std::vector;

class Board {
public:
    Board();
    Board(string fileName);
    ~Board();                                   // Using malloc for array of char

    void readBoard(string fileName);
    void initArray();
    void writeOnArray(string word, bool vertical, unsigned short int vIdx, unsigned short int hIdx);
    void initWordVectors();
    char readLetter(unsigned short int pos[2]);
    void showBoard();
private:
    vector<vector<Word>> hWords;
    vector<vector<Word>> vWords;
    unsigned short int hSize;
    unsigned short int vSize;
    char **letters;
};


#endif //SCRABBLEJUNIOR_BOARD_H
