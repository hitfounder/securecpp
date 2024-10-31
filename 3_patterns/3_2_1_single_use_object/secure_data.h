#pragma once

#include "memzero.h"

#include <cstdint>
#include <iostream>
#include <vector>

template <typename T>
struct SecureAllocator
{
    using value_type = T;

    SecureAllocator() = default;
    template <class U>
    SecureAllocator(const SecureAllocator<U> &) {}

    T *allocate(std::size_t n)
    {
        return m_allocator.allocate(n);
    }
    void deallocate(T *ptr, std::size_t n)
    {
        memzero(ptr, n);
        m_allocator.deallocate(ptr, n);
    }

private:
    std::allocator<T> m_allocator;
};

template <typename T, typename U>
inline bool operator==(const SecureAllocator<T> &, const SecureAllocator<U> &)
{
    return true;
}

template <typename T, typename U>
inline bool operator!=(const SecureAllocator<T> &a, const SecureAllocator<U> &b)
{
    return !(a == b);
}

using SecureData = std::vector<char, SecureAllocator<char>>;

std::ostream& operator<< (std::ostream& stream, const SecureData&)
{
    stream << "*****";
    return stream;
}
