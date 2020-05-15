#ifndef SCRABBLEJUNIOR_PLAYER_H
#define SCRABBLEJUNIOR_PLAYER_H

#include <iostream>
#include <string>
#include <vector>
#include "Color.h"


class Player{
public:
    Player();
    Player(std::vector<char> &pot, std::string name, std::vector<int> pos, ConsoleColors color);
    short int checkTiles(char letter);
    void initTiles(std::vector<char> &pot);
    void showTiles();
    void addTile(char letter);
    void removeTile(char letter);
    void addPoints(unsigned short int);
    unsigned short int getScore();
    std::string getName();
    void setName(std::string name);
    ///Graphical functions
    int getX();
    int getY();
    void setX(int val);
    void setY(int val);
    void setColor(ConsoleColors color);
    ConsoleColors getColor();
private:
    std::pair<int, int> pos;
    ConsoleColors color;
    std::vector<char> tiles;
    unsigned short int score = 0;
    std::string name = "";
};

#endif
