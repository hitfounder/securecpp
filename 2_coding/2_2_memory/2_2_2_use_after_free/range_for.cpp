#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> GetVector() {
  return { "str1", "str2" };
}

int main() {
    for (const auto& val : GetVector().front()) {
        std::cout << val << std::endl; 
    }
    return 0;
}
