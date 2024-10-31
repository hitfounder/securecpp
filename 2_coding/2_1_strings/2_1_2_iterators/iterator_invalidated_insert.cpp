#include <iostream>
#include <string>

int main() {
    std::string str{"hello"};
    const auto begin{str.begin()};
    const auto end(str.end());

    str.insert(end, 20, '+');
    str.insert(begin, 20, '-');
    std::cout << str << std::endl;
    return 0;
}