#include <cstdlib>
#include <gsl/pointers>
#include <iostream>
#include <string>

int main() {
    const char* const tmpEnv{std::getenv("TMP")};
    const std::string tmp{tmpEnv ? tmpEnv : ""};
    if (!tmp.empty()) {
        std::cout << tmp;
    }

    const std::string path{gsl::make_not_null(std::getenv("PATH"))};
    std::cout << path;
    return 0;
}