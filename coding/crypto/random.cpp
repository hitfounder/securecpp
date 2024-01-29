#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>

void Rand() {
    std::srand(std::time(nullptr));
    std::cout << "rand values on [0, " << RAND_MAX << "]: " << std::endl;
    for (int i = 0; i < 10; ++i) {
        std::cout << std::rand() << std::endl;
    }
}

void Random() {
    std::uniform_int_distribution<int> distribution(0, RAND_MAX);
    std::random_device rd;
    std::mt19937 engine(rd());

    std::cout << "mt19937 values on [0, " << RAND_MAX << "]: " << std::endl;
    for (int i = 0; i < 10; ++i) {
        std::cout << distribution(engine) << std::endl;
    }
}

int main() {
    Rand();
    Random();
    return 0;
}