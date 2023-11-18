#include <gtest/gtest.h>
#include <iostream>
#include <limits>

void overflow() {
    constexpr int iMax = std::numeric_limits<int>::max();
    constexpr int iMin = std::numeric_limits<int>::min();

    // int max: 2147483647 int min: -2147483648
    std::cout << "int max: " << iMax << " int min: " << iMin << std::endl;
    // Addition overflow: -2147483648
    std::cout << "Addition overflow: " << iMax + 1 << std::endl;
    // Substraction overflow: 2147483647
    std::cout << "Substraction overflow: " << iMin - 1 << std::endl;
    // Multiplication overflow: -2
    std::cout << "Multiplication overflow: " << iMax * 2 << std::endl;
    // Division overflow: 1672400991 ?
    std::cout << "Division overflow: " << iMin / -1 << std::endl;
}

int overflowAddition(int a, int b) {
    if ((b > 0 && a > std::numeric_limits<int>::max() - b) ||
        (b < 0 && a < std::numeric_limits<int>::min() - b)) {
        throw std::runtime_error("Overflow");
    }
    return a + b;
}

int overflowSubstraction(int a, int b) {
    if ((b > 0 && a < std::numeric_limits<int>::min() + b) ||
        (b < 0 && a > std::numeric_limits<int>::max() + b)) {
        throw std::runtime_error("Overflow");
    }
    return a - b;
}

int main () {
    overflow();

    EXPECT_EQ(overflowAddition(1, 2), 3);
    EXPECT_EQ(overflowAddition(std::numeric_limits<int>::min(), std::numeric_limits<int>::max()), -1);
    EXPECT_THROW(overflowAddition(std::numeric_limits<int>::max(), 1), std::runtime_error);
    EXPECT_THROW(overflowAddition(1, std::numeric_limits<int>::max()), std::runtime_error);
    EXPECT_THROW(overflowAddition(std::numeric_limits<int>::min(), -1), std::runtime_error);
    EXPECT_THROW(overflowAddition(-1, std::numeric_limits<int>::min()), std::runtime_error);

    EXPECT_EQ(overflowSubstraction(2, 1), 1);
    EXPECT_THROW(overflowSubstraction(std::numeric_limits<int>::min(), 1), std::runtime_error);
    EXPECT_THROW(overflowSubstraction(std::numeric_limits<int>::max(), -1), std::runtime_error);

    return 0;
}