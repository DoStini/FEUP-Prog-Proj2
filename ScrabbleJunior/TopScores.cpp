//
// Created by morei on 5/12/2020.
//

#include "TopScores.h"

/**
 * Function to read the scoreboard file
 *
 * @param fileName - Name of the file
 * @return vector<Winner> - vector with the best 5 players of all time, in a struct Winner containing name and score
 */
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


/**
 * Function to write players vector in the scoreboard file
 *
 * @param players - The players to be written in file
 * @param fileName - Name of the file
 * @param firstTime - If there is no file already
 */
void writeScores(std::vector<Winner> &players, std::string fileName, bool firstTime){

    std::ofstream f_out;
    f_out.open(fileName, std::ios::binary);

    if (firstTime){
        for (int i = 0; i < 5; ++i) {                               // If there is not respective file, a clean one with 5 null players will be created
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

/**
 * Checks if a player can go into the score board. If so, they are added
 *
 * @param winners - Players to be add
 * @param fileName - File's name
 */
void checkScores(std::vector<Winner> &winners, std::string fileName){
    std::vector<Winner> bestPlayers = readScores(fileName);
    short int index = -1;                                                   // Predefining index as -1
    for (int i = 0; i < bestPlayers.size(); ++i) {
        if (winners[0].score > bestPlayers[i].score){                       // Finding the first player in the scoreboard with a lower score than current player
            index = i;
            break;
        }
    }

    if (index != -1){                                                       // If there is no player with a lower score, index will remain as -1, so no replacement will be made
        for (int i = 0; i < winners.size(); ++i) {
            bestPlayers.insert(bestPlayers.begin() + index + i, winners[i]);// Inserting all players in index's position
        }
                                                                            // Vector will be extended, so we need to resize and delete extra players
        bestPlayers.resize(5);
        writeScores(bestPlayers, fileName);
    }
}