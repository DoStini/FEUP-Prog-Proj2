#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>
#include "IO.h"
#include "Game.h"
using namespace std;



void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void clrscr(void)
{
    COORD coordScreen = { 0, 0 }; // upper left corner
    DWORD cCharsWritten;
    DWORD dwConSize;
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hCon, &csbi);
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    // fill with spaces
    FillConsoleOutputCharacter(hCon, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
    GetConsoleScreenBufferInfo(hCon, &csbi);
    FillConsoleOutputAttribute(hCon, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
    // cursor to upper left corner
    SetConsoleCursorPosition(hCon, coordScreen);
}
// STILL HAVE TO FIND OUT WHY CANT FREE LETTERS**


int main() {

    vector<int> viktor = {1,2,4,4,3};
    cout << std::find(viktor.begin(), viktor.end(), 3) - viktor.begin();

    //srand(0);
    //Board board("board.txt");
    //clrscr();
    //Game game(1, &board);
}



