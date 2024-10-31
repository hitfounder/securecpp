#include <iostream>
#include <vector>

std::vector<int> GetVals() {
    return {1, 2, 3};
}
int main() {
    const auto begin{GetVals().begin()};
    std::cout << *begin << std::endl;
    return 0;
}