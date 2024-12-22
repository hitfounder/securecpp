#include <string>

void change_last_symbol(std::string& str) {
    str.back() = '!';
}

int main() {
    std::string str{"hello"};
    change_last_symbol(str);
    return 0;
}