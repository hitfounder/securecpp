#include <boost/type_index.hpp>
#include <iostream>

template <typename T>
void CoutSizeof() {
    std::cout << boost::typeindex::type_id<T>().pretty_name() << ": " << sizeof(T) << std::endl; 
}

int main() {
    CoutSizeof<unsigned char>();
    CoutSizeof<signed char>();
    CoutSizeof<signed short>();
    CoutSizeof<unsigned short>();
    CoutSizeof<int>();
    CoutSizeof<unsigned int>();
    CoutSizeof<long>();
    CoutSizeof<unsigned long>();
    CoutSizeof<long long>();
    CoutSizeof<unsigned long long>();
    CoutSizeof<float>();
    CoutSizeof<double>();
    CoutSizeof<long double>();
    CoutSizeof<char>();
    CoutSizeof<wchar_t>();
    CoutSizeof<bool>();
    CoutSizeof<size_t>();
    return 0;
}