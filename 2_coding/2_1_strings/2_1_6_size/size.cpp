#include <iostream>
#include <string>

#define COUNTOF_C(arr) (sizeof(arr) / sizeof(arr[0]))

template <typename T, size_t N>
char (&ArraySizeHelper(T (&array)[N]))[N];
#define COUNTOF_CPP(array) (sizeof(ArraySizeHelper(array)))

template <typename T, size_t N>
constexpr size_t countof(T (&)[N]) noexcept
{
 return N;
}

template <typename Cont>
constexpr auto countof(const Cont &cont) noexcept(noexcept(cont.size()))
    -> decltype(cont.size())
{
  return cont.size();
}

int main() {
    {
        char str[] {"Hello world"};
        std::cout << "Length of C-string \"" << str << "\"" << std::endl;
        std::cout << "COUNTOF_C: " << COUNTOF_C(str) << std::endl;
        std::cout << "COUNTOF_CPP: " <<COUNTOF_CPP(str) << std::endl;
        std::cout << "countof: "<< countof(str) << std::endl;
    }

    {
        std::string str{"Hello world"};
        std::cout << "Length of std::string \"" << str << "\"" << std::endl;
        std::cout << "COUNTOF_C: " << COUNTOF_C(str) << std::endl;
        // Compilation error
        // std::cout << "COUNTOF_CPP: " << COUNTOF_CPP(str) << std::endl;
        std::cout << "countof: " << countof(str) << std::endl;
        std::cout << "size: " << str.size() << std::endl;
        std::cout << "std::size: " << std::size(str) << std::endl;
    }
    return 0;
}