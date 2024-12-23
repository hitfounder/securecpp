#include <cstring>
#include <iostream>
#include <string_view>
#include <string>

void print_legths(std::string_view str) {
    std::cout << "\""<< str <<"\"" << std::endl;
    std::cout
        << "string view actual length: "
        << str.length()
        << std::endl;
    std::cout
        << "strlen with string view: "
        << std::strlen(str.data())
        << std::endl;
    std::cout
        << "strlen with string: "
        << std::strlen(std::string(str).c_str())
        << std::endl;
}

int main() {
    std::string_view str{"Hello World"};
    print_legths(str);
    str.remove_suffix(5);
    print_legths(str);
    print_legths(str.substr(5));
    return 0;
}