#include <iostream>
#include <iterator>

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#include "secure_data.h"
#include "single_use.h"

SecureData RequestPassword() {
    // Password is requested here
    return {'p', 'a', 's', 's', 'w', 'o', 'r', 'd'};
}

void Authenticate(const SecureData& password) {
    // Authentication is performed here
    spdlog::info("Authenticating with password: {}", password);
}

int main(int, char**){
    SingleUse password(RequestPassword());    
    Authenticate(password.extract());

    // Here will be exception
    password.extract();

    return 0;
}
