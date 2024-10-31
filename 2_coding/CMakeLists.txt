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

add_executable(null_pointer_init 2_1_strings/2_1_1_null_initialization/null_pointer_init.cpp)
add_executable(null_pointer_init_fix 2_1_strings/2_1_1_null_initialization/null_pointer_init_fix.cpp)
add_executable(iterator_invalidated_insert 2_1_strings/2_1_2_iterators/iterator_invalidated_insert.cpp)
add_executable(iterator_invalidated_insert_fix 2_1_strings/2_1_2_iterators/iterator_invalidated_insert_fix.cpp)
add_executable(iterator_invalidated_erase 2_1_strings/2_1_2_iterators/iterator_invalidated_erase.cpp)
add_executable(iterator_invalidated_erase_fix 2_1_strings/2_1_2_iterators/iterator_invalidated_erase_fix.cpp)
add_executable(out_of_range 2_1_strings/2_1_3_out_of_bounds/out_of_range.cpp)
add_executable(string_view_dangling 2_1_strings/2_1_5_string_view/string_view_dangling.cpp)
add_executable(string_view_null_termination 2_1_strings/2_1_5_string_view/string_view_null_termination.cpp)
add_executable(sso_stack_overflow 2_1_strings/2_1_4_sso/sso_stack_overflow.cpp)

add_executable(uaf_temporary 2_2_memory/2_2_2_use_after_free/uaf_temporary.cpp)
add_executable(delete 2_2_memory/2_2_3_new_and_delete/delete.cpp)
add_executable(placement_new 2_2_memory/2_2_4_placement_new/placement_new.cpp)
add_executable(aligned_buffer 2_2_memory/2_2_4_placement_new/aligned_buffer.cpp)
add_executable(double_delete 2_2_memory/2_2_6_double_delete/double_delete.cpp)
add_executable(smart_ptr_array 2_2_memory/2_2_7_smart_ptrs/smart_ptr_array.cpp)
add_executable(smart_ptr_dangling 2_2_memory/2_2_7_smart_ptrs/smart_ptr_dangling.cpp)
add_executable(alloca 2_2_memory/2_2_8_stack_dynamic/alloca.cpp)

add_executable(init 2_3_initialization/2_3_1_init/init.cpp)
add_executable(global_ub 2_3_initialization/2_3_1_init/global_ub2.cpp 2_3_initialization/2_3_1_init/global_ub1.cpp)
add_executable(narrowing 2_3_initialization/2_3_2_narrowing/narrowing.cpp)

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

add_executable(terminate 2_5_threading/2_5_1_termination/terminate.cpp)
add_executable(shared_ptr 2_5_threading/2_5_2_synchronization/shared_ptr.cpp)
add_executable(stack_race_condition 2_5_threading/2_5_2_synchronization/stack_race_condition.cpp)
add_executable(multiple_locks 2_5_threading/2_5_3_deadlocks/multiple_locks.cpp)
add_executable(recursive_lock 2_5_threading/2_5_3_deadlocks/recursive_lock.cpp)
add_executable(endless_wait 2_5_threading/2_5_3_deadlocks/endless_wait.cpp)

add_executable(paths 2_6_files/2_6_1_paths/paths.cpp)
target_link_libraries(paths GTest::gtest_main)
add_executable(races 2_6_files/2_6_2_races/races.cpp)
target_link_libraries(races llfio_sl)

add_executable(hash 2_7_crypto/2_7_3_hashing/hash.cpp)
add_executable(random 2_7_crypto/2_7_6_random/random.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
