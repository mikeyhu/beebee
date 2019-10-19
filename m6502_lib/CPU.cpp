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

    uint16_t toUInt16(uint8_t a, uint8_t b) {
        return a << 8 | b;
    }

    uint16_t readUInt16() {
        return toUInt16(memory[programCounter++], memory[programCounter++]);
    }

    uint16_t locationAbsolute() {
        return readUInt16();
    }

    uint8_t readUInt8() {
        return memory[programCounter++];
    }

    uint8_t readImmediate() {
        return readUInt8();
    }

    uint8_t locationZeroPage() {
        return readUInt8();
    }

    uint8_t readZeroPage() {
        return memory[locationZeroPage()];
    }

    uint16_t locationZeroPageX() {
        return locationZeroPage() + XRegister;
    }

    uint8_t readZeroPageX() {
        return memory[locationZeroPageX()];
    }

    uint16_t locationAbsoluteX() {
        return locationAbsolute() + XRegister;
    }

    uint16_t locationAbsoluteY() {
        return locationAbsolute() + YRegister;
    }

    uint8_t readAbsoluteX() {
        return memory[locationAbsoluteX()];
    }

    uint8_t readAbsoluteY() {
        return memory[locationAbsoluteY()];
    }

    uint8_t readAbsolute() {
        return memory[locationAbsolute()];
    }

public:
    CPU(uint16_t programCounter, std::array<uint8_t, SIZE> memory) {
        this->programCounter = programCounter;
        this->memory = memory;
    }

    void run() {
        for (;;) {
            switch (readUInt8()) {
                case BRK :
                    return;
                case CLD :
                    decimalFlag = false;
                    break;
                case JMP_Ab:
                    programCounter = locationAbsolute();
                    break;

                    // AND : bitwise AND with accumulator
                case AND_I :
                    ARegister = ARegister & readImmediate();
                    break;
                case AND_Ab :
                    ARegister = ARegister & readAbsolute();
                    break;
                case AND_AbX :
                    ARegister = ARegister & readAbsoluteX();
                    break;
                case AND_AbY :
                    ARegister = ARegister & readAbsoluteY();
                    break;
                case AND_Z :
                    ARegister = ARegister & readZeroPage();
                    break;
                case AND_ZX :
                    ARegister = ARegister & readZeroPageX();
                    break;

                    // LDA : LoaD Accumulator
                case LDA_I :
                    ARegister = readImmediate();
                    break;
                case LDA_Ab :
                    ARegister = readAbsolute();
                    break;
                case LDA_AbX :
                    ARegister = readAbsoluteX();
                    break;
                case LDA_AbY :
                    ARegister = readAbsoluteY();
                    break;
                case LDA_Z :
                    ARegister = readZeroPage();
                    break;
                case LDA_ZX :
                    ARegister = readZeroPageX();
                    break;

                    // LDX : LoaD Xregister
                case LDX_I :
                    XRegister = readImmediate();
                    break;
                case LDX_Ab :
                    XRegister = readAbsolute();
                    break;
                case LDX_AbY :
                    XRegister = readAbsoluteY();
                    break;
                case LDX_Z :
                    XRegister = readZeroPage();
                    break;
                case LDX_ZX :
                    XRegister = readZeroPageX();
                    break;

                    // LDY : LoaD Yregister
                case LDY_I :
                    YRegister = readImmediate();
                    break;
                case LDY_Ab :
                    YRegister = readAbsolute();
                    break;
                case LDY_AbX :
                    YRegister = readAbsoluteX();
                    break;
                case LDY_Z :
                    YRegister = readZeroPage();
                    break;
                case LDY_ZX :
                    YRegister = readZeroPageX();
                    break;

                    //STA : STore Accumulator
                case STA_Ab :
                    memory[locationAbsolute()] = ARegister;
                    break;
                case STA_AbX :
                    memory[locationAbsoluteX()] = ARegister;
                    break;
                case STA_AbY :
                    memory[locationAbsoluteY()] = ARegister;
                    break;
                case STA_Z :
                    memory[locationZeroPage()] = ARegister;
                    break;
                case STA_ZX :
                    memory[locationZeroPageX()] = ARegister;
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
