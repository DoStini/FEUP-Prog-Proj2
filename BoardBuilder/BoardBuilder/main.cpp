// BoardBuilder.cpp : Defines the entry point for the application.
//

#include "main.h"
#include "fileExplorer.h"
#include "color.h"
#include "boardIO.h"
#include <vector>
#include <string>

int main()
{
	std::vector<std::string> words;
	int input;
	readWords(words);
	
	printMessage("Welcome to the Scrabble Junior Board Builder Tool.");
	printMessage("Creating a Board is easy, don't worry. Just follow the instructions and answer all of the questions.");
	waitForKey();
	clearScreen();
	printMessage("What are the number of columns on the board?", Color::WHITE, Color::BLACK);
	while (!checkInput(input) || input < 0 || input > 20) {
		clearScreen();
		printMessage("Input was invalid, please try again.", RED, BLACK);
		printMessage("What are the number of columns on the board?", Color::WHITE, Color::BLACK);
	}

	
	return 0;
}
