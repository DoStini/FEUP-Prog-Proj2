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

void inputLimits(Board& board) {
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

char inputLocation(char limit, std::string message) {
	char location;

	printMessage(message, Color::WHITE, Color::BLACK);

	while (!checkInputOrSTOP(location) || toupper(location) < 'A' || toupper(location) > toupper(limit)) {
		clearScreen();

		printMessage("Input was invalid, please try again.", RED, BLACK);

		printMessage(message, Color::WHITE, Color::BLACK);
	}

	return location;
}

void inputWords(Board& board) {
	std::stringstream ss;
	std::pair<int, int> size = board.getSize();
	char line, column, orientation;

	while (true) {
		Word newWord;

		char upperLineLimit = (size.first - 1 + 'A');
		ss.str(std::string());
		ss << "Line of word? [A, " << upperLineLimit << "]";
		line = inputLocation(upperLineLimit, ss.str());
		
		if (checkStop(line)) break;

		clearScreen();

		char upperColumnLimit = (size.second - 1 + 'a');
		ss.str(std::string());
		ss << "Column of word? [a, " << upperColumnLimit << "]";
		column = inputLocation(upperColumnLimit, ss.str());

		if (checkStop(column)) break;

		newWord.setPosition(std::make_pair(line, column));

		clearScreen();

		ss.str(std::string());
		ss << "The word is in line " << (char) toupper(line) << " and column " << (char) tolower(column);
		printMessage(ss.str());
		printMessage("Is the word horizontal or vertical? (H, V)", WHITE, BLACK);
		while (!checkInput(orientation) || !newWord.setOrientation(orientation)) {
			clearScreen();

			printMessage("Input was invalid, please try again.", RED, BLACK);

			ss.str(std::string());
			ss << "The word is in line " << (char)toupper(line) << " and column " << (char)tolower(column);
			printMessage(ss.str());
			printMessage("Is the word horizontal or vertical? (H, V)", WHITE, BLACK);
		}

		clearScreen();
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

	clearScreen();
	
	printMessage("You will now be asked to input the words into the board.");
	printMessage("To stop input and save all changes into a file you can do the following:");
	printMessage("If in Windows, at any point, press CTRL+Z.", GREEN, BLACK);
	printMessage("If in Linux or Mac OS, at any point, press CTRL+D.", GREEN, BLACK);
	waitForKey();

	clearScreen();
	
	inputWords(board);
	return 0;
}
