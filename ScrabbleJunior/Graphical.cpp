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
    if (background_color == BLACK)
        SetConsoleTextAttribute(hCon, color);
    else
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

void placePlayer(Player &player){
    cleanLine(player.getX(), player.getY(), 40);
    gotoxy(player.getX(), player.getY());
    std::cout << player.getName() << "'s score: " << player.getScore();
    cleanLine(player.getX(), player.getY() + 1, 40);
    gotoxy(player.getX(), player.getY() + 1);
    std::cout << "This is your board: ";
    player.showTiles();
}