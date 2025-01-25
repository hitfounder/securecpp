#include <algorithm>
#include <iostream>
#include <string>

void fix() {
    std::string str{"hello"};
    str.erase(std::remove(str.begin(), str.end(), 'l'), str.end());
    std::cout << str << std::endl;
}

void fixCpp20() {
    std::string str{"hello"};
    std::erase(str, 'l');
    std::cout << str << std::endl;
}

int main() {
    fix();
    fixCpp20();
    return 0;
}