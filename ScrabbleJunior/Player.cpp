#include <iostream>
#include "Player.h"



void Player::initTiles(Board &board){

    unsigned short int index = rand()&board.;

    for (int i = 0; i < 7; ++i) {

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
