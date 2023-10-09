#include <cstdlib>
#include <iostream>
#include <string>
  
int main() {
    const char* const tmpEnv{std::getenv("TMP")};
    const std::string tmp{tmpEnv ? tmpEnv : ""};
    if (!tmp.empty()) {
        std::cout << tmp;
    }
    return 0;
}