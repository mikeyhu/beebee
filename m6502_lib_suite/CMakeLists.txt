project(m6502_lib_suite)

add_executable(m6502_lib_suite CPUSuite.cpp)

target_link_libraries(m6502_lib_suite m6502_lib)

