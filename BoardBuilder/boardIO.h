#pragma once
#include<iostream>
#include <windows.h>
#include<string>
#include <limits>

#define XBEGMENU 70
#define YBEGMENU 15
#define YSPACING 4

/**
 * Function that prompts the user for input.
 * Checks if input is valid, allows only input without spaces and in the correct type.
 * Doesn't allow for the EOF character to be input, allowing for input to continue.
 *
 * @tparam T the type of data to be input
 * @param[out] input The variable where the input is stored.
 * @param[in] delimiter The last char must be at the end of the buffer
 *
 * @returns a boolean that indicates if a value was input successfully.
 */
template <typename T>
bool checkInput(T& input, char delimiter = '\n') {
	std::cin >> input;

	if (std::cin.eof()) {
		std::cin.clear();
		return false;
	}
	else if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		return false;
	}
	else if (std::cin.peek() != delimiter) {
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		return false;
	}

	std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

	return true;
}

/**
 * Function that prompts the user for input.
 * Checks if input is valid, allows only input without spaces and in the correct type.
 * Ignores the EOF character, allowing it to be input.
 *
 * @tparam T the type of data to be input
 * @param[out] input The variable where the input is stored.
 * @param[in] delimiter The last char must be at the end of the buffer
 *
 * @returns a boolean that indicates if a value was input successfully.
 */
template <typename T>
bool checkInputOrSTOP(T& input, char delimiter = '\n') {
	std::cin >> input;

	if (std::cin.eof()) {
		return true;
	}
	else if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		return false;
	}
	else if (std::cin.peek() != delimiter) {
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		return false;
	}

	std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

	return true;
}

void getString(std::string& string);
void getChar(char& input);
void printMessage(std::string message, std::string end = "\n");
void printMessage(std::string message, int bgColor, int fgColor, std::string end = "\n");
bool checkStop();
//void clearScreen();
void waitForKey();
std::string stringToLower(std::string str);
std::string stringToUpper(std::string str);
void gotoxy(int x, int y);
void clearScreen(short xPos = 0, short yPos = 0);