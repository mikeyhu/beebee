#include <cstdint>
#include <cstring>
#include <array>
#include <iostream>
#include "OpCode.cpp"

template<std::size_t SIZE>

class CPU {
    uint8_t ARegister = 0;
    uint8_t XRegister = 0;
    uint8_t YRegister = 0;
    uint8_t stackPointer = 0;
    uint16_t programCounter;
    bool decimalFlag = false;
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
                case CLD :
                    decimalFlag = false;
                    break;
                case TXS :
                    stackPointer = XRegister;
                    break;
                default:
                    std::cout << "Unknown OpCode:" << std::hex << (int) memory[programCounter - 1] << std::endl;
                    return;
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

    bool isDecimalFlag() const {
        return decimalFlag;
    }

    void setDecimalFlag(bool decimalFlag) {
        CPU::decimalFlag = decimalFlag;
    }

    uint8_t getStackPointer() const {
        return stackPointer;
    }

    void setStackPointer(uint8_t stackPointer) {
        CPU::stackPointer = stackPointer;
    }

    const std::array<uint8_t, SIZE> &getMemory() const {
        return memory;
    }
};
