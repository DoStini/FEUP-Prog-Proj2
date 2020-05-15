//
// Created by morei on 5/12/2020.
//

#include "Graphical.h"


/**
 * Function to put console cursor in a specified position
 *
 * @param x - X position
 * @param y - Y position
 */
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

/**
 * Set the color to be used with cout
 *
 * @param color
 */

void setColor(unsigned int color)
{
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon, color);
}


/**
 * Set color and background color to be used with cout
 *
 * @param color
 * @param background_color
 */
void setColor(unsigned int color, unsigned int background_color)
{
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hCon, color | background_color);
}

/**
 * Function to replace a character in a certain console position by another one
 *
 * @param x - X position to be replaced
 * @param y - Y position to be replaced
 * @param letter - Letter to replace
 * @param fgColor
 * @param bgColor
 */
void replaceVisualChar(int x, int y, char letter, unsigned int fgColor, unsigned int bgColor){
    gotoxy(x, y);
    setColor(fgColor, bgColor);
    std::cout << letter;
    //  gotoxy(100, 100);
    setColor(ConsoleColors::WhiteFore, ConsoleColors::BlackBack);

}

/**
 * Cleaning line with nChar spaces
 *
 * @param x - X position
 * @param y - Y position
 * @param nChar - Number of characters to clean
 */
void cleanLine(int x, int y, int nChar){
    gotoxy(x, y);
    for (int i = 0; i < nChar; ++i) std::cout << ' ';
}


/**
 * Clear screen from a specified position to the end
 *
 * @param xPos
 * @param yPos
 */
void clearScreen(short xPos, short yPos) {
    COORD coordScreen = { xPos, yPos }; // upper left corner
    DWORD cCharsWritten;
    DWORD dwConSize;
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hCon, &csbi);
    dwConSize = (csbi.dwSize.X - xPos) * (csbi.dwSize.Y - yPos);
    // fill with spaces
    FillConsoleOutputCharacter(hCon, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
    GetConsoleScreenBufferInfo(hCon, &csbi);
    FillConsoleOutputAttribute(hCon, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
    // cursor to upper left corner
    SetConsoleCursorPosition(hCon, coordScreen);
}

/**
 * Function to place player's name, score and board on the console, according to predefined positions
 *
 * @param player
 */
void placePlayer(Player &player){
    cleanLine(player.getX(), player.getY(), 40);
    printMsg(player.getName() + "'s ", player.getX(), player.getY(), player.getColor());
    printMsg("score: " + std::to_string(player.getScore()));

    cleanLine(player.getX(), player.getY() + 1, 40);
    printMsg("This is your board: ", player.getX(), player.getY() + 1);

    setColor(ConsoleColors::OliveFore);
    player.showTiles();
    setColor(ConsoleColors::WhiteFore);
}