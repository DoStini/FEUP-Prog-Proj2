#include "menu.h"
#include "boardIO.h"
#include <windows.h>
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
void dropLetter(const std::vector<std::string> &letter, int time, int num, unsigned short int xStart, bool& wait) {
	size_t distanceFallen, relativeDistanceToBottom;
	int xPosition = num * 19 + xStart;

	// Each frame (iteration of this loop) "drops" the letter by one line.
	for (int i = letter.size() - 1; i >= 0; i--) {
		distanceFallen = letter.size() - i;

		// Redraws the part of the letter that can be seen and "drops" it by one line.
		for (auto it = letter.crbegin(); it != letter.crend() - i; it++) {
			if (GetKeyState(VK_RETURN) & 0x8000) { ///< Checks if the "ENTER" key has been pressed.
				wait = false;
			}
			relativeDistanceToBottom = it - letter.crbegin();

			gotoxy(xPosition, distanceFallen - relativeDistanceToBottom);
			std::cout << *it;
		}
		if (wait) Sleep(time);
	}
}

/**
 * Animates showing the title, "dropping" one letter at a time.
 */
void showTitle() {
	bool wait = true;

	for (int letter = 0; letter < 8; letter++) {
		dropLetter(title[letter], 44, letter, 8, wait);
	}
	if (!wait) { ///< If wait is false, this means that the "ENTER" key was pressed, therefore the input buffer needs to be cleared.
		std::cin.clear();
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
	}

	gotoxy(0, titleA.size() + 2);
}