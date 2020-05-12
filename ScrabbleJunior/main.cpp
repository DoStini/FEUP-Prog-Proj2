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
#include "topScores.h"

using namespace std;


int man(){
    Winner p1; strncpy(p1.name, "Homailot", sizeof(p1.name)); p1.score = 35;

    vector<Winner> players = {p1};
    checkScores(players, "scoreboard.win");
    players = readScores("scoreboard.win");

    for (int i = 0; i < players.size(); ++i) {
        cout << i << " " << players[i].name << " " << players[i].score << endl;
    }
    return 0;
}

int mai3n(){


    Winner p1; strncpy(p1.name, "Andre", sizeof(p1.name)); p1.score = 20;
    Winner p2; strncpy(p2.name, "Nunio", sizeof(p2.name)); p1.score = 10;
    Winner p3; strncpy(p3.name, "LOOOL", sizeof(p3.name)); p1.score = 5;

    vector<Winner> players = {p1,p2,p3};
    players = readScores("whatever.win");
    checkScores(players, "whatever.win");
    //players = readScores("whatever.win");

    for (int i = 0; i < players.size(); ++i) {
        cout << i << " " << players[i].name << " " << players[i].score << endl;
    }

    return 0;
}


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

	return 0;
 }
