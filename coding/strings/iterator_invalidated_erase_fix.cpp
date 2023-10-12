#include <iostream>
#include <string>

int main() {
    std::string str{"hello"};
    str.erase(std::remove(str.begin(), str.end(), 'l'), str.end());
    std::cout << str << std::endl;
    return 0;
}