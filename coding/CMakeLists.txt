cmake_minimum_required(VERSION 3.13.0)
project(coding VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

add_executable(null_pointer_init strings/null_pointer_init.cpp)
add_executable(null_pointer_init_fix strings/null_pointer_init_fix.cpp)
add_executable(iterator_invalidated_insert strings/iterator_invalidated_insert.cpp)
add_executable(iterator_invalidated_insert_fix strings/iterator_invalidated_insert_fix.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
