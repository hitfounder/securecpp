#include <string>

int main() {
    std::string hello{"Hello"};
    std::string world{"Woooooooooorld"};

    const auto begin{world.begin()};
    const auto end(world.end());

    world.insert(end, std::begin(hello), std::end(hello));
    world.insert(begin, std::begin(hello), std::end(hello));
    return 0;
}