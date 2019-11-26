project(m6502_lib)

set(HEADER_FILES )

set(SOURCE_FILES
        CPU.cpp
        CPUState.cpp
        Memory.cpp
        OpLog.cpp
        OpCode.cpp
        OpCodeMacro.cpp
        )

add_library(m6502_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})