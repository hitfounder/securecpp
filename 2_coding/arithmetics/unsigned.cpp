#include <gtest/gtest.h>
#include <iostream>
#include <limits>

void wrapping() {
    constexpr unsigned int uiMax = std::numeric_limits<unsigned int>::max();
    constexpr unsigned int uiMin = std::numeric_limits<unsigned int>::min();
    // unsigned int max: 4294967295 unsigned int min: 0
    std::cout << "unsigned int max: " << uiMax << " unsigned int min: " << uiMin << std::endl;
    // Addition wrapping: 0
    std::cout << "Addition wrapping: " << uiMax + 1 << std::endl;
    // Substraction wrapping: 4294967295
    std::cout << "Substraction wrapping: " << uiMin - 1 << std::endl;
    // Multiplication wrapping: 4294967294
    std::cout << "Multiplication wrapping: " << uiMax * 2 << std::endl;
}

unsigned int wrappingAdditionPrecondition(unsigned int a, unsigned int b) {
    if (std::numeric_limits<unsigned int>::max() - a < b) {
        throw std::runtime_error("Wrapping");
    }
    return a + b;
}

unsigned int wrappingAdditionPostcondition(unsigned int a, unsigned int b) {
    const unsigned int summ = a + b;
    if (summ < a) {
        throw std::runtime_error("Wrapping");
    }
    return summ;
}

unsigned int wrappingSubstractingPrecondition(unsigned int a, unsigned int b) {
    if (a < b) {
        throw std::runtime_error("Wrapping");
    }
    return a - b;
}

unsigned int wrappingSubstractingPostcondition(unsigned int a, unsigned int b) {
    const unsigned int diff = a - b;
    if (diff > a) {
        throw std::runtime_error("Wrapping");
    }
    return diff;
}

unsigned int wrappingMultiplicatingPrecondition(unsigned int a, unsigned int b) {
    if (a > std::numeric_limits<unsigned int>::max() / b) {
        throw std::runtime_error("Wrapping");
    }
    return a * b;
}

unsigned int wrappingMultiplicatingPostcondition(unsigned int a, unsigned int b) {
    static_assert(sizeof(unsigned long long) >= 2 * sizeof(unsigned int));
    const unsigned long long prod =
        static_cast<unsigned long long>(a) * static_cast<unsigned long long>(b);
    if (prod > std::numeric_limits<unsigned int>::max()) {
        throw std::runtime_error("Wrapping");
    }
    return static_cast<unsigned int>(prod);
}

int main () {
    wrapping();

    EXPECT_EQ(wrappingAdditionPrecondition(1, 2), 3);
    EXPECT_EQ(wrappingAdditionPostcondition(1, 2), 3);
    EXPECT_THROW(wrappingAdditionPrecondition(std::numeric_limits<unsigned int>::max(), 1), std::runtime_error);
    EXPECT_THROW(wrappingAdditionPrecondition(1, std::numeric_limits<unsigned int>::max()), std::runtime_error);
    EXPECT_THROW(wrappingAdditionPostcondition(std::numeric_limits<unsigned int>::max(), 1), std::runtime_error);
    EXPECT_THROW(wrappingAdditionPostcondition(1, std::numeric_limits<unsigned int>::max()), std::runtime_error);

    EXPECT_EQ(wrappingSubstractingPrecondition(2, 1), 1);
    EXPECT_EQ(wrappingSubstractingPostcondition(2, 1), 1);
    EXPECT_THROW(wrappingSubstractingPrecondition(1, 2), std::runtime_error);
    EXPECT_THROW(wrappingSubstractingPostcondition(1, 2), std::runtime_error);

    EXPECT_EQ(wrappingMultiplicatingPrecondition(2, 2), 4);
    EXPECT_EQ(wrappingMultiplicatingPostcondition(2, 2), 4);
    EXPECT_THROW(wrappingSubstractingPrecondition(std::numeric_limits<unsigned int>::max(), 2), std::runtime_error);
    EXPECT_THROW(wrappingSubstractingPrecondition(2, std::numeric_limits<unsigned int>::max()), std::runtime_error);
    EXPECT_THROW(wrappingSubstractingPostcondition(std::numeric_limits<unsigned int>::max(), 2), std::runtime_error);
    EXPECT_THROW(wrappingSubstractingPostcondition(2, std::numeric_limits<unsigned int>::max()), std::runtime_error);
    return 0;
}