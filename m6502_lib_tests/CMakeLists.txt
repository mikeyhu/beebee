project(m6502_lib_tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

# All from https://www.jetbrains.com/help/clion/unit-testing-tutorial.html

# adding the Google_Tests_run target
add_executable(m6502_lib_tests
        CPUTest.cpp
        CPUTestBitwise.cpp
        CPUTestCompare.cpp
        CPUTestBranch.cpp
        CPUTestStack.cpp
        CPUTestInterrupt.cpp
        MemoryTest.cpp
        Helpers.cpp
        PageableMemoryTest.cpp
        ViaTest.cpp)

target_link_libraries(m6502_lib_tests m6502_lib)

target_link_libraries(m6502_lib_tests gtest gtest_main)