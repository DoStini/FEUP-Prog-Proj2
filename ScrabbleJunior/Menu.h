//
// Created by morei on 5/5/2020.
//

#ifndef SCRABBLEJUNIOR_MENU_H
#define SCRABBLEJUNIOR_MENU_H

#include <windows.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include "IO.h"
#include "Player.h"
#include "Game.h"
#include "Board.h"
#include "TopScores.h"



void showTitle();
void showCascading(std::string s, time_t t, unsigned short int xStart, unsigned short int yStart);
void showOptions();
void startGame(unsigned short int numPlayers, std::vector<std::string> playerNames, std::string fileName);
#endif //SCRABBLEJUNIOR_MENU_H
