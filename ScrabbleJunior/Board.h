//
// Created by morei on 4/25/2020.
//

#ifndef SCRABBLEJUNIOR_BOARD_H
#define SCRABBLEJUNIOR_BOARD_H

#include <iostream>

#include "Player.h"
#include "Word.h"
#include "IO.h"
#include "Color.h"

using std::string;
using std::vector;

class Board {
public:
    Board();
    Board(string fileName);
    ~Board();                                   // Using malloc for array of char

    void readBoard(string fileName);
    void showBoard();
    Word *findWord(unsigned short int index, unsigned short int charPos, bool vertical);
    void initArray();
    void writeOnArray(string word, bool vertical, unsigned short int vIdx, unsigned short int hIdx);
    void initWordVectors();
    char getTile(unsigned short int *pos);
    unsigned short int getHSize();
    unsigned short int getVSize();

    bool analyseMoves(Player &player);

    void setTempBoard(unsigned short int pos[2]);
private:
    vector<vector<Word>> hWords;
    vector<vector<Word>> vWords;
    unsigned short int hSize;
    unsigned short int vSize;
    char **letters;

    bool ** tempBoard;
};


#endif //SCRABBLEJUNIOR_BOARD_H
