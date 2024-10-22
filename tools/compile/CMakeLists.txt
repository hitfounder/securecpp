cmake_minimum_required(VERSION 3.13.0)
project(coding VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-O2 -Wall -Wformat -Wformat=2 -Wconversion -Wsign-conversion
                    -Wimplicit-fallthrough -Werror=format-security
                    -U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=3
                    -D_GLIBCXX_ASSERTIONS
                    -fstack-clash-protection -fstack-protector-strong
                    -fPIE
                    -fcf-protection=full -fno-delete-null-pointer-checks -fno-strict-overflow -fno-strict-aliasing)
add_link_options(-pie
                 -Wl,-z,nodlopen -Wl,-z,noexecstack -Wl,-z,relro -Wl,-z,now -Wl,--as-needed -Wl,--no-copy-dt-needed-entries)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 12)
        add_compile_options(-Wtrampolines -Wbidi-chars=any -ftrivial-auto-var-init=zero)
    endif()
endif()

add_executable(champ_compile main.cpp)
