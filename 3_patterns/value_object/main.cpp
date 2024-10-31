#include "../single_use_object/secure_data.h"
#include "../single_use_object/single_use.h"

#include <string>

struct AuthUserBad {
    explicit AuthUserBad(const std::string& name, const std::string& password)
        : m_name(name), m_password(password) {}

    std::string m_name;
    std::string m_password;
};

class UserName {
public:
    explicit UserName(const std::string& value)
        : m_value(validate(value)) {}

    std::string get() const {
        return m_value;
    }

private:
    const std::string& validate(const std::string& value) const {
        // Domain rules are checked here
        return value;
    };

    const std::string m_value;
};

class Password {
public:
    explicit Password(const SecureData& value)
        : m_value(validate(value)) {}

    SecureData get() const {
        return m_value.extract();
    }

private:
    const SecureData& validate(const SecureData& value) const {
        // Domain rules are checked here
        return value;
    };

    mutable SingleUse<SecureData> m_value;
};

struct AuthUser {
    explicit AuthUser(UserName&& name, Password&& password)
        : m_name(std::move(name)), m_password(std::move(password)) {}

    UserName m_name;
    Password m_password;
};

int main(int, char**) {
    UserName userName{"user"};
    Password password({'p', 'a', 's', 's', 'w', 'o', 'r', 'd'});
    AuthUser(std::move(userName), std::move(password));
    return 0;
}