#include "color.h"
#include "IO.h"
#include <string>



/**
 * Function to put the program on hold
 */
void waitForKey() {
    std::cout <<"Press any key to continue...";
    std::cin.get();
}

/**
 * Function to convert a string into a lowered case one
 *
 * @param str - original string
 * @return - converted string
 */
std::string stringToLower(std::string str) {
    std::string::iterator it;
    std::string newCopy = str;

    for (it = newCopy.begin(); it != newCopy.end(); it++) {
        (*it) = tolower((*it));
    }

    return newCopy;
}

void errorMsg(std::string text, short int x, short int y){
    gotoxy(x,y);
    setColor(ConsoleColors::RedFore, ConsoleColors::SilverBack);
    std::cout << text;
    setColor(ConsoleColors::WhiteFore, ConsoleColors::BlackBack);
}


void printMsg(std::string text, short int x, short int y){
    gotoxy(x, y);
    std::cout << text;
}
void printMsg(std::string text, ConsoleColors color){
    setColor(color);
    std::cout << text;
    setColor(ConsoleColors::WhiteFore);
}
void printMsg(std::string text, short int x, short int y, ConsoleColors color){
    gotoxy(x, y);
    setColor(color);
    std::cout << text;
    setColor(ConsoleColors::WhiteFore);
}
void printMsg(std::string text, ConsoleColors color, ConsoleColors backColor){
    setColor(color, backColor);
    std::cout << text;
    setColor(ConsoleColors::WhiteFore, ConsoleColors::BlackBack);
}

void printMsg(std::string text, short int x, short int y, ConsoleColors color, ConsoleColors backColor){
    gotoxy(x, y);
    setColor(color, backColor);
    std::cout << text;
    setColor(ConsoleColors::WhiteFore, ConsoleColors::BlackBack);
}