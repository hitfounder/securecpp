#include <iostream>
#include <vector>

#pragma GCC diagnostic ignored "-Wuninitialized"
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"

struct Bar {
    int i;
    int j;
};

struct SafeBar {
    SafeBar() : i(0), j(0) {}
    
    int i;
    int j;
};

struct SaferBar {
    int i = 0;
    int j = 0;
};

void fooDefaultInitization() {
    int i;
    char buff[10];
    Bar bar;

    // Undefined behavior
    // 917094401 ? 21847
    std::cout << i << " " << buff << " " << bar.i << std::endl;

    SafeBar safeBar;
    SaferBar saferBar;

    // OK
    // 0 0
    std::cout << safeBar.i << " " << saferBar.i << " " << std::endl;
}

void fooValueInitization() {
    int i{};
    char buff[10]{};
    Bar bar = Bar();
    char *buffDyn = new char[10]();

    // 0  0
    std::cout << i << " " << buff << " "<< bar.i << " " << buffDyn << std::endl;
    delete [] buffDyn;
}

void fooDirectInitization() {
    int i{1};
    char *c = new char('2');

    // 1 2
    std::cout << i << " " << *c << std::endl;
    delete c;
}

void fooCopyInitization() {
    int i = 1;
    char buff[10] = {'2', '3', '4'};

    // 1 234
    std::cout << i << " " << buff << std::endl;
}

void fooAgregateInitization() {
    Bar bar1{1,2};
    Bar bar2 = {3, 4};
    Bar bar3 = {.i = 5, .j = 6};
    Bar bar4 = {7};
    char buff[10] = {'8'};

    // 1 3 5 0 8
    std::cout << bar1.i << " " << bar2.i << " " << bar3.i << " " << bar4.j << " " << buff << std::endl;
}

int globalVal;
Bar globalBar;
char globalBuff[10];

void fooStaticInitization() {
    static int localStatic;
    static Bar localStaticBar;
    static char localStaticBuff[10];

    // 0 0 
    std::cout << globalVal << " " << globalBar.i << " " << globalBuff << std::endl;
    // 0 0 
    std::cout << localStatic << " " << localStaticBar.i << " " << localStaticBuff << std::endl;
}

void fooUniversalInitialization() {
    std::string s1(49, '2');
    std::string s2{49, '2'};
    // 2222222222222222222222222222222222222222222222222 12
    std::cout << s1 << " " << s2 << std::endl;
}

int main() {
    std::cout << "Default initization" << std::endl;
    fooDefaultInitization();

    std::cout << "Value initization" << std::endl;
    fooValueInitization();

    std::cout << "Direct initization" << std::endl;
    fooDirectInitization();

    std::cout << "Copy initization" << std::endl;
    fooCopyInitization();

    std::cout << "Agregate initization" << std::endl;
    fooAgregateInitization();

    std::cout << "Static initization" << std::endl;
    fooStaticInitization();

    std::cout << "Universal initialization" << std::endl;
    fooUniversalInitialization();
    return 0;
}