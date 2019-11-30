project(beebee_lib)

include(${CMAKE_BINARY_DIR}/../beebee_lib/conanbuildinfo.cmake)
conan_basic_setup()

set(HEADER_FILES )

set(SOURCE_FILES
        Screen.cpp
        )

add_library(beebee_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(beebee_lib m6502_lib)