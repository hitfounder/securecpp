#include <iostream>
#include <mutex>
#include <thread>

void MultipleLockDeadlock() {
    std::mutex m1;
    std::mutex m2;

    auto t1{std::thread([&m1, &m2]() {
        std::lock_guard lock1(m1);
        std::lock_guard lock2(m2);
    })};
    auto t2{std::thread([&m1, &m2]() {
        std::lock_guard lock2(m2);
        std::lock_guard lock1(m1);
    })};

    t1.join();
    t2.join();
}

void MultipleLock() {
    std::mutex m1;
    std::mutex m2;

    auto t1{std::thread([&m1, &m2]() {
        std::scoped_lock lock(m1, m2);
    })};
    auto t2{std::thread([&m1, &m2]() {
        std::scoped_lock lock(m2, m1);
    })};

    t1.join();
    t2.join();
}

int main() {
    int i = 0;
    // Deadlock could happen at eny time, so need a lot of tries 
    while(true) {
        MultipleLock();
        //MultipleLockDeadlock();
        std::cout << i++ << std::endl;
    }
    return 0;
}