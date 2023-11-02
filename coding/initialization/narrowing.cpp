#include <iostream>

#pragma GCC diagnostic ignored "-Wliteral-conversion"
#pragma GCC diagnostic ignored "-Wconstant-conversion"

void foo() {
    int i = 20.10;  // -Wliteral-conversion
    unsigned int ui = -10;
    short s = 2147483647;  // -Wconstant-conversion

    // 20 4294967286 -1
    std::cout << i << " " << ui << " " << s << std::endl;
}

int main() {
    foo();
    return 0;
}