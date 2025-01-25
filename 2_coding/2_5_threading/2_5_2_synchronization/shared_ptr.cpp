#include <algorithm>
#include <memory>
#include <vector>
#include <thread>
#include <iostream>

struct Data {
    int m_a{0};
    int m_b{0};
    explicit Data(int a, int b) : m_a{a}, m_b(b) {};
};

void SharedPtrValTest() {
    auto gData{std::make_shared<Data>(1, 2)};

    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back(std::thread([gData](){
            std::shared_ptr<Data> local{gData};
            local = std::make_shared<Data>(3, 4);
        }));
    }

    std::for_each(std::begin(threads), std::end(threads),
    [](std::thread& t){
        t.join();
    });
}

void SharedPtrRefTest() {
#if __cpp_lib_atomic_shared_ptr >= 201711L
    std::atomic<std::shared_ptr<Data>> gData{std::make_shared<Data>(1, 2)};
#else
    auto gData{std::make_shared<Data>(1, 2)};
#endif

    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back(std::thread([&gData](){
#if __cpp_lib_atomic_shared_ptr >= 201711L
            gData = std::make_shared<Data>(3, 4);
#else
            std::atomic_store(&gData, std::make_shared<Data>(3, 4));
#endif
        }));
    }

    std::for_each(std::begin(threads), std::end(threads),
    [](std::thread& t){
        t.join();
    });
}


int main() {
    SharedPtrValTest();
    SharedPtrRefTest();
    return 0;
}