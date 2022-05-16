cmake_minimum_required(VERSION 3.12)
project(skiplist)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_COMPILE_FEATURES)

add_executable(main main.cc skiplist/Node.h skiplist/SkipList.h skiplist/RandomGenerator.h)
include_directories(./skiplist)