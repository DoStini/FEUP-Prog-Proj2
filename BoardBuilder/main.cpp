﻿// BoardBuilder.cpp : Defines the entry point for the application.
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
#include <algorithm>

void inputLimits(Board& board) {
	std::stringstream ss;
	unsigned short input;

	unsigned short heightLowerLimit = board.getHeightLimits().first;
	unsigned short heightUpperLimit = board.getHeightLimits().second;
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

	unsigned short widthLowerLimit = board.getWidthLimits().first;
	unsigned short widthUpperLimit = board.getWidthLimits().second;
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
		if (checkStop()) break;

		printMessage("Input was invalid, please try again.", RED, BLACK);

		printMessage(message, Color::WHITE, Color::BLACK);
	}

	return location;
}

void inputWords(Board& board, const std::vector<std::string>& words) {
	std::stringstream ss;
	std::string deletePrompt, text;
	std::pair<unsigned short, unsigned short> size = board.getSize();
	char line, column, orientation, input;
	short success;

	while (true) {
		Word newWord;
		printMessage(board.showBoard());

		printMessage("Add or delete? (write 'delete' to delete, anything else to continue)", WHITE, BLACK);
		getString(deletePrompt);

		clearScreen();
		if (checkStop()) break;

		printMessage(board.showBoard());
		printMessage("What is the word?", WHITE, BLACK);
		while (!checkInputOrSTOP(text) || !newWord.setText(words, text)) {
			clearScreen();
			if (checkStop()) break;
			printMessage(board.showBoard());

			printMessage("Input was invalid or word is not real, please try again.", RED, BLACK);

			printMessage("What is the word?", WHITE, BLACK);
		}
		if (checkStop()) break;

		clearScreen();

		printMessage(board.showBoard());
		char upperLineLimit = (size.first - 1 + 'A');
		ss.str(std::string());
		ss << "Line of word? [A, " << upperLineLimit << "]";
		line = inputLocation(upperLineLimit, ss.str());
		
		if (checkStop()) break;
		line = toupper(line);

		clearScreen();

		printMessage(board.showBoard());
		char upperColumnLimit = (size.second - 1 + 'a');
		ss.str(std::string());
		ss << "Column of word? [a, " << upperColumnLimit << "]";
		column = inputLocation(upperColumnLimit, ss.str());

		if (checkStop()) break;
		column = tolower(column);

		clearScreen();

		printMessage(board.showBoard());
		printMessage("Is the word horizontal or vertical? (H, V)", WHITE, BLACK);
		while (!checkInputOrSTOP(orientation) || (toupper(orientation) != 'H' && toupper(orientation) != 'V')) {
			clearScreen();
			if (checkStop()) break;
			printMessage(board.showBoard());

			printMessage("Input was invalid, please try again.", RED, BLACK);

			printMessage("Is the word horizontal or vertical? (H, V)", WHITE, BLACK);
		}
		orientation = toupper(orientation);
		if (checkStop()) break;

		newWord.setLocation(std::make_pair(line - 'A', column - 'a'), orientation);

		clearScreen();

		printMessage(board.showBoard());
		ss.str(std::string());
		ss << "So the word is '" << text << "', it's orientation is " << orientation << ", and is in line " << (char)line << " and column " << (char)column << ".";
		printMessage(ss.str());
		printMessage("Is this correct? (N to retry)", Color::WHITE, Color::BLACK);
		getChar(input);

		Coordinate position = std::make_pair(line - 'A', column - 'a');

		if (toupper(input) != 'N') {
			clearScreen();
			if (input == EOF) break;

			if (stringToUpper(deletePrompt) == "DELETE") {
				success = board.deleteWord(newWord, position, orientation == 'V');
			}
			else {
				success = board.addWord(newWord, position, orientation == 'V');
			}

			if (success == 1) {
				printMessage("Success!");
			}
			else {
				if (stringToUpper(deletePrompt) == "DELETE") {
					if(success == 0) printMessage("Error! That word is not on the board.", RED, BLACK);
					else {
						printMessage("Error! Can't delete that word.", RED, BLACK);
						printMessage("Deleting that word creates an illegal board disposition.", RED, BLACK);
					}
				}
				else printMessage("Error! The word does not fit in the board or intersects with another word.", RED, BLACK);
			}

			waitForKey();
			
		}

		clearScreen();
	}
}

int main()
{
	std::vector<std::string> words;
	std::string fileName;
	std::stringstream ss;
	std::pair<unsigned short, unsigned short> size;
	char input;
	Board board;
	readWords(words);

	printMessage("Welcome to the Scrabble Junior Board Builder Tool.");
	printMessage("Creating a Board is easy, don't worry. Just follow the instructions and answer all of the questions.");
	ss.str(std::string());
	ss << "The minimum size of a board is " << board.getMinSquares() << " squares.";

	printMessage(ss.str(), GREEN, BLACK);
	waitForKey();

	while (true) {
		clearScreen();

		inputLimits(board);
		while (!board.hasMinimumOfSquares()) {
			ss.str(std::string());
			ss << "The minimum size of a board is " << board.getMinSquares() << " squares, ";
			ss << "please re-enter the size of the board.";
			printMessage(ss.str(), RED, BLACK);
			waitForKey();

			clearScreen();

			inputLimits(board);
		}

		clearScreen();

		size = board.getSize();
		ss.str(std::string());
		ss << "Your input was: " << size.first << "x" << size.second;
		printMessage(ss.str());
		printMessage("Is this correct? (N to retry)", Color::WHITE, Color::BLACK);
		getChar(input);

		if (toupper(input) != 'N') break;
	}

	clearScreen();
	board.initializeWords();
	
	printMessage("You will now be asked to input the words into the board.");
	printMessage("To stop input and save all changes into a file you can do the following:");
	printMessage("A minimum of 14 letters is required to save the board.", GREEN, BLACK);
	printMessage("If in Windows, at any point, press CTRL+Z.", GREEN, BLACK);
	printMessage("If in Linux or Mac OS, at any point, press CTRL+D.", GREEN, BLACK);
	waitForKey();

	clearScreen();
	inputWords(board, words);
	while (!board.hasMinimumOfLetters()) {
		std::cin.clear();

		ss.str(std::string());
		ss << "The board does not have the required minimum of " << board.getMinLetters() << " letters.";
		printMessage(ss.str(), RED, BLACK);
		printMessage("Please continue building the board until the minimum is reached.", RED, BLACK);

		inputWords(board, words);
	}
	std::cin.clear();


	clearScreen();

	printMessage("Insert the name of the file where the board will be saved.", WHITE, BLACK);
	while (!checkInput(fileName)) {
		clearScreen();

		printMessage("Input was invalid, please try again.", RED, BLACK);
		printMessage("Insert the name of the file where the board will be saved.", WHITE, BLACK);
	};

	board.saveBoard(fileName);
	

	ss.str(std::string());
	ss << "Your board has been saved into the '" << fileName << ".TXT' file in the Assets folder.";
	printMessage(ss.str());
	waitForKey();
	return 0;
}