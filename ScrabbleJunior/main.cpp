#pragma comment(lib, "winmm.lib")

#define _WIN32_WINNT 0x0500

#include <iostream>
#include <vector>
#include <time.h>
#include <cstdlib>
#include <algorithm>
#include <windows.h>
#include <mmsystem.h>
//#include <mciapi.h>
#include <fstream>
#include "IO.h"
#include "Color.h"
#include "Game.h"
#include "Menu.h"
using namespace std;


int main() {
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r); //stores the console's current dimensions

    MoveWindow(console, r.left, r.top, 1400, 1100, TRUE);       // Setting window Size

    SetWindowLong(console, GWL_STYLE, GetWindowLong(console, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);   // Making window unresizable



//	PlaySound("Sound/back.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    srand(time(NULL));

    showTitle();

	while (1) {
        showOptions();
    }
 }
