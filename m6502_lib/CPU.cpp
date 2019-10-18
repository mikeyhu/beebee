#include <cstdint>
#include <cstring>
#include <array>
#include "OpCode.cpp"

template<std::size_t SIZE>

class CPU {
    uint8_t ARegister = 0;
    uint8_t XRegister = 0;
    uint8_t YRegister = 0;
    uint8_t stackPointer = 0;
    uint16_t programCounter;
    std::array<uint8_t, SIZE> memory;

public:
    CPU(uint16_t programCounter, std::array<uint8_t, SIZE> memory) {
        this->programCounter = programCounter;
        this->memory = memory;
    }

    void run() {
        for (;;) {
            switch (memory[programCounter++]) {
                case BRK :
                    return;
                case LDA_I :
                    ARegister = memory[programCounter++];
                    break;
                case LDX_I :
                    XRegister = memory[programCounter++];
                    break;
                case LDY_I :
                    YRegister = memory[programCounter++];
                    break;
                case STA_Z :
                    memory[memory[programCounter++]] = ARegister;
                    break;
            }
        }
    }

    uint16_t getProgramCounter() const {
        return programCounter;
    }

    uint8_t getARegister() const {
        return ARegister;
    }

    uint8_t getXRegister() const {
        return XRegister;
    }

    uint8_t getYRegister() const {
        return YRegister;
    }

    const std::array<uint8_t, SIZE> &getMemory() const {
        return memory;
    }
};
