cmake_minimum_required(VERSION 3.13)
project(beebee)

set(CMAKE_CXX_STANDARD 17)

add_executable(beebee main.cpp)

include_directories(m6502_lib)
add_subdirectory(m6502_lib)
add_subdirectory(m6502_lib_tests)
add_subdirectory(m6502_lib_suite)
