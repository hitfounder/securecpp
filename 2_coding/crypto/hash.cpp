#include <functional>
#include <iostream>

int main() {
    std::cout << std::hash<std::string_view>{}("Hello World!") << std::endl;
    std::cout << std::hash<std::string_view>{}("World Hello!") << std::endl;

    // Hash for integer numbers is the same number
    std::cout << std::hash<int>{}(123) << std::endl;
    std::cout << std::hash<int>{}(456) << std::endl;

    // Hash for raw string is actualy a hash of pointer
    std::cout << std::hash<const char*>{}("Raw string") << std::endl;
}