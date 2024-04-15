cmake_minimum_required(VERSION 3.0.0)
project(patterns VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -Wall -Wextra -Wpedantic -pthread")

include(FetchContent)
FetchContent_Declare(spdlog
    GIT_REPOSITORY "https://github.com/gabime/spdlog.git"
    GIT_TAG "v1.13.0"
    GIT_SHALLOW ON
)
FetchContent_MakeAvailable(spdlog)
FetchContent_Declare(abseil
    GIT_REPOSITORY "https://github.com/abseil/abseil-cpp.git"
    GIT_TAG "lts_2024_01_16"
    GIT_SHALLOW ON
)
FetchContent_MakeAvailable(abseil)

add_executable(single_use_object single_use_object/main.cpp)
target_link_libraries(single_use_object PRIVATE spdlog::spdlog_header_only)

add_executable(value_object value_object/main.cpp)

add_executable(secure_logging secure_logging/main.cpp)
target_link_libraries(secure_logging PRIVATE spdlog::spdlog_header_only absl::strings)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
