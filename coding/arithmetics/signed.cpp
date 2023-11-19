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

int overflowMultiplicationPrecondition(int a, int b) {
    if (a > 0) {
        if (b > 0) {
            if (a > (std::numeric_limits<int>::max() / b)) {
               throw std::runtime_error("Overflow");
            }
        } else {
            if (b < (std::numeric_limits<int>::min() / a)) {
                throw std::runtime_error("Overflow");
            }
        }
    } else {
        if (b > 0) {
            if (a < (std::numeric_limits<int>::min() / b)) {
                throw std::runtime_error("Overflow");
            }
        } else {
            if ((a != 0) && (b < (std::numeric_limits<int>::max() / a))) {
                throw std::runtime_error("Overflow");
            }
        }
    }
    return a * b;
}

int overflowMultiplicationPostcondition(int a, int b) {
    static_assert(sizeof(long long) >= 2 * sizeof(int));

    const long long prod =
        static_cast<long long>(a) * static_cast<long long>(b);
    if (prod > std::numeric_limits<int>::max() ||
        prod < std::numeric_limits<int>::min()) {
        throw std::runtime_error("Overflow");
    }
    return static_cast<int>(prod);
}

int overflowDivision(int a, int b) {
    if (b == 0 || (a == std::numeric_limits<int>::min() && b == -1)) {
        throw std::runtime_error("Overflow");
    }
    return a / b;
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

    EXPECT_EQ(overflowMultiplicationPrecondition(2, 2), 4);
    // a > 0, b > 0
    EXPECT_THROW(overflowMultiplicationPrecondition(std::numeric_limits<int>::max(), 2), std::runtime_error);
    // a > 0, b < 0
    EXPECT_THROW(overflowMultiplicationPrecondition(std::numeric_limits<int>::max(), -2), std::runtime_error);
    // a < 0, b > 0
    EXPECT_THROW(overflowMultiplicationPrecondition(-std::numeric_limits<int>::max(), 2), std::runtime_error);
    // a < 0, b < 0
    EXPECT_THROW(overflowMultiplicationPrecondition(-std::numeric_limits<int>::max(), -2), std::runtime_error);

    EXPECT_EQ(overflowMultiplicationPostcondition(2, 2), 4);
    EXPECT_THROW(overflowMultiplicationPostcondition(std::numeric_limits<int>::max(), 2), std::runtime_error);
    EXPECT_THROW(overflowMultiplicationPostcondition(2, std::numeric_limits<int>::max()), std::runtime_error);

    EXPECT_EQ(overflowDivision(2, 2), 1);
    EXPECT_THROW(overflowDivision(std::numeric_limits<int>::min(), -1), std::runtime_error);
    EXPECT_THROW(overflowDivision(std::numeric_limits<int>::min(), 0), std::runtime_error);
    return 0;
}