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
    bool zeroFlag = false;
    std::array<uint8_t, SIZE> memory;

    uint16_t toUInt16(uint8_t a, uint8_t b) {
        return b << 8 | a;
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

    OpCode readOpCode() {
        OpCode opCode = (OpCode) readUInt8();
        return opCode;
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

    uint16_t locationZeroPageY() {
        return locationZeroPage() + YRegister;
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

    void branchIfTrue(bool check) {
        uint8_t location = readImmediate(); //always read immediate to move counter anyway
        if (check) {
            if (location >= 0x80) {
                programCounter = programCounter - 0x100 + location;
            } else {
                programCounter = programCounter + location;
            }
        }
    }

public:
    CPU(uint16_t programCounter, std::array<uint8_t, SIZE> memory) {
        this->programCounter = programCounter;
        this->memory = memory;
    }

    void run() {
        for (;;) {
            switch (readOpCode()) {
                case BRK :
                    printState();
                    return;
                case CLD :
                    decimalFlag = false;
                    break;
                case JMP_Ab:
                    programCounter = locationAbsolute();
                    break;

                    // AND : bitwise AND with accumulator
                case AND_I :
                    setARegister(ARegister & readImmediate());
                    break;
                case AND_Ab :
                    setARegister(ARegister & readAbsolute());
                    break;
                case AND_AbX :
                    setARegister(ARegister & readAbsoluteX());
                    break;
                case AND_AbY :
                    setARegister(ARegister & readAbsoluteY());
                    break;
                case AND_Z :
                    setARegister(ARegister & readZeroPage());
                    break;
                case AND_ZX :
                    setARegister(ARegister & readZeroPageX());
                    break;

                    // Branch
                case BNE_Re : {
                    branchIfTrue(!zeroFlag);
                    break;
                }
                case BEQ_Re : {
                    branchIfTrue(zeroFlag);
                    break;
                }

                    // Compare
                case CPX_I :
                    zeroFlag = readImmediate() == XRegister;
                    break;

                    //IN : INcremement
                case INX :
                    XRegister++;
                    break;
                case INY :
                    YRegister++;
                    break;

                    //DE : DEcremement
                case DEX :
                    setXRegister(XRegister - 1);
                    break;
                case DEY :
                    setYRegister(YRegister - 1);
                    break;

                    // LDA : LoaD Accumulator
                case LDA_I :
                    setARegister(readImmediate());
                    break;
                case LDA_Ab :
                    setARegister(readAbsolute());
                    break;
                case LDA_AbX :
                    setARegister(readAbsoluteX());
                    break;
                case LDA_AbY :
                    setARegister(readAbsoluteY());
                    break;
                case LDA_Z :
                    setARegister(readZeroPage());
                    break;
                case LDA_ZX :
                    setARegister(readZeroPageX());
                    break;

                    // LDX : LoaD Xregister
                case LDX_I :
                    setXRegister(readImmediate());
                    break;
                case LDX_Ab :
                    setXRegister(readAbsolute());
                    break;
                case LDX_AbY :
                    setXRegister(readAbsoluteY());
                    break;
                case LDX_Z :
                    setXRegister(readZeroPage());
                    break;
                case LDX_ZX :
                    setXRegister(readZeroPageX());
                    break;

                    // LDY : LoaD Yregister
                case LDY_I :
                    setYRegister(readImmediate());
                    break;
                case LDY_Ab :
                    setYRegister(readAbsolute());
                    break;
                case LDY_AbX :
                    setYRegister(readAbsoluteX());
                    break;
                case LDY_Z :
                    setYRegister(readZeroPage());
                    break;
                case LDY_ZX :
                    setYRegister(readZeroPageX());
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
                    //STX : STore Xregister
                case STX_Ab :
                    memory[locationAbsolute()] = XRegister;
                    break;
                case STX_Z :
                    memory[locationZeroPage()] = XRegister;
                    break;
                case STX_ZY :
                    memory[locationZeroPageY()] = XRegister;
                    break;

                    // T : Transfer
                case TAX:
                    setXRegister(ARegister);
                    break;
                case TAY :
                    setYRegister(ARegister);
                    break;
                case TXA:
                    setARegister(XRegister);
                    break;
                case TYA:
                    setARegister(YRegister);
                    break;
                case TXS :
                    stackPointer = XRegister;
                    break;
                default:
                    std::cout << "Unknown OpCode:" << std::hex << (int) memory[programCounter - 1] << std::endl;
                    printState();
                    return;
            }
            printState();
        }
    }

    uint16_t getProgramCounter() const {
        return programCounter;
    }

    uint8_t getARegister() const {
        return ARegister;
    }

    void setARegister(uint8_t aRegister) {
        ARegister = aRegister;
        zeroFlag = ARegister == 0;
    }

    uint8_t getXRegister() const {
        return XRegister;
    }

    void setXRegister(uint8_t xRegister) {
        XRegister = xRegister;
        zeroFlag = XRegister == 0;

    }

    uint8_t getYRegister() const {
        return YRegister;
    }

    void setYRegister(uint8_t yRegister) {
        YRegister = yRegister;
        zeroFlag = YRegister == 0;
    }

    bool isDecimalFlag() const {
        return decimalFlag;
    }

    void setDecimalFlag(bool decimalFlag) {
        CPU::decimalFlag = decimalFlag;
    }

    bool isZeroFlag() const {
        return zeroFlag;
    }

    void setZeroFlag(bool zeroFlag) {
        CPU::zeroFlag = zeroFlag;
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

    void printState() {
        std::cout << "PC:" << std::hex << (int) programCounter
                  << " SP:" << (int) stackPointer
                  << " A:" << (int) ARegister
                  << " X:" << (int) XRegister
                  << " Y:" << (int) YRegister
                  << std::endl;
    }
};
