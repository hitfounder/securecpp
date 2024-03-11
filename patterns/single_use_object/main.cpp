#include "memzero.h"

#include <iostream>
#include <optional>
#include <string>

using SecureData = std::string;

class SingleUse {
public:
    explicit SingleUse(const SecureData& secureData)
        : m_secureData(secureData) {}

    SingleUse(const SingleUse&) = delete;
    SingleUse& operator=(const SingleUse&) = delete;

    SingleUse(SingleUse&&) = default;
    SingleUse& operator=(SingleUse&&) = default;

    SecureData extract() {
        if (m_secureData.has_value()) {
            OptionalSecureData secureData;
            std::swap(m_secureData, secureData);
            return secureData.value();
        }
        throw std::runtime_error("Value already used");
    }
    
private:
    using OptionalSecureData = std::optional<SecureData>;

    mutable OptionalSecureData m_secureData;
};

SecureData RequestPassword() {
    // Password is requested here
    return "password";
}

void Authenticate(const SecureData& password) {
    // Authentication is performed here
    std::cout << "Authentication with password: " << password << std::endl;
}

int main(int, char**){
    SingleUse password(RequestPassword());    
    Authenticate(password.extract());

    // Here will be exception
    password.extract();

    return 0;
}
