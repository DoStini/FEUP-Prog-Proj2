
#include "Menu.h"

#include <mmsystem.h>
#include<iostream>
#include<string>
#include<sstream>
#include <vector>
#include <fstream>

const std::vector<std::string> titleS{
	" .----------------. \n",
	"| .--------------. |\n",
	"| |    _______   | |\n",
	"| |   /  ___  |  | |\n",
	"| |  |  (__ \\_|  | |\n",
	"| |   '.___`-.   | |\n",
	"| |  |`\\____) |  | |\n",
	"| |  |_______.'  | |\n",
	"| |              | |\n",
	"| '--------------' |\n",
	" '----------------' \n"
};

const std::vector<std::string> titleC{
	" .----------------. \n",
	"| .--------------. |\n",
	"| |     ______   | |\n",
	"| |   .' ___  |  | |\n",
	"| |  / .'   \\_|  | |\n",
	"| |  | |         | |\n",
	"| |  \\ `.___.'\\  | |\n",
	"| |   `._____.'  | |\n",
	"| |              | |\n",
	"| '--------------' |\n",
	" '----------------'\n"
};

const std::vector<std::string> titleR{
	" .----------------. \n",
	"| .--------------. |\n",
	"| |  _______     | |\n",
	"| | |_   __ \\    | |\n",
	"| |   | |__) |   | |\n",
	"| |  _|  __ /    | |\n",
	"| | |   |  \\ \\_  | |\n",
	"| | |____| |___| | |\n",
	"| |              | |\n",
	"| '--------------' |\n",
	" '----------------' \n"
};

const std::vector<std::string> titleA{
	" .----------------. \n",
	"| .--------------. |\n",
	"| |      __      | |\n",
	"| |     /  \\     | |\n",
	"| |    / /\\ \\    | |\n",
	"| |   / ____ \\   | |\n",
	"| | _/ /    \\ \\_ | |\n",
	"| ||____|  |____|| |\n",
	"| |              | |\n",
	"| '--------------' |\n",
	" '----------------' \n"
};

const std::vector<std::string> titleB{
	" .----------------. \n",
	"| .--------------. |\n",
	"| |   ______     | |\n",
	"| |  |_   _ \\    | |\n",
	"| |    | |_) |   | |\n",
	"| |    |  __'.   | |\n",
	"| |   _| |__) |  | |\n",
	"| |  |_______/   | |\n",
	"| |              | |\n",
	"| '--------------' |\n",
	" '----------------' \n"
};

const std::vector<std::string> titleL{
	" .----------------. \n",
	"| .--------------. |\n",
	"| |   _____      | |\n",
	"| |  |_   _|     | |\n",
	"| |    | |       | |\n",
	"| |    | |   _   | |\n",
	"| |   _| |__/ |  | |\n",
	"| |  |________|  | |\n",
	"| |              | |\n",
	"| '--------------' |\n",
	" '----------------' \n"
};

const std::vector<std::string> titleE{
	" .----------------. \n",
	"| .--------------. |\n",
	"| |  _________   | |\n",
	"| | |_   ___  |  | |\n",
	"| |   | |_  \\_|  | |\n",
	"| |   |  _ | _   | |\n",
	"| |  _| |___/ |  | |\n",
	"| | |_________|  | |\n",
	"| |              | |\n",
	"| '--------------' |\n",
	" '----------------' \n"
};

const std::vector<std::string> title[8] = { titleS, titleC, titleR, titleA, titleB, titleB, titleL, titleE };

/**
 * Animates the drop of an individual letter from the title in the console.
 * Allows to skip the animation by pressing "ENTER"/"RETURN"
 *
 * @param[in] letter The vector of strings representing the letter
 * @param[in] time The time waited between frames of the animation
 * @param[in] num The order of the letter that is falling (letter 1, letter 2, ...)
 * @param[in] xStart The starting horizontal position of the title in the console. Allows to adjust and center the position of the title
 * @param[in, out] wait A boolean indicating if the key "ENTER"/"RETURN" has been pressed, allowing to skip the animation
 */
