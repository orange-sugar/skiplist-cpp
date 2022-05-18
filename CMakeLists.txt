cmake_minimum_required(VERSION 3.12)
project(skiplist)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -g")
# set(CMAKE_CXX_COMPILE_FEATURES)

add_executable(main main.cc skiplist/Node.h skiplist/SkipList.h skiplist/RandomGenerator.h)
include_directories(./skiplist)

# add_subdirectory(tests)
add_subdirectory(thirdparty/googletest)

add_executable(test tests/skiplist_tests.cc)
# add_library(gtest gtest_main)
target_link_libraries(test gtest gtest_main)