#include <iostream>
#include <optional>
#include <string>
#include <string.h>

#define __STDC_WANT_LIB_EXT1__ 1

template <typename T>
class SingleUse {
public:
    explicit SingleUse(const T& data)
        : m_data(data) {}

    T get() {
        if (m_data.has_value()) {
            std::optional<T> data;
            std::swap(m_data, data);
            return data.value();
        }
        throw std::runtime_error("Value already used");
    }
    
private:
    mutable std::optional<T> m_data;
};

std::string RequestPassword() {
    // Password is requested here
    return "password";
}

void Authenticate(const std::string& password) {
    // Authentication is performed here
    std::cout << "Authentication with password: " << password << std::endl;
}

int main(int, char**){
    SingleUse password(RequestPassword());    
    Authenticate(password.get());

    // Here will be exception
    password.get();

    return 0;
}
