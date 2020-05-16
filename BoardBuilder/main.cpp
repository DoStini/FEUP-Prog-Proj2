// BoardBuilder.cpp : Defines the entry point for the application.
//

#include "main.h"
#include "fileExplorer.h"
#include "color.h"
#include "boardIO.h"
#include "word.h"
#include "board.h"
#include "menu.h"
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

/**
 * Function used to ask the user to input the number of lines and columns in the board.
 * Then, there is an attempt to store the values in the board, if this is not possible then it asks again.
 *
 * @param[in, out] board Current board state, passed as reference
 */
void inputLimits(Board& board) {
	std::stringstream ss;
	unsigned short input;

	unsigned short heightLowerLimit = board.getHeightLimits().first;
	unsigned short heightUpperLimit = board.getHeightLimits().second;
	ss << "What are the number of lines on the board? [" << heightLowerLimit << ", " << heightUpperLimit << "]";
	printMessage(ss.str(), Color::WHITE, Color::BLACK);
	while (!checkInput(input) || !board.setHeight(input)) {
		clearScreen(0, YBEGMENU);

		printMessage("Input was invalid, please try again.", RED, BLACK);

		ss.str(std::string());
		ss << "What are the number of lines on the board? [" << heightLowerLimit << ", " << heightUpperLimit << "]";
		printMessage(ss.str(), Color::WHITE, Color::BLACK);
	}

	clearScreen(0, YBEGMENU);

	unsigned short widthLowerLimit = board.getWidthLimits().first;
	unsigned short widthUpperLimit = board.getWidthLimits().second;
	ss.str(std::string());
	ss << "What are the number of columns on the board? [" << widthLowerLimit << ", " << widthUpperLimit << "]";
	printMessage(ss.str(), Color::WHITE, Color::BLACK);
	while (!checkInput(input) || !board.setWidth(input)) {
		clearScreen(0, YBEGMENU);

		printMessage("Input was invalid, please try again.", RED, BLACK);

		ss.str(std::string());
		ss << "What are the number of columns on the board? [" << widthLowerLimit << ", " << widthUpperLimit << "]";
		printMessage(ss.str(), Color::WHITE, Color::BLACK);
	}
}

/**
 * Function used to ask the user to input the number of lines and columns in the board.
 * Then, there is an attempt to store the values in the board, if this is not possible then it asks again.
 *
 * @param limit Upper limit of the board (column or row from 'A' to 'Z') that a word can be placed on
 * @param message Prompt message asked to the player
 * @param yStart Where to clean the screen
 *
 * @returns the in bounds location that the user inputed
 */
char inputLocation(char limit, std::string message, unsigned short yStart) {
	char location;

	printMessage(message, Color::WHITE, Color::BLACK);

	while (!checkInputOrSTOP(location) || toupper(location) < 'A' || toupper(location) > toupper(limit)) {
		clearScreen(0, yStart);
		if (checkStop()) break;

		printMessage("Input was invalid, please try again.", RED, BLACK);

		printMessage(message, Color::WHITE, Color::BLACK);
	}

	return location;
}

/**
 * Function used to ask the user to input words into the board.
 * Asks if the user wants to add or delete word.
 * Then it asks for it's position and orientation.
 * If the word is valid and is placed in a valid position, the words is added to/deleted from the board.
 * Repeats this process until an EOF character is input.
 *
 * @param[in, out] board Current board state, passed as reference
 * @param[in] words Vector of strings containing the valid words that can be input
 */
