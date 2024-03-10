#define __STDC_WANT_LIB_EXT1__ 1

#include <iostream>
#include <optional>
#include <string>
#include <string.h>

void memzero(void *const buff, const size_t len)
{
#ifdef _WIN32
    SecureZeroMemory(buff, len);
#elif defined(__STDC_LIB_EXT1__)
    if (len && memset_s(buff, static_cast<rsize_t>(len), 0, static_cast<rsize_t>(len)) != 0) {
        throw std::runtime_error("Memset error");
    }
#elif defined(__linux__ ) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__)
    explicit_bzero(buff, len);
#else
    volatile unsigned char *volatile buff_ =
        static_cast<volatile unsigned char *volatile>(buff);
    size_t i{0};

    while (i < len) {
        buff_[i++] = 0U;
    }
#endif
}

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
