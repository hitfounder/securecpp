#include <cstdlib>
#include <iostream>
#include <string>
  
int main() {
    const std::string tmp{std::getenv("TMP")};
    if (!tmp.empty()) {
        std::cout << tmp;
    }
    return 0;
}