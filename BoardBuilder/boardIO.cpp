#include "color.h"
#include "boardIO.h"
#include <iostream>
#include <string>
#include <sstream>


/**
 * Set color and background color to be used with cout
 *
 * @param color
 * @param background_color
 */
void setColor(unsigned int color, unsigned int background_color)
{
	color = COLOR[color].second;
	background_color = COLOR[background_color].first;
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon, color | background_color);
}

void getString(std::string &string) {
	std::getline(std::cin, string);
}

/**
 * Function that prompts the user for the input of a single char.
 * Reads only the first char input to the buffer, all else is deleted from the buffer.
 * Allows the EOF character.
 *
 * @param[out] input The variable where the input is stored.
 */
void getChar(char& input) {
	input = getchar();
	if(input != '\n' && input != EOF) std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
}

void printMessage(std::string message, std::string end) {
	std::cout << message << end;
}

void printMessage(std::string message, int bgColor, int fgColor, std::string end) {
	setColor(fgColor, bgColor);
	std::cout << message << end;
	setColor(WHITE, BLACK);
}

bool checkStop() {
	return std::cin.eof();
}

void waitForKey() {
	printMessage("Press any key to continue...", WHITE, BLACK, "");
	std::cin.get();
}

std::string stringToLower(std::string str) {
	std::string::iterator it;
	std::string newCopy = str;

	for (it = newCopy.begin(); it != newCopy.end(); it++) {
		(*it) = tolower((*it));
	}

	return newCopy;
}

std::string stringToUpper(std::string str) {
	std::string::iterator it;
	std::string newCopy = str;

	for (it = newCopy.begin(); it != newCopy.end(); it++) {
		(*it) = toupper((*it));
	}

	return newCopy;
}

/**
 * Function to put the console cursor in a specified position
 *
 * @param x X position
 * @param y Y position
 */
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

/**
 * Clears the screen from a specified position.
 *
 * @param xPos, yPos Coordinates for the upper left corner.
 */
void clearScreen(short xPos, short yPos) {
	COORD coordScreen = { xPos, yPos }; // upper left corner
	DWORD cCharsWritten;
	DWORD dwConSize;
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hCon, &csbi);
	dwConSize = (csbi.dwSize.X - xPos) * (csbi.dwSize.Y - yPos);
	// fill with spaces
	FillConsoleOutputCharacter(hCon, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
	GetConsoleScreenBufferInfo(hCon, &csbi);
	FillConsoleOutputAttribute(hCon, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
	// cursor to upper left corner
	SetConsoleCursorPosition(hCon, coordScreen);
}

