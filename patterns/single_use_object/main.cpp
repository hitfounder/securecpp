#include "secure_data.h"
#include "single_use.h"

#include <iostream>
#include <iterator>

SecureData RequestPassword() {
    // Password is requested here
    return {'p', 'a', 's', 's', 'w', 'o', 'r', 'd'};
}

void Authenticate(const SecureData& password) {
    // Authentication is performed here
    std::cout << "Authenticating with password: ";
    std::copy(password.begin(), password.end(), std::ostream_iterator<char>(std::cout, ""));
    std::cout << std::endl;
}

int main(int, char**){
    SingleUse password(RequestPassword());    
    Authenticate(password.extract());

    // Here will be exception
    password.extract();

    return 0;
}