void dropLetter(std::vector<std::string> letter, int time, int num, unsigned short int xStart, bool &wait) {
	size_t distanceFallen, relativeDistanceToBottom;
	int xPosition = num * 19 + xStart;

	for (int i = letter.size() - 1; i >= 0; i--) {
		distanceFallen = letter.size() - i;

		for (std::vector<std::string>::const_reverse_iterator it = letter.crbegin(); it != letter.crend() - i; it++) {
			if (GetKeyState(VK_RETURN) & 0x8000) {
				wait = false;
			}
			relativeDistanceToBottom = it - letter.crbegin();

			gotoxy(xPosition, distanceFallen - relativeDistanceToBottom);
			std::cout << *it;
		}
		if(wait) Sleep(time);
	}
}

/**
 * Graphical function to show the title with ascii art word
 */
void showTitle() {
	bool wait = true;

	for (int letter = 0; letter < 8; letter++) {
		dropLetter(title[letter], 44, letter, 8, wait);
	}
	if (!wait) {
		std::cin.clear();
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
	}
}

/**
 * Function to show a string one character at a time intervaled by t miliseconds.
 *
 * @param s - String to be shown
 * @param t - Time in milliseconds between each character
 * @param xStart - x position to start writing
 * @param yStart - y position to start writing
 */
void showCascading(std::string s, time_t t, unsigned short int xStart, unsigned short int yStart) {
	unsigned short int lineFeed = yStart;
	gotoxy(xStart, lineFeed);
	for (int i = 0; i < s.length(); ++i) {
		if (s[i] == '\n') {
			lineFeed++;
			gotoxy(xStart, lineFeed);
			continue;
		}
		std::cout << s[i];
		Sleep(t);
	}

}


/**
 * Function to start the game, calling board and game
 *
 * @param numPlayers - Number of players
 * @param playerNames - Vector with the player names
 * @param fileName - File's name where the board is stored
 */
void startGame(unsigned short int numPlayers, std::vector<std::string> playerNames, std::string fileName){

    clearScreen(0, YBEGMENU);

    showCascading("\n"
                  "  ___    __    __  __  ____ \n"
                  " / __)  /__\\  (  \\/  )( ___)\n"
                  "( (_-. /(__)\\  )    (  )__) \n"
                  " \\___/(__)(__)(_/\\/\\_)(____)", 1, XBEGMENU, YBEGMENU);

    Board board(fileName);

    Game game(numPlayers, playerNames, &board);
}


/**
 * Function to graphicly show the subtitle
 * Also does:
 *      - Ask how many players that will play
 *      - Ask their names
 *      - Ask the name of the board file
 *      - Verify that the board file exists, if it doesn't, will ask to re-enter
 */
