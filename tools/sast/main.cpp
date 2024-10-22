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
