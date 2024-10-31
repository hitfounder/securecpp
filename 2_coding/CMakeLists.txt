cmake_minimum_required(VERSION 3.13.0)
project(coding VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -Wall -Wextra -Wpedantic -pthread")

include(FetchContent)
FetchContent_Declare(GSL
    GIT_REPOSITORY "https://github.com/microsoft/GSL"
    GIT_TAG "v4.0.0"
    GIT_SHALLOW ON
)
FetchContent_MakeAvailable(GSL)
FetchContent_Declare(llfio
    GIT_REPOSITORY "https://github.com/ned14/llfio"
    GIT_SHALLOW ON
)
FetchContent_MakeAvailable(llfio)

link_libraries(Microsoft.GSL::GSL)

find_package(Boost REQUIRED)
find_package(GTest REQUIRED)

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

add_executable(uaf_temporary memory/uaf_temporary.cpp)
add_executable(delete memory/delete.cpp)
add_executable(placement_new memory/placement_new.cpp)
add_executable(aligned_buffer memory/aligned_buffer.cpp)
add_executable(double_delete memory/double_delete.cpp)
add_executable(smart_ptr_array memory/smart_ptr_array.cpp)
add_executable(smart_ptr_dangling memory/smart_ptr_dangling.cpp)
add_executable(alloca memory/alloca.cpp)

add_executable(init initialization/init.cpp)
add_executable(global_ub initialization/global_ub2.cpp initialization/global_ub1.cpp)
add_executable(narrowing initialization/narrowing.cpp initialization/narrowing.cpp)

add_executable(unsigned 2_4_arithmetics/2_4_1_unsigned/unsigned.cpp)
target_link_libraries(unsigned GTest::gtest_main)
add_executable(signed 2_4_arithmetics/2_4_2_signed/signed.cpp)
target_link_libraries(signed GTest::gtest_main)
add_executable(sizeof 2_4_arithmetics/tools/sizeof.cpp)
add_executable(bitshift 2_4_arithmetics/2_4_3_bits/bitshift.cpp)
target_link_libraries(bitshift GTest::gtest_main)
add_executable(type_conversion 2_4_arithmetics/2_4_4_conversion/type_conversion.cpp)
add_executable(floats 2_4_arithmetics/2_4_5_floats/floats.cpp)
target_link_libraries(floats GTest::gtest_main)

add_executable(terminate threading/terminate.cpp)
add_executable(shared_ptr threading/shared_ptr.cpp)
add_executable(stack_race_condition threading/stack_race_condition.cpp)
add_executable(multiple_locks threading/multiple_locks.cpp)
add_executable(recursive_lock threading/recursive_lock.cpp)
add_executable(endless_wait threading/endless_wait.cpp)

add_executable(paths files/paths.cpp)
target_link_libraries(paths GTest::gtest_main)
add_executable(races files/races.cpp)
target_link_libraries(races llfio_sl)

add_executable(hash 2_7_crypto/2_7_3_hashing/hash.cpp)
add_executable(random 2_7_crypto/2_7_6_random/random.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
