#include <string>

void foo(std::string& str) {
    str.back() = '!';
}

int main() {
    std::string str{"hello"};
    foo(str);
    return 0;
}