#include <alloca.h>
#include <array>
#include <cstddef>
#include <iostream>

void funcAlloca(std::size_t size) {
    char* buff{static_cast<char*>(alloca(size))};
    std::cout << static_cast<void*>(buff) << std::endl;
}

void funcVLA(std::size_t size) {
    std::array<int, size> vals;
    (void) vals;
    {
        char buff[size];
        std::cout << static_cast<void*>(buff) << std::endl;
    }
    // Here buff will be destroyed
}

int main() {
    funcAlloca(100);
    funcVLA(100);
    return 0;
}