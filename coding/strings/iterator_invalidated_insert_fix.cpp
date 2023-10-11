#include <iostream>
#include <string>

int main() {
    std::string hello{"Hello"};
    std::string world{"Woooooooooorld"};

    world.insert(world.end(), std::begin(hello), std::end(hello));
    world.insert(world.begin(), std::begin(hello), std::end(hello));
    std::cout << world;
    return 0;
}