#include <iostream>
#include <thread>

void termination() {
    auto t{std::thread([](){})};
}

void terminationFixed() {
#if __cpp_lib_jthread >= 201911L
    auto t{std::jthread([](){})};
#else
    auto t{std::thread([](){})};
    t.join();
#endif
}

void joinAfterDetach() {
    auto t{std::thread([](){})};
    t.detach();
    t.join();
}

void joinAfterDetachFixed() {
    auto t{std::thread([](){})};
    t.detach();

    if (t.joinable()) {
        t.join();
    }
}

void unhandledException() {
    try
    {
        auto t{std::thread([](){
            throw std::runtime_error("Error");
        })};
        t.join();
    }
    catch(const std::runtime_error& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void unhandledExceptionFixed() {
    auto t{std::thread([](){
        try
        {
            throw std::runtime_error("Error");
        }
        catch(const std::runtime_error& e)
        {
            std::cerr << e.what() << std::endl;
        }
    })};
    t.join();
}

int main() {
    std::set_terminate([]()
    {
        std::cout << "Termination" << std::endl;
    });

    //termination();
    terminationFixed();

    //joinAfterDetach();
    joinAfterDetachFixed();

    //unhandledException();
    unhandledExceptionFixed();
    return 0;
}