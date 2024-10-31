#include <iostream>
#include <string>

int main() {
    std::string str{"hello"};

    str.insert(str.end(), 20, '+');
    str.insert(str.begin(), 20, '-');
    std::cout << str << std::endl;
    return 0;
}