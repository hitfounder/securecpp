#include <memory>

int main() {
    std::shared_ptr<int> fault{new int[10]};
    std::shared_ptr<int[]> fixed{new int[10]};
#if __cpp_lib_shared_ptr_arrays >= 201707L
    const auto betterFixedShared{std::make_shared<int[]>(10)};
#endif

    std::unique_ptr<int[]> fixedUP{new int[10]};
    const auto betterFixedUP{std::make_unique<int[]>(10)};
    return 0;
}