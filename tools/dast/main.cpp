#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    const bool heapOverflow{argc > 1 && argv[1] == std::string("heap_overflow")};

    // Small strings will be allocated at stack because of SSO.
    // Large strings are allocated at heap.
    // So we could select heap or stack overflow.
    std::string str(heapOverflow ? 100 : 5, 'H');
    const auto begin{str.begin()};
    const auto end(str.end());

    str.insert(end, 200, '+');
    str.insert(begin, 200, '-');  // Invalid iterator here, will be stack or heap overflow
    std::cout << str << std::endl;
    return 0;
}
