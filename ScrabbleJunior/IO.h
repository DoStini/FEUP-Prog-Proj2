#pragma once
#include<iostream>
#include <limits>
#include <iostream>
#include <windows.h>
#include<string>

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
void getChar(char& input);
void printMessage(std::string message, std::string end = "\n");
void printMessage(std::string message, int bgColor, int fgColor, std::string end = "\n");
bool checkStop();
void clearScreen(short xPos, short yPos);
void waitForKey();
std::string stringToLower(std::string str);
std::string stringToUpper(std::string str);
void setColor(unsigned int color);
void setColor(unsigned int color, unsigned int background_color);
void gotoxy(int x, int y);
void replaceVisualChar(int x, int y, char letter, unsigned int fgColor, unsigned int bgColor);