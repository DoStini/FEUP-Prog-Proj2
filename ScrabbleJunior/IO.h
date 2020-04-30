//
// Created by morei on 4/27/2020.
//

#ifndef SCRABBLEJUNIOR_IO_H
#define SCRABBLEJUNIOR_IO_H

#include<iostream>
#include<string>
#include <limits>
#include <ctime>
#include <cstdlib>
#include <windows.h>

using namespace std;


//==========================================================================================
// Position the cursor at column 'x', line 'y'
// The coodinates of upper left corner of the screen are (x,y)=(0,0)


template <typename T>
bool checkInput(T& input, char delimiter = '\n') {
    std::cin >> input;

    if (std::cin.eof()) {
        std::cin.clear();
        return false;
    }
    else if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        return false;
    }
    else if (std::cin.peek() != delimiter) {
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        return false;
    }

    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

    return true;
}

template <typename T>
bool checkInputOrSTOP(T& input, char delimiter = '\n') {
    std::cin >> input;

    if (std::cin.eof()) {
        return true;
    }
    else if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        return false;
    }
    else if (std::cin.peek() != delimiter) {
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        return false;
    }

    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

    return true;
}

void getString(std::string& string);
void printMessage(std::string message, std::string end = "\n");
void printMessage(std::string message, int bgColor, int fgColor, std::string end = "\n");
bool checkStop();
void clearScreen();
void waitForKey();


#endif //SCRABBLEJUNIOR_IO_H
