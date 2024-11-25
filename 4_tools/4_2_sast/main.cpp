// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include <iostream>

int* test() {
    auto p{new int};
    *p = 100;
    return p;
}

int main() {
    auto ptr{test()};
    std::cout << *ptr;

    // ...

    ptr = 0;
    delete ptr;
    return 0;
}
