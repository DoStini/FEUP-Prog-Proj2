#include <iostream>
#include <vector>

using std::cout, std::cin, std::vector;












int main() {
    vector<char> chars = {'a', 'b', 'c'};
    chars.erase(chars.begin() + 1);
    for (auto charara:chars) {
        cout << charara;
    }
}