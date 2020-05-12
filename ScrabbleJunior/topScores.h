//
// Created by morei on 5/12/2020.
//

#ifndef SCRABBLEJUNIOR_TOPSCORES_H
#define SCRABBLEJUNIOR_TOPSCORES_H

#include <iostream>
#include <fstream>
#include "Player.h"


typedef struct Winner{
    char name[20] = "";
    int score = 0;
} Winner;


std::vector<Winner> readScores(std::string fileName);
void checkScores(std::vector<Winner> &winners, std::string fileName);
void writeScores(std::vector<Winner> &players, std::string fileName, bool firstTime = false);
#endif //SCRABBLEJUNIOR_TOPSCORES_H
