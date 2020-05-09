#include "color.h"
#include "IO.h"
#include <string>

void getString(std::string &string) {
    std::getline(std::cin, string);
}

void getChar(char& input) {
    input = getchar();
    if(input != '\n' && input != EOF) std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
}

void printMessage(std::string message, std::string end) {
    std::cout << message << end;
}

void printMessage(std::string message, int fgColor, std::string end) {
    setColor(fgColor);
    std::cout << message << end;
    setColor(BLACK, WHITE);
}

void printMessage(std::string message, int fgColor, int bgColor, std::string end) {
    setColor(fgColor, bgColor);
    std::cout << message << end;
    setColor(BLACK, WHITE);
}

bool checkStop() {
    return std::cin.eof();
}

void clearScreen(short xPos = 0, short yPos = 0) {
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

void waitForKey() {
    printMessage("Press any key to continue...", BLACK, WHITE, "");
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

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setColor(unsigned int color)
{
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon, color);
}


void setColor(unsigned int color, unsigned int background_color)
{
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    if (background_color == BLACK)
        SetConsoleTextAttribute(hCon, color);
    else
        SetConsoleTextAttribute(hCon, color | background_color);
}

void replaceVisualChar(int x, int y, char letter, unsigned int fgColor, unsigned int bgColor){
    gotoxy(x, y);
    setColor(fgColor, bgColor);
    std::cout << letter;
  //  gotoxy(100, 100);
    setColor(WHITE, BLACK);
}

void cleanLine(int x, int y, int nChar){
    gotoxy(x, y);
    for (int i = 0; i < nChar; ++i) std::cout << ' ';
}

void placePlayer(Player &player){
    cleanLine(player.getX(), player.getY(), 40);
    gotoxy(player.getX(), player.getY());
    std::cout << player.getName() << "'s score: " << player.getScore();
    cleanLine(player.getX(), player.getY() + 1, 40);
    gotoxy(player.getX(), player.getY() + 1);
    std::cout << "This is your board: ";
    player.showTiles();
}