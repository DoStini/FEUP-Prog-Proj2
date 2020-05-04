#include <iostream>
#include <vector>
#include <time.h>
#include <cstdlib>
#include <algorithm>
#include <windows.h>
#include <zconf.h>
#include "IO.h"
#include "Color.h"
#include "Game.h"
using namespace std;






int main() {

    //vector<int> viktor = {1,2,4,4,3};
    //cout << std::find(viktor.begin(), viktor.end(), 3) - viktor.begin();
    srand(0);
    Board board("board.txt");
    Game game(3, &board);

}



