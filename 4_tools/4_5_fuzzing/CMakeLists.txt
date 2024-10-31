cmake_minimum_required(VERSION 3.13.0)
project(coding VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

if (NOT CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    message( SEND_ERROR "Please use clang" )
endif()

include(FetchContent)
FetchContent_Declare(nlohmann
        GIT_REPOSITORY "https://github.com/nlohmann/json.git"
        GIT_TAG "v3.11.3"
        GIT_SHALLOW ON
    )
FetchContent_MakeAvailable(nlohmann)

add_executable(fuzztest target.cpp)

target_link_libraries(fuzztest PRIVATE nlohmann_json::nlohmann_json)
target_compile_options(fuzztest PRIVATE -fsanitize=fuzzer,address -g -O0)
target_link_options(fuzztest PRIVATE -fsanitize=fuzzer,address)
