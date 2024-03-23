#include "../single_use_object/secure_data.h"
#include "../single_use_object/single_use.h"

#include <string>

struct AuthUserBad {
    explicit AuthUserBad(const std::string& name, const std::string& password)
        : m_name(name), m_password(password) {}

    std::string m_name;
    std::string m_password;
};

struct UserName {
    explicit UserName(const std::string& value)
        : m_value(validate(value)) {}

    std::string m_value;

private:
    std::string validate(const std::string& value) const {
        // Domain rules are checked here
        return value;
    };
};

struct Password {
    explicit Password(const SecureData& value)
        : m_value(validate(value)) {}

    SingleUse<SecureData> m_value;

private:
    SecureData validate(const SecureData& value) const {
        // Domain rules are checked here
        return value;
    };
};

struct AuthUser {
    explicit AuthUser(UserName&& name, Password&& password)
        : m_name(std::move(name)), m_password(std::move(password)) {}

    UserName m_name;
    Password m_password;
};

int main(int, char**) {
    return 0;
}