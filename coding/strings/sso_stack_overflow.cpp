#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>

int main() {
    // String is allocated in stack
    std::string str{"11111111111111"};

    // Save iterator pointed to stack
    auto begin{str.begin()};
    // String is reallocated to heap
    str.append("22222222222");

    // Input data to dangling pointer causes stack overflow
    std::copy(std::istream_iterator<char>(std::cin),
              std::istream_iterator<char>(),
              std::inserter(str, begin));

    std::cout << str;
    return 0;
}