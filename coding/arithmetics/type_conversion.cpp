#include <boost/type_index.hpp>
#include <iostream>

void IntPromotionInt() {
    constexpr unsigned char a{std::numeric_limits<unsigned char>::max()};
    constexpr unsigned char b{2};
    constexpr unsigned char c{100};
    constexpr auto res{(a * b) / c};
    // 5 int
    std::cout << res << " " << boost::typeindex::type_id_runtime(res).pretty_name() << std::endl;
}

void UsualArithmeticConversion() {
    // 4 294 967 295
    constexpr unsigned int a{std::numeric_limits<unsigned int>::max()};
    constexpr unsigned long long b{2};
    constexpr unsigned short c{10};
    constexpr auto res{(a * b) / c};
    // 858 993 459 unsigned long long
    std::cout << res << " " << boost::typeindex::type_id_runtime(res).pretty_name() << std::endl;
}

void SignedUnsignedConversion() {
    constexpr int a{std::numeric_limits<int>::max()};
    constexpr unsigned int b{2};
    constexpr auto res{(a * b)};
    // 4 294 967 294 unsigned int
    std::cout << res << " " << boost::typeindex::type_id_runtime(res).pretty_name() << std::endl;
}

void SignedUnsignedOverflow() {
    // -2 147 483 648
    constexpr int a{std::numeric_limits<int>::min()};
    constexpr unsigned int b{2};
    constexpr auto res{(a * b)};
    // 0 unsigned int
    std::cout << res << " " << boost::typeindex::type_id_runtime(res).pretty_name() << std::endl;
}

int main() {
    IntPromotionInt();
    UsualArithmeticConversion();
    SignedUnsignedConversion();
    SignedUnsignedOverflow();
    return 0;
}