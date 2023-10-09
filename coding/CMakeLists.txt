cmake_minimum_required(VERSION 3.13.0)
project(coding VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(null_pointer_init strings/null_pointer_init.cpp)
add_executable(null_pointer_init_fix strings/null_pointer_init_fix.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
