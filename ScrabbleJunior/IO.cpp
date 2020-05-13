#include "color.h"
#include "IO.h"
#include <string>




void waitForKey() {
    std::cout <<"Press any key to continue...";
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

