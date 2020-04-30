#include <iostream>
#include <vector>
#include <time.h>
#include "IO.h"
#include "Game.h"
using namespace std;

int main() {
    srand(0);
    Board board("board.txt");
    cout << "\033[0;0H";
    cout << "Z";
    //Game game(1, &board);
}

// STILL HAVE TO FIND OUT WHY CANT FREE LETTERS**