#include <cstdint>
#include <cstring>

#ifndef CLASS_OPCODE
#define CLASS_OPCODE

#include "OpCode.cpp"

#endif

#ifndef BEEBEE_UTILITIES
#define BEEBEE_UTILITIES

#include "Utilities.cpp"

#endif
#ifndef BEEBEE_MEMORY
#include "Memory.cpp"
#endif

template<std::size_t SIZE>

class Via {
    Memory<SIZE> *memory;

public:
    Via(Memory<SIZE> &memory) : memory(&memory) {}

    void initialise() {
        memory->setValue(0xFE40, 0xFF);
        memory->setValue(0xFE41, 0x00);
        memory->setValue(0xFE42, 0x00);
        memory->setValue(0xFE43, 0xFF);
        memory->setValue(0xFE4E, 0x00);
        memory->setValue(0xFE60, 0xFF);
        memory->setValue(0xFE61, 0x00);
        memory->setValue(0xFE62, 0x00);
        memory->setValue(0xFE63, 0xFF);
    }
};