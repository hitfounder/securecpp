#include <mutex>
#include <stack>
#include <thread>
#include <vector>

template <typename T>
class ThreadSafeStack {
public:
    void push(const T& val) {
        std::lock_guard lock(m_lock);
        m_stack.push(val);
    }

    T top() const {
        std::lock_guard lock(m_lock);
        return m_stack.top();
    }

    void pop() {
        std::lock_guard lock(m_lock);
        m_stack.pop();
    }

    bool empty() {
        std::lock_guard lock(m_lock);
        return m_stack.empty();
    }

    bool checkAndPop() {
        std::lock_guard lock(m_lock);
        if (!m_stack.empty()) {
            m_stack.pop();
            return true;
        }
        return false;
    }

private:
    std::stack<T> m_stack;
    mutable std::mutex m_lock;
};

int main() {
    ThreadSafeStack<int> gStack;

    auto test = [&gStack]() {
        for (int i = 0; i < 10; ++i) {
            gStack.push(i);
        }
        //while (!gStack.empty()) {
        //    gStack.pop();
        //}
        while (gStack.checkAndPop()) {}
    };

    std::vector<std::thread> threads;
    for (int i = 0; i < 1000; ++i) {
        threads.emplace_back(std::thread(test));
    }

    std::for_each(std::begin(threads), std::end(threads),
    [](std::thread& t){
        t.join();
    });

    return 0;
}