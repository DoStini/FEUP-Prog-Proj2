#pragma once
#include<iostream>
#include <limits>
#include <iostream>
#include <windows.h>
#include<string>
#include "Player.h"
#include "Graphical.h"

#define YBEG 25
#define XSPACING 2  // For calculations use this value
#define YSPACING 1    // For showBoard use each - 1
#define XBEGMENU 70
#define YBEGMENU 13


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


void waitForKey();
std::string stringToLower(std::string str);
std::string stringToUpper(std::string str);
