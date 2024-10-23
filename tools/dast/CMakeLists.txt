cmake_minimum_required(VERSION 3.13.0)
project(coding VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_BUILD_TYPE MATCHES "asan")
    add_compile_options(-fsanitize=address -g -O0)
    add_link_options(-fsanitize=address)
endif()

add_executable(dast main.cpp)
