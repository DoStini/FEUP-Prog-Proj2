// BoardBuilder.cpp : Defines the entry point for the application.
//

#include "main.h"
#include "fileExplorer.h"
#include "color.h"
#include "boardIO.h"
#include "word.h"
#include "board.h"
#include <vector>
#include <string>
#include <sstream>

void inputLimits(Board &board) {
	std::stringstream ss;
	int input;

	int heightLowerLimit = board.getHeightLimits().first;
	int heightUpperLimit = board.getHeightLimits().second;
	ss << "What are the number of lines on the board? [" << heightLowerLimit << ", " << heightUpperLimit << "]";
	printMessage(ss.str(), Color::WHITE, Color::BLACK);
	while (!checkInput(input) || !board.setHeight(input)) {
		clearScreen();

		printMessage("Input was invalid, please try again.", RED, BLACK);

		ss.str(std::string());
		ss << "What are the number of lines on the board? [" << heightLowerLimit << ", " << heightUpperLimit << "]";
		printMessage(ss.str(), Color::WHITE, Color::BLACK);
	}

	clearScreen();

	int widthLowerLimit = board.getWidthLimits().first;
	int widthUpperLimit = board.getWidthLimits().second;
	ss.str(std::string());
	ss << "What are the number of columns on the board? [" << widthLowerLimit << ", " << widthUpperLimit << "]";
	printMessage(ss.str(), Color::WHITE, Color::BLACK);
	while (!checkInput(input) || !board.setWidth(input)) {
		clearScreen();

		printMessage("Input was invalid, please try again.", RED, BLACK);

		ss.str(std::string());
		ss << "What are the number of columns on the board? [" << widthLowerLimit << ", " << widthUpperLimit << "]";
		printMessage(ss.str(), Color::WHITE, Color::BLACK);
	}
}

int main()
{
	std::vector<std::string> words;
	std::stringstream ss;
	std::pair<int, int> size;
	char input;
	Board board;
	readWords(words);
	
	printMessage("Welcome to the Scrabble Junior Board Builder Tool.");
	printMessage("Creating a Board is easy, don't worry. Just follow the instructions and answer all of the questions.");
	waitForKey();

	while (true) {
		clearScreen();

		inputLimits(board);

		clearScreen();

		size = board.getSize();
		ss.str(std::string());
		ss << "Your input was: " << size.first << "x" << size.second;
		printMessage(ss.str());
		printMessage("Is this correct? (Y, N)", Color::WHITE, Color::BLACK);

		if (checkInput(input) && toupper(input) == 'Y') break;
	}
	


	
	return 0;
}
