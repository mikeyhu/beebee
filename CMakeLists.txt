cmake_minimum_required(VERSION 3.13)
project(beebee)

set(CMAKE_CXX_STANDARD 17)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(beebee main.cpp App.cpp)

include_directories(m6502_lib)
add_subdirectory(m6502_lib)
add_subdirectory(m6502_lib_tests)
add_subdirectory(m6502_lib_suite)
add_subdirectory(beebee_lib)

target_link_libraries(beebee ${CONAN_LIBS})