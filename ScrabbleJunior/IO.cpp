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

void waitForKey(short int x, short int y) {
    gotoxy(x, y);
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

/**
 * Shows a error message on the console
 *
 * @param text - Error message
 * @param x - X Position
 * @param y - Y Position
 */
void errorMsg(std::string text, short int x, short int y){
    gotoxy(x,y);
    setColor(ConsoleColors::RedFore);
    std::cout << text;
    setColor(ConsoleColors::WhiteFore);
}

/**
 * Clears the screen and prints in that position
 *
 * @param text - Message
 * @param x - X Position
 * @param y - Y Position
 */
void clearAndPrint(std::string text, short int x, short int y){
    clearScreen(x,y);
    std::cout << text;
}

/**
 * Print a message in the specified position
 *
 * @param text - Message
 * @param x - X Position
 * @param y - Y Position
 */
void printMsg(std::string text, short int x, short int y){
    gotoxy(x, y);
    std::cout << text;
}

/**
 * Print a simple message
 *
 * @param text
 */
void printMsg(std::string text){
    std::cout << text;
}

/**
 * Print a message with color
 *
 * @param text - Message
 * @param color - Color from ConsoleColors
 */
void printMsg(std::string text, ConsoleColors color){
    setColor(color);
    std::cout << text;
    setColor(ConsoleColors::WhiteFore);
}

/**
 * Prints a message in a specified position with color
 *
 * @param text - Message
 * @param x - X Position
 * @param y - Y position
 * @param color - Color from ConsoleColors
 */
void printMsg(std::string text, short int x, short int y, ConsoleColors color){
    gotoxy(x, y);
    setColor(color);
    std::cout << text;
    setColor(ConsoleColors::WhiteFore);
}

/**
 * Prints a message with a color and background color
 *
 * @param text - Message
 * @param color - Color
 * @param backColor - Background color
 */
void printMsg(std::string text, ConsoleColors color, ConsoleColors backColor){
    setColor(color, backColor);
    std::cout << text;
    setColor(ConsoleColors::WhiteFore, ConsoleColors::BlackBack);
}

/**
 * Prints a messa with color and background color in a specified position
 *
 * @param text - Message
 * @param x - X Position
 * @param y - Y Position
 * @param color - Color
 * @param backColor - Background color
 */
void printMsg(std::string text, short int x, short int y, ConsoleColors color, ConsoleColors backColor){
    gotoxy(x, y);
    setColor(color, backColor);
    std::cout << text;
    setColor(ConsoleColors::WhiteFore, ConsoleColors::BlackBack);
}