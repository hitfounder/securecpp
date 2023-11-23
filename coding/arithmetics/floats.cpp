#include <boost/type_index.hpp>
#include <cfenv>
#include <cmath>
#include <gtest/gtest.h>
#include <iostream>

#pragma STDC FENV_ACCESS ON

template<typename T>
T NanInfWrapper(std::function<T ()> op) {
    const auto res{op()};
    if constexpr (std::numeric_limits<T>::is_iec559) {
        if (std::isnan(res))
            throw std::runtime_error("Result is NaN");
        else if (std::isinf(res))
            throw std::runtime_error("Result is Infinity");
    }
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

int main() {
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

    return 0;
}