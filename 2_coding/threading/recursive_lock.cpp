#include <iostream>
#include <mutex>
#include <thread>

void RecursiveLockDeadlock() {
    std::mutex m;

    auto callback = [&m](){
        std::lock_guard lock(m);
    };

    auto t1{std::thread([&m, callback]() {
        std::lock_guard lock(m);
        callback();
    })};

    t1.join();
}

void RecursiveLock() {
    std::recursive_mutex m;

    auto callback = [&m](){
        std::lock_guard lock(m);
    };

    auto t1{std::thread([&m, callback]() {
        std::lock_guard lock(m);
        callback();
    })};

    t1.join();
}

int main() {
    //RecursiveLockDeadlock();
    RecursiveLock();
    return 0;
}