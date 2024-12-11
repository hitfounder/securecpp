#include <cstring>
#include <iostream>
#include <string_view>
#include <string>

void foo(std::string_view str) {
    std::cout << "string view actual length: " << str.length() << std::endl;
    std::cout << "strlen with string view: " << std::strlen(str.data()) << std::endl;
    std::cout << "strlen with string: " << std::strlen(std::string(str).c_str()) << std::endl;
}

int main() {
    std::string_view str{"Hello World"};
    foo(str);
    str.remove_suffix(5);
    foo(str);
    foo(str.substr(5));
    return 0;
}