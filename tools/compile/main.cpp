#include <iostream>
#include <stdio.h>
#include <string.h>

int main() {
    // -Wformat-insufficient-args
    printf("Missing format argument %i:\n");

    // -Wfloat-conversion
    {
        double val = 0;
        int i = val; 
        (void)i;
    }

    // -Wsign-conversion
    {
        unsigned int i = -10;
        (void)i;
    }

    // -Wimplicit-fallthrough
    {
        int i = 0;
        switch (i) {
            case(0):
                ++i;
            case(1):
                ++i;
            default:
                break;
        }
    }

    // Will terminate at runtime: *** buffer overflow detected ***: terminated
    // GCC will also warn: -Wstringop-overflow, -Warray-bounds
    {
        const char *src = "Copy with overflow";
        char dst[5];
        strcpy(dst, src);
        std::cout << dst << "/n";
    }

    // Will terminate at runtime: Assertion '__pos <= size()' failed    
    {
        std::string str;
        std::cout << str[1] << "/n";
    }
    return 0;
}
