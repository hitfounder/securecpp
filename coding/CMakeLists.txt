cmake_minimum_required(VERSION 3.13.0)
project(coding VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -Wall -Wextra -Wpedantic")

find_package(Microsoft.GSL CONFIG REQUIRED)
find_package(Boost REQUIRED)

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

add_executable(unsigned arithmetics/unsigned.cpp)
add_executable(sizeof arithmetics/sizeof.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
