project(beebee_lib)

set(HEADER_FILES )

set(SOURCE_FILES
        Teletext.cpp
        )

add_library(beebee_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})