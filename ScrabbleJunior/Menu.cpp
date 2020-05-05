#include "IO.h"
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

void dropLetter(std::vector<std::string> letter, int num, unsigned short int xStart) {
	size_t distanceFallen, relativeDistanceToBottom;

	for (int i = letter.size() - 1; i >= 0; i--) {
		distanceFallen = letter.size() - i;

		for (std::vector<std::string>::const_reverse_iterator it = letter.crbegin(); it != letter.crend() - i; it++) {
			relativeDistanceToBottom = it - letter.crbegin();

			gotoxy(num * 19 + xStart, distanceFallen - relativeDistanceToBottom);
			std::cout << *it;
		}
		Sleep(50);
	}
}

void showTitle() {
	for (int letter = 0; letter < 8; letter++) {
		dropLetter(title[letter], letter, 8);
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

void showOptions() {
	showCascading("\n"
		" __  __  ____  _  _  __  __ \n"
		"(  \\/  )( ___)( \\( )(  )(  )\n"
		" )    (  )__)  )  (  )(__)( \n"
		"(_/\\/\\_)(____)(_)\\_)(______)", 1, 65, 13);
	clearScreen(66, 20);
	std::cout << "Welcome to Scrabble Junior.";
	gotoxy(61, 21);
	std::cout << "Made by Andre Moreira and Nuno Alves\n";
}