#include <cstdlib>
#include <new>

struct A {
    static void *operator new(std::size_t size) noexcept {
        return std::malloc(size);
    }
    static void operator delete(void *ptr) noexcept {
        std::free(ptr);
    }
};

int main() {
    A* a{new A};
    ::delete a;
    return 0;
}
