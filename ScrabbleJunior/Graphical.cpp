//
// Created by morei on 5/12/2020.
//

#include "Graphical.h"


void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setColor(unsigned int color)
{
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon, color);
}


void setColor(unsigned int color, unsigned int background_color)
{
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hCon, color | background_color);
}

void replaceVisualChar(int x, int y, char letter, unsigned int fgColor, unsigned int bgColor){
    gotoxy(x, y);
    setColor(fgColor, bgColor);
    std::cout << letter;
    //  gotoxy(100, 100);
    setColor(WHITE, BLACK);
}

void cleanLine(int x, int y, int nChar){
    gotoxy(x, y);
    for (int i = 0; i < nChar; ++i) std::cout << ' ';
}


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


void placePlayer(Player &player){
    cleanLine(player.getX(), player.getY(), 40);
    gotoxy(player.getX(), player.getY());
    std::cout << player.getName() << "'s score: " << player.getScore();
    cleanLine(player.getX(), player.getY() + 1, 40);
    gotoxy(player.getX(), player.getY() + 1);
    std::cout << "This is your board: ";
    player.showTiles();
}