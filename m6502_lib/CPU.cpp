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
    uint16_t previousProgramCounter;
    bool carryFlag = false;
    bool zeroFlag = false;
    bool interruptDisableFlag = false;
    bool breakCommandFlag = true;
    bool decimalFlag = false;
    bool unknownFlag = false;
    bool overflowFlag = false;
    bool negativeFlag = false;
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

    void compareRegisterTo(uint8_t reg, uint8_t value) {
        zeroFlag = value == reg;
        carryFlag = reg >= value;
        negativeFlag = reg < value;
    }

    uint8_t flagsAsInt() {
        return carryFlag |
               (zeroFlag << 1) |
               (interruptDisableFlag << 2) |
               (decimalFlag << 3) |
               (true << 4) |
               (true << 5) |
               (overflowFlag << 6) |
               (negativeFlag << 7);
    }

    void intToFlags(uint8_t flags) {
        carryFlag = flags & 1;
        zeroFlag = flags >> 1 & 1;
        interruptDisableFlag = flags >> 2 & 1;
        decimalFlag = flags >> 3 & 1;
//        breakCommandFlag = flags >> 4 & 1;
        breakCommandFlag = true;
//        unknownFlag = flags >> 5 & 1;
        unknownFlag = true;
        overflowFlag = flags >> 6 & 1;
        negativeFlag = flags >> 7 & 1;
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
                case CLC :
                    carryFlag = false;
                    break;
                case CLD :
                    decimalFlag = false;
                    break;
                case JMP_Ab:
                    programCounter = locationAbsolute();
                    break;
                case JMP_Indir: {
                    uint16_t indirect = locationAbsolute();
                    uint8_t upper = memory[indirect];
                    uint8_t lower = memory[indirect + 1];
                    programCounter = toUInt16(upper, lower);
                    break;
                }
                    // ADC : ADd with Carry
                case ADC_I :
                    addToARegister(readImmediate());
                    break;
                case ADC_Z :
                    addToARegister(readZeroPage());
                    break;
                case ADC_ZX :
                    addToARegister(readZeroPageX());
                    break;
                case ADC_Ab :
                    addToARegister(readAbsoluteY());
                    break;
                case ADC_AbX :
                    addToARegister(readAbsoluteX());
                    break;
                case ADC_AbY :
                    addToARegister(readAbsoluteY());
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
                    // AND : bitwise AND with accumulator
                case EOR_I :
                    setARegister(ARegister ^ readImmediate());
                    break;
                case EOR_Ab :
                    setARegister(ARegister ^ readAbsolute());
                    break;
                case EOR_AbX :
                    setARegister(ARegister ^ readAbsoluteX());
                    break;
                case EOR_AbY :
                    setARegister(ARegister ^ readAbsoluteY());
                    break;
                case EOR_Z :
                    setARegister(ARegister ^ readZeroPage());
                    break;
                case EOR_ZX :
                    setARegister(ARegister ^ readZeroPageX());
                    break;

                    // Branch
                case BCC_Re :
                    branchIfTrue(!carryFlag);
                    break;
                case BCS_Re :
                    branchIfTrue(carryFlag);
                    break;
                case BNE_Re :
                    branchIfTrue(!zeroFlag);
                    break;
                case BEQ_Re :
                    branchIfTrue(zeroFlag);
                    break;
                case BPL_Re :
                    branchIfTrue(!negativeFlag);
                    break;
                case BMI_Re :
                    branchIfTrue(negativeFlag);
                    break;
                case BVC_Re :
                    branchIfTrue(!overflowFlag);
                    break;
                case BVS_Re :
                    branchIfTrue(overflowFlag);
                    break;
                    // Compare
                case CMP_I :
                    compareRegisterTo(ARegister, readImmediate());
                    break;
                case CMP_Z :
                    compareRegisterTo(ARegister, readZeroPage());
                    break;
                case CMP_ZX :
                    compareRegisterTo(ARegister, readZeroPageX());
                    break;
                case CMP_Ab :
                    compareRegisterTo(ARegister, readAbsolute());
                    break;
                case CMP_AbX :
                    compareRegisterTo(ARegister, readAbsoluteX());
                    break;
                case CMP_AbY :
                    compareRegisterTo(ARegister, readAbsoluteY());
                    break;
                case CPX_I :
                    compareRegisterTo(XRegister, readImmediate());
                    break;
                case CPX_Ab :
                    compareRegisterTo(XRegister, readAbsolute());
                    break;
                case CPX_Z :
                    compareRegisterTo(XRegister, readZeroPage());
                    break;
                case CPY_I :
                    compareRegisterTo(YRegister, readImmediate());
                    break;
                case CPY_Ab :
                    compareRegisterTo(YRegister, readAbsolute());
                    break;
                case CPY_Z :
                    compareRegisterTo(YRegister, readZeroPage());
                    break;

                    //IN : INcremement
                case INX :
                    setXRegister(XRegister + 1);
                    break;
                case INY :
                    setYRegister(YRegister + 1);
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

                    //stack
                case TSX :
                    setXRegister(stackPointer);
                    break;
                case PHA :
                    memory[0x100 + stackPointer--] = ARegister;
                    break;
                case PLA :
                    setARegister(memory[0x100 + ++stackPointer]);
                    break;
                case PHP :
                    memory[0x100 + stackPointer--] = flagsAsInt();
                    break;
                case PLP :
                    intToFlags(memory[0x100 + ++stackPointer]);
                    break;
                case NOP :
                    break;
                default:
                    std::cout << "Unknown OpCode:" << std::hex << (int) memory[programCounter - 1] << std::endl;
                    printState();
                    return;
            }
            if (previousProgramCounter == programCounter) {
                std::cout << "Trap found!" << std::endl;
                return;
            }
            previousProgramCounter = programCounter;

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
        negativeFlag = ARegister >> 7 != 0;
    }

    void addToARegister(uint8_t b) {
        int sum = ARegister + b;
        if (sum > 0xff) {
            carryFlag = 1;
        }
        ARegister = sum;
        zeroFlag = ARegister == 0;
        negativeFlag = ARegister >> 7 != 0;
    }

    uint8_t getXRegister() const {
        return XRegister;
    }

    void setXRegister(uint8_t xRegister) {
        XRegister = xRegister;
        zeroFlag = XRegister == 0;
        negativeFlag = XRegister >> 7 != 0;
    }

    uint8_t getYRegister() const {
        return YRegister;
    }

    void setYRegister(uint8_t yRegister) {
        YRegister = yRegister;
        zeroFlag = YRegister == 0;
        negativeFlag = YRegister >> 7 != 0;
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

    bool isCarryFlag() const {
        return carryFlag;
    }

    bool isNegativeFlag() const {
        return negativeFlag;
    }

    void setNegativeFlag(bool negativeFlag) {
        CPU::negativeFlag = negativeFlag;
    }

    void setCarryFlag(bool carryFlag) {
        CPU::carryFlag = carryFlag;
    }

    bool isOverflowFlag() const {
        return overflowFlag;
    }

    void setOverflowFlag(bool overflowFlag) {
        CPU::overflowFlag = overflowFlag;
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
                  << " flags N;" << negativeFlag
                  << " V;" << overflowFlag
                  << " -B;" << breakCommandFlag
                  << " D;" << decimalFlag
                  << " I;" << interruptDisableFlag
                  << " Z;" << zeroFlag
                  << " C;" << carryFlag
                  << std::endl;
    }
};
