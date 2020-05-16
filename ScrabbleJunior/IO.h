#pragma once
#include<iostream>
#include <limits>
#include <iostream>
#include <windows.h>
#include<string>
#include "Player.h"
#include "Graphical.h"



/**
 * Function that prompts the user for input.
 * Checks if input is valid, allows only input without spaces and in the correct type.
 * Doesn't allow for the EOF character to be input, allowing for input to continue.
 *
 * @tparam T the type of data to be input
 * @param[out] input The variable where the input is stored.
 * @param[in] delimiter The last char must be at the end of the buffer
 *
 * @returns a boolean that indicates if a value was input successfully.
 */
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

/**
 * Function that prompts the user for input.
 * Checks if input is valid, allows only input without spaces and in the correct type.
 * Ignores the EOF character, allowing it to be input.
 *
 * @tparam T the type of data to be input
 * @param[out] input The variable where the input is stored.
 * @param[in] delimiter The last char must be at the end of the buffer
 *
 * @returns a short int if he gave a valid input(1), eof (2) or invalid(0)
 */
template <typename T>
unsigned short int checkInputOrSTOP(T& input, char delimiter = '\n') {
    std::cin >> input;

    if (std::cin.eof()) {
        return 2;
    }
    else if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        return 0;
    }
    else if (std::cin.peek() != delimiter) {
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        return 0;
    }

    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

    return 1;
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