cmake_minimum_required(VERSION 3.13.0)
project(coding VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -Wall -Wextra -Wpedantic -pthread")

add_executable(sast main.cpp)
