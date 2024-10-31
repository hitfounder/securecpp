#include <iostream>

struct A {
    int a{123};
};

int main() {
    alignas(A) char alignedSpace[sizeof(A) + 1];

    A *a = new (&alignedSpace[1]) A;
    std::cout << "Aligned address: " << static_cast<void*>(alignedSpace) << std::endl;
    std::cout << "Object address: " << a << std::endl;
    std::cout << "Data: " << a->a << std::endl;
    // ..
    a->~A();
    return 0;
}