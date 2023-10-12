#include <iostream>
#include <string>

int main() {
    std::string str{"hello"};
    for (auto it = str.begin(); it != str.end(); ++it) {
        if (*it == 'l')
            str.erase(it);
    }
    std::cout << str << std::endl;
    return 0;
}