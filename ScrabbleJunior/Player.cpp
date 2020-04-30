#include <iostream>
#include <algorithm>
#include "Player.h"


Player::Player() = default;

Player::Player(vector<char> &pot){
    initTiles(pot);
}

void Player::initTiles(vector<char> &pot){
    unsigned short int index;

    for (int i = 0; i < 7; ++i) {
        index = rand()%pot.size();
        tiles.push_back(pot[i]);
        pot.erase(pot.begin() + i);
    }
}

void Player::showTiles() {
    for (int i = 0; i < 7; ++i) {
        std::cout << tiles[i] << ' ';
    }
    std::cout << std::endl;
}

unsigned short int Player::checkTiles(char letter){
    vector<char>::iterator it = std::find(tiles.begin(), tiles.end(), letter);
    return it != tiles.end() ? it-tiles.begin() : -1;

    for (int i = 0; i < 7; ++i) {
        if (letter == tiles[i])
            return i;
    }
    return -1;
}

void Player::addTile(char letter){
    tiles.push_back(letter);
}
void Player::removeTile(char letter){
    tiles.erase(std::find(tiles.begin(), tiles.end(), letter));
}

void Player::addPoints(unsigned short int points){
    score += points;
}
