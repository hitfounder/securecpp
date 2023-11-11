#include <iostream>
#include <limits>

void wrapping() {
    constexpr unsigned int uiMax = std::numeric_limits<unsigned int>::max();
    constexpr unsigned int uiMin = std::numeric_limits<unsigned int>::min();
    std::cout << "unsigned int max: " << uiMax << " unsigned int min: " << uiMin << std::endl;
    std::cout << "Addition wrapping: " << uiMax + 1 << std::endl;
    std::cout << "Substraction wrapping: " << uiMin - 1 << std::endl;
    std::cout << "Multiplication wrapping: " << uiMax * 2 << std::endl;
}

void wrappingAdditionPrecondition(unsigned int a, unsigned int b) {
    if (std::numeric_limits<unsigned int>::max() - a < b) {
        throw std::runtime_error("Wrapping");
    }
    // unsigned int summ = a + b;
}

void wrappingAdditionPostcondition(unsigned int a, unsigned int b) {
    unsigned int summ = a + b;
    if (summ < a) {
        throw std::runtime_error("Wrapping");
    }
}

void wrappingSubstractingPrecondition(unsigned int a, unsigned int b) {
    if (a < b) {
        throw std::runtime_error("Wrapping");
    }
    // unsigned int diff = a - b;
}

void wrappingSubstractingPostcondition(unsigned int a, unsigned int b) {
    unsigned int diff = a - b;
    if (diff > a) {
        throw std::runtime_error("Wrapping");
    }
}

void wrappingMultiplicatingPrecondition(unsigned int a, unsigned int b) {
    if (a > std::numeric_limits<unsigned int>::max()/b) {
        throw std::runtime_error("Wrapping");
    }
    // unsigned int prod = a * b;
}

void wrappingMultiplicatingPostcondition(unsigned int a, unsigned int b) {
    static_assert(sizeof(unsigned long long) >= 2 * sizeof(unsigned int));
    unsigned long long prod =
        static_cast<unsigned long long>(a) * static_cast<unsigned long long>(b);
    if (prod > std::numeric_limits<unsigned int>::max()) {
        throw std::runtime_error("Wrapping");
    }
}

int main () {
    wrapping();
    return 0;
}