void newGame(){
    std::vector<std::string> phrases{
            "          So you decided to play the game?",
            "          How many players will be playing?",
            "                       Input: ",
            "What is the file of the board which you wish to load?",
            "          Input (example: board.txt): ",
    };

    std::vector<Player> players;

    clearScreen(0, YBEGMENU);

    showCascading("\n"
                  " _  _  ____  _    _     ___    __    __  __  ____ \n"
                  "( \\( )( ___)( \\/\\/ )   / __)  /__\\  (  \\/  )( ___)\n"
                  " )  (  )__)  )    (   ( (_-. /(__)\\  )    (  )__) \n"
                  "(_)\\_)(____)(__/\\__)   \\___/(__)(__)(_/\\/\\_)(____)", 1, XBEGMENU-10, YBEGMENU);

    for (int i = 0; i < 3; ++i) {
        showCascading(phrases[i], 2, XBEGMENU-10,YBEGMENU + 7 + i);
    }

    unsigned short int numPlayers;

    while (1){
        if (!checkInput(numPlayers) || (numPlayers < 2 || numPlayers > 4)){
            clearScreen(0,YBEGMENU + 9);
            errorMsg("Invalid, re-enter: ", XBEGMENU,YBEGMENU + 9);
        }
        else{
            break;
        }
    }

    std::vector<std::string> playerNames;
    std::string name;
    for (int k = 0; k < numPlayers; ++k) {
        printMsg("Player " + std::to_string(k+1) + "'s name: ", XBEGMENU, YBEGMENU + 10 + k);
        std::cin >> name;
        playerNames.push_back(name);
    }

    for (int i = 3; i < phrases.size(); ++i) {
        showCascading(phrases[i], 2, 60,YBEGMENU + 7 + numPlayers + i);
    }


    std::string file;
	std::stringstream ss;
    while (1){
		ss.str(std::string());
        if (checkInput(file)){
            std::ifstream ff;

			ss << "../Assets/" << file;
            ff.open(ss.str());
            if (!ff.is_open()){
                errorMsg("File does not exist!", XBEGMENU, YBEGMENU + 12 + numPlayers);
                waitForKey(XBEGMENU, YBEGMENU + 13 + numPlayers);
                clearAndPrint("Re-enter: ", XBEGMENU, YBEGMENU + 11 + numPlayers);
            }
            else{
                ff.close();
                break;
            }
        }
    }
    startGame(numPlayers, playerNames, ss.str());
}



/**
 * Graphical function to show the rules of the game
 */
void showRules(){

    std::vector<std::string> rules{
            "1) On your turn, play two of your tiles by covering",
            "letters on the gameboard squares with matching tiles.",
            "2) Draw as many tiles from the pool as you played,",
            "so that you have seven tiles again.",

            "3) You can only play tiles in the beggining of a word,",
            "or a a tile whose precedents in a word are all covered.",

            "4) If you can play, you must play.",

            "5) If you can't play any tile, trade two tiles.",

            "6) The game ends when all of the letters are covered.",
    };


    clearScreen(0, YBEGMENU);

    showCascading("\n"
                  " ____  __  __  __    ____  ___ \n"
                  "(  _ \\(  )(  )(  )  ( ___)/ __)\n"
                  " )   / )(__)(  )(__  )__) \\__ \\\n"
                  "(_)\\_)(______)(____)(____)(___/", 1, XBEGMENU, YBEGMENU);

    for (int i = 0; i < rules.size(); ++i) {
        showCascading(rules[i], 2, 60,YBEGMENU + 7 + 2*i);      // 2*i -> skipping lines
    }

    waitForKey(XBEGMENU, YBEGMENU + 9 + 2*rules.size());                     // Skipping lines
}

/**
 * Graphical function to show credits
 */
void showCredits(){
    std::vector<std::string> credits{
            "                              Made by:",
            "                 Andre Moreira: github.com/DoStini",
            "                  Nuno Alves: github.com/homailot",
            " ",
            "           Thank you to http://patorjk.com/software/taag/",
            "for providing amazing ascii art to make our project more visually apealing."
    };


    clearScreen(0, YBEGMENU);

    showCascading("\n"
                  "  ___  ____  ____  ____  ____  ____  ___ \n"
                  " / __)(  _ \\( ___)(  _ \\(_  _)(_  _)/ __)\n"
                  "( (__  )   / )__)  )(_) )_)(_   )(  \\__ \\\n"
                  " \\___)(_)\\_)(____)(____/(____) (__) (___/", 1, XBEGMENU - 7, YBEGMENU);

    for (int i = 0; i < credits.size(); ++i) {
        showCascading(credits[i], 2, XBEGMENU - 20,YBEGMENU + 7 + i);
    }
    waitForKey(XBEGMENU, YBEGMENU + 9 + credits.size());
}

/**
 * Function to close the game
 */
