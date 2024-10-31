#include <functional>
#include <iostream>
#include <memory>

int main () {
    std::function<void()> func;
    {
        auto ptr{std::make_shared<int>(100)};
        func = [&]() {
            std::cout << *ptr << std::endl;
        };
    }
    //...
    func();
    return 0;
}