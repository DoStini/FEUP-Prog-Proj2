//
// Created by morei on 4/27/2020.
//

#ifndef SCRABBLEJUNIOR_COLOR_H
#define SCRABBLEJUNIOR_COLOR_H

#include <vector>
#include <string>

enum Color {BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE};

// Pair of codes stand for BG and FG respectively
const std::vector<std::pair<int, int>> COLOR = {
        std::make_pair(40, 30),
        std::make_pair(41, 31),
        std::make_pair(42, 32),
        std::make_pair(43, 33),
        std::make_pair(44, 34),
        std::make_pair(45, 35),
        std::make_pair(46, 36),
        std::make_pair(47, 37),
};


#endif //SCRABBLEJUNIOR_COLOR_H
