//
// Created by morei on 5/12/2020.
//

#ifndef SCRABBLEJUNIOR_GRAPHICAL_H
#define SCRABBLEJUNIOR_GRAPHICAL_H

#include "Player.h"
#include <windows.h>
#include "Color.h"

void gotoxy(int x, int y);
void replaceVisualChar(int x, int y, char letter, unsigned int fgColor, unsigned int bgColor);
void cleanLine(int x, int y, int nChar);
void placePlayer(Player &player);
void setColor(unsigned int color);
void setColor(unsigned int color, unsigned int background_color);


#endif //SCRABBLEJUNIOR_GRAPHICAL_H
