#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>

int main() {
    // Only 14 symbols, so string is allocated on stack
    std::string str{"11111111111111"};

    // Save iterator pointed to begin (contains stack address)
    auto begin{str.begin()};

    // Add more symbols, so string is reallocated to heap
    str.append("22222222222");

    // Input data is copied to dangling pointer, this causes stack overflow
    std::copy(std::istream_iterator<char>(std::cin),
              std::istream_iterator<char>(),
              std::inserter(str, begin));
    return 0;
}