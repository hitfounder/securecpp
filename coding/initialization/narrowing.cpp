#include <gsl/narrow>
#include <iostream>

#pragma GCC diagnostic ignored "-Wliteral-conversion"
#pragma GCC diagnostic ignored "-Wconstant-conversion"

void foo() {
    int i = 20.10;  // Warning: -Wliteral-conversion
    unsigned int ui = -10;
    short s = 2147483647;  // Warning: -Wconstant-conversion

    // 20 4294967286 -1
    std::cout << i << " " << ui << " " << s << std::endl;
}

void bar() {
   /*
    // Error: -Wc++11-narrowing
    int i{20.10};
    unsigned int ui{-10};
    short s{2147483647};

    // i value could not be checked on compile time, so -Wc++11-narrowing
    int i{10};
    unsigned int ui{i};
   */

    // ci value could be checked on compile time, so conversion is acceptable
    constexpr int ci{30};
    unsigned int ui{ci};
    short s{ci};

    // 30 30 30
    std::cout << ci << " " << ui << " " << s << std::endl;
}

void qux() {
    float f{20};
    int i1 {static_cast<int>(f)};
    int i2 {gsl::narrow_cast<int>(f)};
    int i3 {gsl::narrow<int>(f)};

    // 20 20 20
    std::cout << i1 << " " << i2  << " " << i3 << std::endl;

    float f2{20.30};
    // Exception: gsl::narrowing_error
    int i4 {gsl::narrow<int>(f2)};
    (void) i4;
}

int main() {
    foo();
    bar();
    qux();
    return 0;
}