//
// Created by morei on 5/12/2020.
//

#include "topScores.h"


std::vector<Winner> readScores(std::string fileName){
    std::ifstream f_in;
    f_in.open(fileName, std::ios::binary);
    std::vector<Winner> bestPlayers;

    if (!f_in.is_open()){
        std::vector<Winner> temp;
        writeScores(temp, fileName, true);
    }

    Winner player;

    for (int i = 0; i < 5; ++i){
        f_in.read((char *) &player, sizeof(Winner));
        bestPlayers.push_back(player);
    }

    f_in.close();

    return bestPlayers;
}



void writeScores(std::vector<Winner> &players, std::string fileName, bool firstTime){

    std::ofstream f_out;
    f_out.open(fileName, std::ios::binary);

    if (firstTime){
        for (int i = 0; i < 5; ++i) {
            Winner player;
            f_out.write((char * ) &player, sizeof(Winner));
        }
    }
    else{
        for (int i = 0; i < 5; ++i) {
            f_out.write((char * ) &players[i], sizeof(Winner));
        }
    }

    f_out.close();
}

void checkScores(std::vector<Winner> &winners, std::string fileName){
    std::vector<Winner> bestPlayers = readScores(fileName);
    short int index = bestPlayers.size() == 5 ? -1 : bestPlayers.size();
    for (int i = 0; i < bestPlayers.size(); ++i) {
        if (winners[0].score > bestPlayers[i].score){
            index = i;
            break;
        }
    }

    if (index != -1){
        for (int i = 0; i < winners.size(); ++i) {
            bestPlayers.insert(bestPlayers.begin() + index + i, winners[i]);
        }

        bestPlayers.resize(5);
        writeScores(bestPlayers, fileName);
    }
}