void closeGame(){
    clearScreen(0, YBEGMENU);
    showCascading("\n"
                  " ____  _   _  ____    ____  _  _  ____  \n"
                  "(_  _)( )_( )( ___)  ( ___)( \\( )(  _ \\ \n"
                  "  )(   ) _ (  )__)    )__)  )  (  )(_) )\n"
                  " (__) (_) (_)(____)  (____)(_)\\_)(____/ ", 1, XBEGMENU-5, YBEGMENU);
    showCascading("Thanks for playing!",10,XBEGMENU+5, YBEGMENU + 7);
    Sleep(1000);
    showCascading("We hope you enjoyed your stay...",10,XBEGMENU, YBEGMENU + 9);
    Sleep(1000);
    waitForKey(XBEGMENU, YBEGMENU + 11);
    exit(1);
}


/**
 * Function to show the scoreboard (best 5 players of all time)
 */
void showScores(){

    clearScreen(0, YBEGMENU);

    showCascading("\n"
                  " ____  _____  ____    ___ \n"
                  "(_  _)(  _  )(  _ \\  | __)\n"
                  "  )(   )(_)(  )___/  |__ \\\n"
                  " (__) (_____)(__)    (___/", 1, XBEGMENU + 10, YBEGMENU);


    std::vector<Winner> bestPlayers = readScores("scoreboard.win");
    std::vector<ConsoleColors> medals = {ConsoleColors::OliveBack, ConsoleColors::SilverBack, ConsoleColors::YellowBack, ConsoleColors::WhiteBack, ConsoleColors::WhiteBack};
    std::vector<ConsoleColors> textColor = {ConsoleColors::OliveFore, ConsoleColors::SilverFore, ConsoleColors::YellowFore, ConsoleColors::WhiteFore, ConsoleColors::WhiteFore};

    if (bestPlayers[0].score != 0){
        showCascading("Congratulations to the best players around here", 1, XBEGMENU, YBEGMENU + 10);
        for (int i = 0; i < 5; ++i) {
            if (bestPlayers[i].score == 0){
                break;
            }
            printMsg(std::to_string(i+1), XBEGMENU + 10, YBEGMENU + 11 + i, ConsoleColors::BlackFore, medals[i]);
            printMsg(" " + std::string(bestPlayers[i].name), textColor[i]);
            printMsg(" - ");
            printMsg(std::to_string(bestPlayers[i].score), textColor[i]);
        }
        waitForKey(XBEGMENU, YBEGMENU + 18);
    }
    else{
        printMsg("There is noone here yet. Go on and play!", XBEGMENU + 5, YBEGMENU + 9);
        waitForKey(XBEGMENU + 5, YBEGMENU + 11);
    }
}


/**
 * The principal function. Shows the menu and deals with the input, calling functions depending on the player's input
 */
void showOptions() {
    clearScreen(0, YBEGMENU);
	showCascading("\n"
		" __  __  ____  _  _  __  __ \n"
		"(  \\/  )( ___)( \\( )(  )(  )\n"
		" )    (  )__)  )  (  )(__)( \n"
		"(_/\\/\\_)(____)(_)\\_)(______)", 1, XBEGMENU, YBEGMENU);

	std::vector<std::string> options{
            "Play (p)",
            "Rules (r)",
            "Credits (c)",
            "Scoreboard (s)",
            "Exit (e)",
            "Input: "
	};


	showCascading("You have several commands:",1,XBEGMENU, YBEGMENU + 7);

    for (int i = 0; i < options.size(); ++i) {
        showCascading(options[i], 1, XBEGMENU + 5,YBEGMENU + 8 + i);
    }

    std::string command;
    std::cin >> command;
    std::cin.ignore(100, '\n');
    command = stringToLower(command);

    if (command == "p" || command == "play")                newGame();
    else if (command == "r" || command == "rules")          showRules();
    else if (command == "c" || command == "credits")        showCredits();
    else if (command == "s" || command == "scoreboard")     showScores();
    else if (command == "e" || command == "exit")           closeGame();
}
