#include <iostream>
#include <vector>

#pragma GCC diagnostic ignored "-Wuninitialized"
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#pragma GCC diagnostic ignored "-Wpointer-bool-conversion"

struct Bar {
    int i;
    int j;
};

struct UnsafeBar {
    UnsafeBar() {}
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

void DefaultInitization() {
    int i;
    char buff[10];
    Bar bar;

    // UB
    // 917094401 ? 21847
    std::cout << i << " " << buff << " " << bar.i << std::endl;

    SafeBar safeBar;
    SaferBar saferBar;

    // OK
    // 0 0
    std::cout << safeBar.i << " " << saferBar.i << " " << std::endl;
}

void ValueInitization() {
    int i{};
    char buff[10]{};
    Bar bar = Bar();
    char *buffDyn = new char[10]();
    UnsafeBar unsafeBar{};

    // 0  0
    std::cout << i << " " << buff << " "<< bar.i << " " << buffDyn << std::endl;
    // UB
    // 1031968064 32686
    std::cout << unsafeBar.i << " " << unsafeBar.j << std::endl;
    delete [] buffDyn;
}

void VexingParse() {
    int i();

    // 1 - address of function will be implicitly converted to bool
    std::cout << i << std::endl;
}

void DirectInitization() {
    int i{1};
    char *c = new char('2');

    // 1 2
    std::cout << i << " " << *c << std::endl;
    delete c;
}

void CopyInitization() {
    int i = 1;
    char buff[10] = {'2', '3', '4'};

    // 1 234
    std::cout << i << " " << buff << std::endl;
}

void AgregateInitization() {
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

void StaticInitization() {
    static int localStatic;
    static Bar localStaticBar;
    static char localStaticBuff[10];

    // 0 0 
    std::cout << globalVal << " " << globalBar.i << " " << globalBuff << std::endl;
    // 0 0 
    std::cout << localStatic << " " << localStaticBar.i << " " << localStaticBuff << std::endl;
}

void UniversalInitialization() {
    std::string s1(49, '2');
    std::string s2{49, '2'};
    // 2222222222222222222222222222222222222222222222222 12
    std::cout << s1 << " " << s2 << std::endl;
}

void AutoInitialization() {
    auto i = 10;
    auto ui = 100u;
    auto s = std::string{"string"};

    auto print = [](auto val) {
        std::cout << val << " " << typeid(val).name() << std::endl;
    };

    print(i);
    print(ui);
    print(s);

    auto oops = {1000};
    // initializer_list
    std::cout << typeid(oops).name() << std::endl;
}

int main() {
    std::cout << "Default initization" << std::endl;
    DefaultInitization();

    std::cout << "Value initization" << std::endl;
    ValueInitization();

    std::cout << "Vexing parse" << std::endl;
    VexingParse();

    std::cout << "Direct initization" << std::endl;
    DirectInitization();

    std::cout << "Copy initization" << std::endl;
    CopyInitization();

    std::cout << "Agregate initization" << std::endl;
    AgregateInitization();

    std::cout << "Static initization" << std::endl;
    StaticInitization();

    std::cout << "Universal initialization" << std::endl;
    UniversalInitialization();

    std::cout << "Auto initialization" << std::endl;
    AutoInitialization();
    return 0;
}