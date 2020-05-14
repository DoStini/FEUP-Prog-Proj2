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
#include "Graphical.h"

class Board {
public:
    Board();
    Board(std::string fileName);
    ~Board();                                   // Using malloc for array of char

    void readBoard(std::string fileName);
    void showBoard();
    Word *findWord(unsigned short int index, unsigned short int charPos, bool vertical);
    void initArray();
    void writeOnArray(std::string word, bool vertical, unsigned short int vIdx, unsigned short int hIdx);
    void initWordVectors();
    char getTile(unsigned short int *pos);
    unsigned short int getHSize();
    unsigned short int getVSize();


    bool analyseMoves(Player &player);

    unsigned short int getStart();          // Graphical function«
private:
    std::vector<std::vector<Word>> hWords;
    std::vector<std::vector<Word>> vWords;
    unsigned short int hSize;
    unsigned short int vSize;
    char **letters;

    unsigned short int start;
};


#endif //SCRABBLEJUNIOR_BOARD_H
