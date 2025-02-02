cmake_minimum_required(VERSION 3.0.0)
project(patterns VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

if (NOT CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra -Wpedantic -pthread -std=c++17")
endif()

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")

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

add_executable(single_use_object 3_2_1_single_use_object/main.cpp)
target_link_libraries(single_use_object PRIVATE spdlog::spdlog_header_only)

add_executable(value_object 3_2_3_value_object/main.cpp)

add_executable(secure_logging 3_2_4_secure_logging/main.cpp)
target_link_libraries(secure_logging PRIVATE spdlog::spdlog_header_only absl::strings)

if (UNIX)
    add_executable(sandboxing 3_2_8_sandboxing/main.cpp)

    add_executable(policy 3_2_10_policy/main.cpp)
    include(CheckSeLinux)
    CheckSELinux()
    if (DEFINED SELINUX_FOUND)
        target_link_libraries(policy PRIVATE selinux)
        target_compile_definitions(policy PRIVATE WITH_SELINUX)
    endif()
endif()

if (WIN32)
    FetchContent_Declare(nlohmann
        GIT_REPOSITORY "https://github.com/nlohmann/json.git"
        GIT_TAG "v3.11.3"
        GIT_SHALLOW ON
    )
    FetchContent_MakeAvailable(nlohmann)
    FetchContent_Declare(hash-library
        GIT_REPOSITORY "https://github.com/stbrumme/hash-library.git"
        GIT_TAG "hash_library_v8"
        GIT_SHALLOW ON
    )
    FetchContent_MakeAvailable(hash-library)

    add_executable(secure_storage
        3_2_11_secure_storage/main.cpp
        3_2_11_secure_storage/json_storage.cpp
        3_2_11_secure_storage/encrypted_storage.cpp
        ${hash-library_SOURCE_DIR}/sha256.cpp)
    target_link_libraries(secure_storage PRIVATE
        absl::cleanup
        absl::flags_parse
        absl::strings
        nlohmann_json::nlohmann_json
        Crypt32.lib)
    target_include_directories(secure_storage PRIVATE ${hash-library_SOURCE_DIR})
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
