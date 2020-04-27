#include <iostream>
#include <vector>
#include <time.h>

#include "Game.h"


int main() {
    srand(time(NULL));
    Board board("board.txt");
    Game game(2, board);
    std::cout << "Hello";
}