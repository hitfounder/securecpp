#include <iostream>

extern int a;
int b = a;

extern int safeA;
int safeB = safeA;

int main() {
    // UB
    // a=100 b=0
    // a=100 b=100
    std::cout << "a=" << a << " b=" << b << std::endl;

    // OK
    // safeA=100 safeB=100
    std::cout << "safeA=" << safeA << " safeB=" << safeB << std::endl;
    return 0;
}