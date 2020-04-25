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

int main()
{
	std::stringstream ss;
	std::vector<std::string> words;
	int input;
	Board board;
	readWords(words);
	
	printMessage("Welcome to the Scrabble Junior Board Builder Tool.");
	printMessage("Creating a Board is easy, don't worry. Just follow the instructions and answer all of the questions.");
	waitForKey();
	clearScreen();
	ss << "What are the number of lines on the board? [" << board.getHeightLimits().first << ", " << board.getHeightLimits().second << "]";
	printMessage(ss.str(), Color::WHITE, Color::BLACK);
	while (!checkInput(input) || !board.setHeight(input)) {
		clearScreen();
		printMessage("Input was invalid, please try again.", RED, BLACK);
		printMessage("What are the number of columns on the board?", Color::WHITE, Color::BLACK);
	}

	
	return 0;
}
