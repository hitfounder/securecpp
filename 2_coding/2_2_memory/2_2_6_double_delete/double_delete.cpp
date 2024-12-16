#include <algorithm>
#include <assert.h>

class A {
public:
    A() : val(new int) {}
    ~A() {
        delete val;
    }
private:
    int* val{nullptr};
};

class AFixed {
public:
    AFixed() : val(new int) {}
    AFixed(const AFixed& other) {
        assert(other.val);
        val = new int(*other.val);
    }
    AFixed& operator=(const AFixed& other) {
        AFixed temp(other);
        std::swap(val, temp.val);
        return *this;
    }
    AFixed(AFixed&& other) noexcept {
        val = other.val;
        other.val = nullptr;
    }
    AFixed& operator=(AFixed&& other) noexcept {
        delete val;
        val = other.val;
        other.val = nullptr;
        return *this;
    }
    ~AFixed() {
        delete val;
    }
private:
    int* val{nullptr};
};

int main() {
    A a1, a2;
    a2 = a1;

    AFixed af1, af2;
    af2 = af1;
    return 0;
}
