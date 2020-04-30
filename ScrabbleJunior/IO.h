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


#define BLACK2 0
#define BLUEtooth 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGRAY 7
#define DARKGRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14




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
