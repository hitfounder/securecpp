#include <iostream>

struct A {
    // ...
};

int main() {
    alignas(A) char space[sizeof(A)];
    A *a = new (&space) A;
    // ..
    delete a;
    return 0;
}