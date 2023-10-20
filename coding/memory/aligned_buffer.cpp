#include <iostream>

struct A {
    int a{123};
};

int main() {
    char i{0};  // This shifts stack alignment
    (void)i;  // Just to suppress unused variable warning

    char nonAlignedSpace[sizeof(A)];
    alignas(A) char alignedSpace[sizeof(A)];

    std::cout << "Non align address: " << static_cast<void*>(nonAlignedSpace) << std::endl;
    std::cout << "Aligned address: " << static_cast<void*>(alignedSpace) << std::endl;

    A *a = new (&nonAlignedSpace) A;
    std::cout << "Object address: " << a << std::endl;
    std::cout << a->a << std::endl;
    // ..
    a->~A();
    return 0;
}