#include "IO.h"
#include "Menu.h"
#include <mmsystem.h>
#include<iostream>
#include<string>
#include<sstream>
#include <vector>

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

void showTitle() {
	bool wait = true;

	for (int letter = 0; letter < 8; letter++) {
		dropLetter(title[letter], 44, letter, 8, wait);
	}
	if (!wait) {
		std::cin.clear();
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
	}
	
	gotoxy(0, titleA.size() + 2);
}

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

void newGame(){

}
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
                  "(_)\\_)(______)(____)(____)(___/", 1, 70, YBEGMENU);

    for (int i = 0; i < rules.size(); ++i) {
        showCascading(rules[i], 2, 60,YBEGMENU + 7 + 2*i);      // 2*i -> skipping lines
    }
    gotoxy(70, YBEGMENU + 9 + 2*rules.size());          // Skipping lines
    waitForKey();
}

void showInst(){
    std::vector<std::string> rules{
            "1) It's crucial for the program integrity that",
            "you don't resize the window as it may break the program"
    };


    clearScreen(0, YBEGMENU);

    showCascading("\n"
                  " ____  __  __  __    ____  ___ \n"
                  "(  _ \\(  )(  )(  )  ( ___)/ __)\n"
                  " )   / )(__)(  )(__  )__) \\__ \\\n"
                  "(_)\\_)(______)(____)(____)(___/", 1, 70, YBEGMENU);

    for (int i = 0; i < rules.size(); ++i) {
        showCascading(rules[i], 2, 60,YBEGMENU + 7 + 2*i);      // 2*i -> skipping lines
    }
    gotoxy(70, YBEGMENU + 9 + 2*rules.size());          // Skipping lines
    waitForKey();
}
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
                  " \\___)(_)\\_)(____)(____/(____) (__) (___/", 1, 63, YBEGMENU);

    for (int i = 0; i < credits.size(); ++i) {
        showCascading(credits[i], 2, 50,YBEGMENU + 7 + i);
    }
    gotoxy(70, YBEGMENU + 9 + credits.size());
    waitForKey();
}
void showScores(){

}
void closeGame(){
    clearScreen(0, YBEGMENU);
    showCascading("\n"
                  " ____  _   _  ____    ____  _  _  ____  \n"
                  "(_  _)( )_( )( ___)  ( ___)( \\( )(  _ \\ \n"
                  "  )(   ) _ (  )__)    )__)  )  (  )(_) )\n"
                  " (__) (_) (_)(____)  (____)(_)\\_)(____/ ", 1, 65, YBEGMENU);
    showCascading("Thanks for playing!",10,75, YBEGMENU + 7);
    Sleep(1000);
    showCascading("We hope you enjoyed your stay...",10,70, YBEGMENU + 9);
    Sleep(1000);
    gotoxy(70, YBEGMENU + 11);
    waitForKey();
    exit(1);
}


void showOptions() {
    clearScreen(0, YBEGMENU);
	showCascading("\n"
		" __  __  ____  _  _  __  __ \n"
		"(  \\/  )( ___)( \\( )(  )(  )\n"
		" )    (  )__)  )  (  )(__)( \n"
		"(_/\\/\\_)(____)(_)\\_)(______)", 1, 70, YBEGMENU);

	std::vector<std::string> options{
            "Play (p)",
            "Rules (r)",
            "Instructions (i)",
            "Credits (c)",
            "Scoreboard (s)",
            "Exit (e)",
            "Input: "
	};


	showCascading("You have several commands:",1,71, YBEGMENU + 7);

    for (int i = 0; i < options.size(); ++i) {
        showCascading(options[i], 1, 75,YBEGMENU + 8 + i);
    }

    std::string command;
    std::cin >> command;
    std::cin.ignore(100, '\n');
    command = stringToLower(command);

    if (command == "p" || command == "play")                newGame();
    else if (command == "i" || command == "instructions")   showInst();
    else if (command == "r" || command == "rules")          showRules();
    else if (command == "c" || command == "credits")        showCredits();
    else if (command == "s" || command == "scoreboard")     showScores();
    else if (command == "e" || command == "exit")           closeGame();
}



