#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/type_index.hpp>
#include <cfenv>
#include <cmath>
#include <gtest/gtest.h>
#include <iostream>

#pragma STDC FENV_ACCESS ON

template <typename T>
void CoutDigits() {
    std::cout << boost::typeindex::type_id<T>().pretty_name() 
        << ", digits: " << std::numeric_limits<T>::digits10 
        << ", max_digits: " << std::numeric_limits<T>::max_digits10
        << ", size bytes: " << sizeof(T)
        << std::endl; 
}

void GetDigits() {
    CoutDigits<float>();
    CoutDigits<double>();
    CoutDigits<long double>();
}

template<typename T>
T NanInfWrapper(std::function<T ()> op) {
    const auto res{op()};
    if (std::isnan(res))
        throw std::runtime_error("Result is NaN");
    else if (std::isinf(res))
        throw std::runtime_error("Result is Infinity");
    return res;
}

template<typename T>
T MathErrWrapper(std::function<T ()> op) {
    if (math_errhandling & MATH_ERREXCEPT) {
        std::feclearexcept(FE_ALL_EXCEPT);
    }
    errno = 0;

    const auto res{op()};
    
    if ((math_errhandling & MATH_ERRNO) && errno != 0) {
        throw std::runtime_error(std::strerror(errno));
    }
    if ((math_errhandling & MATH_ERREXCEPT) && std::fetestexcept(FE_ALL_EXCEPT) != 0) {
        throw std::runtime_error("Math exception");
    }
    return res;
}

template<typename T>
T MathFullErrWrapper(std::function<T ()> op) {
    return MathErrWrapper<T>([op](){return NanInfWrapper<T>(op);});
}

void FloatsEquality() {
    constexpr float a{1.0};
    constexpr float b{3.0};
    constexpr float c{a / b};
    std::cout << "Direct equality: " << ((1.0/3.0) == c) << std::endl;
    std::cout << "Epsilon equality: " << (std::fabs(c - 1.0/3.0) < std::numeric_limits<float>::epsilon()) << std::endl;
}

void DoubleVsDecimal() {
    using Decimal50 = boost::multiprecision::cpp_dec_float_50;

    double valDouble{123456789.123456789};
    Decimal50 valDecimal{"123456789.123456789"};

    // Double: 123456789.123457
    std::cout << std::setprecision(std::numeric_limits<double>::digits10) << "Double: " << valDouble << std::endl;
    // Decimal: 123456789.123456789
    std::cout << std::setprecision(std::numeric_limits<Decimal50>::digits10) << "Decimal: " << valDecimal.str(50) << std::endl;
}

int main() {
    static_assert(std::numeric_limits<float>::is_iec559);
    static_assert(std::numeric_limits<double>::is_iec559);
    static_assert(std::numeric_limits<long double>::is_iec559);

    GetDigits();

    // Domain error
    EXPECT_THROW(NanInfWrapper<double>([](){return std::sqrt(-1.0);}), std::runtime_error);
    EXPECT_THROW(MathErrWrapper<double>([](){return std::sqrt(-1.0);}), std::runtime_error);

    // Pole error
    EXPECT_THROW(NanInfWrapper<double>([](){return std::log(0.0);}), std::runtime_error);
    EXPECT_THROW(MathErrWrapper<double>([](){return std::log(0.0);}), std::runtime_error);
    EXPECT_THROW(NanInfWrapper<double>([](){return 10.0 / 0.0;}), std::runtime_error);
    EXPECT_THROW(MathErrWrapper<double>([](){return 10.0 / 0.0;}), std::runtime_error);

    // Range error
    EXPECT_THROW(NanInfWrapper<double>([](){return std::pow(1000.0, 1000.0);}), std::runtime_error);
    EXPECT_THROW(MathErrWrapper<double>([](){return std::pow(1000.0, 1000.0);}), std::runtime_error);
    EXPECT_NO_THROW(NanInfWrapper<double>([](){return std::pow(12345678999999999, -123);}));
    EXPECT_THROW(MathErrWrapper<double>([](){return std::pow(12345678999999999, -123);}), std::runtime_error);

    EXPECT_THROW(MathFullErrWrapper<double>([](){return 10.0 / 0.0;}), std::runtime_error);

    FloatsEquality();
    DoubleVsDecimal();
    return 0;
}