cmake_minimum_required(VERSION 2.8)

project(PimpMyLog)

include_directories(src)
add_definitions(-Wall -W -std=c++0x)
add_subdirectory(src)
add_subdirectory(tests)
