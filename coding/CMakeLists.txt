cmake_minimum_required(VERSION 3.13.0)
project(coding VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -Wall -Wextra -Wpedantic")

add_executable(null_pointer_init strings/null_pointer_init.cpp)
add_executable(null_pointer_init_fix strings/null_pointer_init_fix.cpp)
add_executable(iterator_invalidated_insert strings/iterator_invalidated_insert.cpp)
add_executable(iterator_invalidated_insert_fix strings/iterator_invalidated_insert_fix.cpp)
add_executable(iterator_invalidated_erase strings/iterator_invalidated_erase.cpp)
add_executable(iterator_invalidated_erase_fix strings/iterator_invalidated_erase_fix.cpp)
add_executable(out_of_range strings/out_of_range.cpp)
add_executable(string_view_dangling strings/string_view_dangling.cpp)
add_executable(string_view_null_termination strings/string_view_null_termination.cpp)
add_executable(sso_stack_overflow strings/sso_stack_overflow.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