void inputWords(Board& board, const std::vector<std::string>& words) {
	std::stringstream ss;
	std::string deletePrompt, text;
	std::pair<unsigned short, unsigned short> size = board.getSize();
	char line, column, orientation, input;
	short success;
	unsigned short hSize = ((board.getSize()).first * 2) + 2 + YBEGMENU;
	bool vertical;

	while (true) {
		Word newWord;
		clearScreen(0, YBEGMENU);
		board.showCenteredBoard();

		printMessage("Add or delete? (write 'delete' to delete, anything else to continue)", WHITE, BLACK);
		getString(deletePrompt);

		clearScreen(0, hSize);
		if (checkStop()) break;

		board.showCenteredBoard();
		printMessage("What is the word?", WHITE, BLACK);
		while (!checkInputOrSTOP(text) || !newWord.setText(words, text)) {
			clearScreen(0, hSize);
			if (checkStop()) break;

			printMessage("Input was invalid or word is not real, please try again.", RED, BLACK);

			printMessage("What is the word?", WHITE, BLACK);
		}
		if (checkStop()) break;

		clearScreen(0, hSize);
		char upperLineLimit = (size.first - 1 + 'A');
		ss.str(std::string());
		ss << "Line of word? [A, " << upperLineLimit << "]";
		line = inputLocation(upperLineLimit, ss.str(), hSize);
		
		if (checkStop()) break;
		line = toupper(line);

		clearScreen(0, hSize);

		char upperColumnLimit = (size.second - 1 + 'a');
		ss.str(std::string());
		ss << "Column of word? [a, " << upperColumnLimit << "]";
		column = inputLocation(upperColumnLimit, ss.str(), hSize);

		if (checkStop()) break;
		column = tolower(column);

		clearScreen(0, hSize);

		printMessage("Is the word horizontal or vertical? (H, V)", WHITE, BLACK);
		while (!checkInputOrSTOP(orientation) || (toupper(orientation) != 'H' && toupper(orientation) != 'V')) {
			clearScreen(0, hSize);
			if (checkStop()) break;

			printMessage("Input was invalid, please try again.", RED, BLACK);

			printMessage("Is the word horizontal or vertical? (H, V)", WHITE, BLACK);
		}
		orientation = toupper(orientation);
		if (checkStop()) break;
		vertical = orientation == 'V';

		newWord.setLimits(std::make_pair(line - 'A', column - 'a'), vertical);

		clearScreen(0, hSize);

		ss.str(std::string());
		ss << "So the word is '" << text << "', it's orientation is " << orientation << ", and is in line " << (char)line << " and column " << (char)column << ".";
		printMessage(ss.str());
		printMessage("Is this correct? (N to retry)", Color::WHITE, Color::BLACK);
		getChar(input);

		Coordinate position = std::make_pair(line - 'A', column - 'a');

		if (toupper(input) == 'N') {
			clearScreen(0, hSize);
			continue;
		}

		clearScreen(0, hSize);
		if (input == EOF) break;

		if (stringToUpper(deletePrompt) == "DELETE") {
			success = board.deleteWord(newWord, position, vertical);
		}
		else {
			success = board.addWord(newWord, position, vertical);
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
			
		clearScreen(0, hSize);
	}
}

/**
 * Main function, asks the user to build a board.
 * Afterwards, asks for a name used for a file where the board will be saved.
 */
int main()
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions

	MoveWindow(console, r.left, r.top, 1400, 1100, TRUE);       // Setting window Size

	SetWindowLong(console, GWL_STYLE, GetWindowLong(console, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);   // Making window unresizable


	std::vector<std::string> words;
	std::string fileName;
	std::stringstream ss;
	std::pair<unsigned short, unsigned short> size;
	char input;
	Board board;
	readWords(words);

	showTitle();
	gotoxy(0, YBEGMENU);

	printMessage("Welcome to the Scrabble Junior Board Builder Tool.");
	printMessage("Creating a Board is easy, don't worry. Just follow the instructions and answer all of the questions.");
	ss.str(std::string());
	ss << "The minimum size of a board is " << board.getMinSquares() << " squares.";

	printMessage(ss.str(), GREEN, BLACK);
	waitForKey();

	while (true) {
		clearScreen(0, YBEGMENU);

		inputLimits(board);
		while (!board.hasMinimumOfSquares()) {
			ss.str(std::string());
			ss << "The minimum size of a board is " << board.getMinSquares() << " squares, ";
			ss << "please re-enter the size of the board.";
			printMessage(ss.str(), RED, BLACK);
			waitForKey();

			clearScreen(0, YBEGMENU);

			inputLimits(board);
		}

		clearScreen(0, YBEGMENU);

		size = board.getSize();
		ss.str(std::string());
		ss << "Your input was: " << size.first << "x" << size.second;
		printMessage(ss.str());
		printMessage("Is this correct? (N to retry)", Color::WHITE, Color::BLACK);
		getChar(input);

		if (toupper(input) != 'N') break;
	}

	clearScreen(0, YBEGMENU);
	board.initializeWords();
	
	printMessage("You will now be asked to input the words into the board.");
	printMessage("To stop input and save all changes into a file you can do the following:");
	printMessage("A minimum of 14 letters is required to save the board.", GREEN, BLACK);
	printMessage("If in Windows, at any point, press CTRL+Z.", GREEN, BLACK);
	printMessage("If in Linux or Mac OS, at any point, press CTRL+D.", GREEN, BLACK);
	waitForKey();

	clearScreen(0, YBEGMENU);
	inputWords(board, words);
	while (!board.hasMinimumOfLetters()) {
		std::cin.clear();

		ss.str(std::string());
		ss << "The board does not have the required minimum of " << board.getMinLetters() << " letters.";
		printMessage(ss.str(), RED, BLACK);
		printMessage("Please continue building the board until the minimum is reached.", RED, BLACK);

		waitForKey();

		inputWords(board, words);
	}
	std::cin.clear();


	clearScreen(0, YBEGMENU);

	printMessage("Insert the name of the file where the board will be saved.", WHITE, BLACK);
	while (!checkInput(fileName)) {
		clearScreen(0, YBEGMENU);

		printMessage("Input was invalid, please try again.", RED, BLACK);
		printMessage("Insert the name of the file where the board will be saved.", WHITE, BLACK);
	};

	board.saveBoard(fileName);
	clearScreen(0, YBEGMENU);
	

	ss.str(std::string());
	ss << "Your board has been saved into the '" << fileName << ".TXT' file.";
	
	printMessage(ss.str());

	ss.str(std::string());
	ss << "To use this board in Scrabble Junior, please transfer the file to the ";

	printMessage(ss.str(), "");

	printMessage("Scrabble Junior folder", GREEN, BLACK);
	waitForKey();
	return 0;
}
