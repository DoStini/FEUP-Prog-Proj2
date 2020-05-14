//
// Created by morei on 5/12/2020.
//

#ifndef SCRABBLEJUNIOR_GRAPHICAL_H
#define SCRABBLEJUNIOR_GRAPHICAL_H

#include "Player.h"
#include <windows.h>
#include "Color.h"

#define YBEG 25
#define XSPACING 2
#define YSPACING 1
#define XBEGMENU 70
#define YBEGMENU 13

void gotoxy(int x, int y);
void replaceVisualChar(int x, int y, char letter, unsigned int fgColor, unsigned int bgColor);
void clearScreen(short xPos = 0, short yPos = 0);
void cleanLine(int x, int y, int nChar);
void placePlayer(Player &player);
void setColor(unsigned int color);
void setColor(unsigned int color, unsigned int background_color);


#endif //SCRABBLEJUNIOR_GRAPHICAL_H
