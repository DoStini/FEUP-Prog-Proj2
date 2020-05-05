#include <iostream>
#include <vector>
#include <time.h>
#include <cstdlib>
#include <algorithm>
#include <windows.h>
#include "IO.h"
#include "Color.h"
#include "Game.h"
#include "Menu.h"
using namespace std;


int main() {
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r); //stores the console's current dimensions

    MoveWindow(console, r.left, r.top, 1400, 900, TRUE);


    //vector<int> viktor = {1,2,4,4,3};
    //cout << std::find(viktor.begin(), viktor.end(), 3) - viktor.begin();

/*
    srand(0);
    Board board("board2.txt");
    Game game(1, &board);
    waitForKey();
*/

    showTitle();
    showOptions();
    waitForKey();
 }
