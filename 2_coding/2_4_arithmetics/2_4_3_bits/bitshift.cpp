#include <gtest/gtest.h>
#include <iostream>
#include <limits>

#if __cplusplus >= 202002L
int ShiftLeftSigned(int a, int b) {
    if ((b < 0) ||
        b >= std::numeric_limits<int>::digits) {
        throw std::runtime_error("Overflow");
    }
    return a << b;
}

int ShiftRightSigned(int a, int b) {
    if ((b < 0) ||
        b >= std::numeric_limits<int>::digits) {
        throw std::runtime_error("Overflow");
    }
    return a >> b;
}
#else
int ShiftLeftSigned(int a, int b) {
    if ((a < 0) || (b < 0) ||
        b >= std::numeric_limits<int>::digits ||
        a > (std::numeric_limits<int>::max() >> b)) {
        throw std::runtime_error("Overflow");
    }
    return a << b;
}
#endif  // __cplusplus >= 202002L

unsigned int ShiftLeftUnsigned(unsigned int a, unsigned int b) {
    if (b >= std::numeric_limits<unsigned int>::digits) {
        throw std::runtime_error("Overflow");
    }
    return a << b;
}

int main() {
    EXPECT_THROW(ShiftLeftSigned(-1, -1), std::runtime_error);
    EXPECT_THROW(ShiftLeftSigned(0, -1), std::runtime_error);

#if __cplusplus >= 202002L
    EXPECT_EQ(ShiftLeftSigned(-1, 0), -1);
    EXPECT_EQ(ShiftLeftSigned(-1, 1), -2);
    EXPECT_EQ(ShiftLeftSigned(-1, 30), -1073741824);
#else
    EXPECT_THROW(ShiftLeftSigned(-1, 0), std::runtime_error);
#endif  // __cplusplus >= 202002L

    EXPECT_EQ(ShiftLeftSigned(0, 0), 0);
    EXPECT_EQ(ShiftLeftSigned(1, 30), 1073741824);
    EXPECT_THROW(ShiftLeftSigned(1, 31), std::runtime_error);
    EXPECT_EQ(ShiftLeftUnsigned(0, 0), 0);
    EXPECT_EQ(ShiftLeftUnsigned(1, 31), 2147483648);
    EXPECT_THROW(ShiftLeftUnsigned(1, 32), std::runtime_error);

#if __cplusplus >= 202002L
    EXPECT_EQ(ShiftRightSigned(-1, 0), -1);
    EXPECT_EQ(ShiftRightSigned(-1, 1), -1);
    EXPECT_EQ(ShiftRightSigned(1, 1), 0);
    EXPECT_THROW(ShiftRightSigned(1, -1), std::runtime_error);
    EXPECT_THROW(ShiftRightSigned(1, 31), std::runtime_error);
#endif  // __cplusplus >= 202002L
    return 0;
}