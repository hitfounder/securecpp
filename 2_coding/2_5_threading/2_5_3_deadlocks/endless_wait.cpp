#include <condition_variable>
#include <iostream>
#include <thread>

void WaitWithoutCondition() {
    std::condition_variable cv;
    std::mutex m;

    auto t1{std::thread([&cv, &m](){
        std::unique_lock ul(m);
        cv.wait(ul);
    })};

    auto t2{std::thread([&cv, &m](){
        std::unique_lock ul(m);
        cv.notify_all();
    })};

    t1.join();
    t2.join();
}

void WaitWithCondition() {
    std::condition_variable cv;
    std::mutex m;
    bool isOK{false};

    auto t1{std::thread([&cv, &m, &isOK](){
        std::unique_lock ul(m);
        cv.wait(ul, [&isOK](){return isOK;});
    })};

    auto t2{std::thread([&cv, &m, &isOK](){
        std::unique_lock ul(m);
        isOK = true;
        cv.notify_all();
    })};

    t1.join();
    t2.join();
}

int main() {
    int i = 0;
    // Deadlock could happen at eny time, so need a lot of tries 
    while(true) {
        WaitWithCondition();
        //WaitWithoutCondition();
        std::cout << i++ << std::endl;
    }
    return 0;
}