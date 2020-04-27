#include <iostream>
#include "Player.h"



Player::Player() = default;

Player::Player(vector<char> &pot){
    initTiles(pot);
}

void Player::initTiles(vector<char> &pot){
    unsigned short int index;

    for (int i = 0; i < 7; ++i) {
        index = rand()%pot.size();
        tiles[i] = pot[i];
        pot.erase(pot.begin() + i);
    }
}

unsigned short int Player::checkTiles(char letter){
    for (int i = 0; i < 7; ++i) {
        if (letter == tiles[i])
            return i;
    }
    return -1;
}

void Player::setTile(char letter, unsigned short int pos){
    tiles[pos] = letter;
}
