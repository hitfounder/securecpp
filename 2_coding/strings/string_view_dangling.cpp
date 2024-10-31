#include <iostream>
#include <string>
#include <string_view>

int main() {
    const std::string str{"Helloooooooooooooooooooooooo "};
    std::string_view sv{str + "World\n"};
    std::cout << sv;
    return 0;
}
