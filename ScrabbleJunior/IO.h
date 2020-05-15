#pragma once
#include<iostream>
#include <limits>
#include <iostream>
#include <windows.h>
#include<string>
#include "Player.h"
#include "Graphical.h"




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




void waitForKey();
void waitForKey(short int x, short int y);
std::string stringToLower(std::string str);
void errorMsg(std::string text, short int x, short int y);
void clearAndPrint(std::string text, short int x, short int y);
void printMsg(std::string text);
void printMsg(std::string text, short int x, short int y);
void printMsg(std::string text, ConsoleColors color);
void printMsg(std::string text, short int x, short int y, ConsoleColors color);
void printMsg(std::string text, ConsoleColors color, ConsoleColors backColor);
void printMsg(std::string text, short int x, short int y, ConsoleColors color, ConsoleColors backColor);