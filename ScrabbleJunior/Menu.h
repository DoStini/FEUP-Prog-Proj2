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


void showTitle();
void showCascading(std::string s, time_t t, unsigned short int xStart, unsigned short int yStart);
void showOptions();


#endif //SCRABBLEJUNIOR_MENU_H
