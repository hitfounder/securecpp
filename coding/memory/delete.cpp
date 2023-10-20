#include <cstdlib>
#include <new>

struct A {
    static void *operator new(std::size_t size) noexcept(true) {
        return std::malloc(size);
    }

    static void operator delete(void *ptr) noexcept(true) {
        std::free(ptr);
    }
};

int main() {
    A* a{new A};
    ::delete a;
    return 0;
}
