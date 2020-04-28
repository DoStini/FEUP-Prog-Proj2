#include <iostream>
#include <vector>
#include <time.h>

#include "Game.h"


int main() {
    srand(0);
    Board board("board.txt");
    Game game(2, &board);
    std::cout << "Hello";
}


// STILL HAVE TO FIND OUT WHY CANT FREE LETTERS**