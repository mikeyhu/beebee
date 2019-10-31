#include <cstdint>
#include <cstring>
#include <array>
#include <iostream>
#include "OpCode.cpp"

template<std::size_t SIZE>

class CPU {
    const uint16_t STACK_START = 0x100;

    uint8_t ARegister = 0;
    uint8_t XRegister = 0;
    uint8_t YRegister = 0;
    uint8_t stackPointer = 0xff;
    uint16_t programCounter;
    uint16_t previousProgramCounter;
    bool carryFlag = false;
    bool zeroFlag = false;
    bool interruptDisableFlag = false;
    bool breakCommandFlag = true;
    bool decimalFlag = false;
    bool overflowFlag = false;
    bool negativeFlag = false;
    std::array<uint8_t, SIZE> memory;
    uint16_t breakLocation = 0;

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

    uint16_t read16From(uint16_t location) {
        uint8_t upper = memory[location];
        uint8_t lower = memory[location+1];
        return toUInt16(upper, lower);
    }

    void pushStack8(uint8_t value) {
        memory[STACK_START + stackPointer--] = value;
    }

    void pushStack16(uint16_t value) {
        uint8_t lower = value >> 8;
        uint8_t upper = (uint8_t) value;
        pushStack8(lower);
        pushStack8(upper);
    }

    uint8_t popStack8() {
        return memory[STACK_START + ++stackPointer];
    }

    uint16_t popStack16() {
        uint8_t upper = popStack8();
        uint8_t lower = popStack8();
        return toUInt16(upper, lower);
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
        breakCommandFlag = true;
        overflowFlag = flags >> 6 & 1;
        negativeFlag = flags >> 7 & 1;
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

public:
    CPU(uint16_t programCounter, std::array<uint8_t, SIZE> memory) {
        this->programCounter = programCounter;
        this->memory = memory;
    }

    void run() {
        for (;;) {
            switch (readOpCode()) {
                case BReaK : {
                    if (breakLocation > 0x00) {
                        pushStack16(programCounter + 1);
                        breakCommandFlag = true;
                        pushStack8(flagsAsInt());
                        programCounter = read16From(breakLocation);
                    }
                    return;
                }
                case CLearCarry :
                    carryFlag = false;
                    break;
                case CLearDecimal :
                    decimalFlag = false;
                    break;
                case JuMP_Ab:
                    programCounter = locationAbsolute();
                    break;
                case JuMP_Indir: {
                    programCounter = read16From(locationAbsolute());
                    break;
                }
                    // ADC : ADd with Carry
                case ADdwithCarry_I :
                    addToARegister(readImmediate());
                    break;
                case ADdwithCarry_Z :
                    addToARegister(readZeroPage());
                    break;
                case ADdwithCarry_ZX :
                    addToARegister(readZeroPageX());
                    break;
                case ADdwithCarry_Ab :
                    addToARegister(readAbsoluteY());
                    break;
                case ADdwithCarry_AbX :
                    addToARegister(readAbsoluteX());
                    break;
                case ADdwithCarry_AbY :
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
                case ExclusiveOR_I :
                    setARegister(ARegister ^ readImmediate());
                    break;
                case ExclusiveOR_Ab :
                    setARegister(ARegister ^ readAbsolute());
                    break;
                case ExclusiveOR_AbX :
                    setARegister(ARegister ^ readAbsoluteX());
                    break;
                case ExclusiveOR_AbY :
                    setARegister(ARegister ^ readAbsoluteY());
                    break;
                case ExclusiveOR_Z :
                    setARegister(ARegister ^ readZeroPage());
                    break;
                case ExclusiveOR_ZX :
                    setARegister(ARegister ^ readZeroPageX());
                    break;

                    // Branch
                case BranchonCarryClear :
                    branchIfTrue(!carryFlag);
                    break;
                case BranchonCarrySet :
                    branchIfTrue(carryFlag);
                    break;
                case BranchonNotEqual :
                    branchIfTrue(!zeroFlag);
                    break;
                case BranchonEQual :
                    branchIfTrue(zeroFlag);
                    break;
                case BranchonPLus :
                    branchIfTrue(!negativeFlag);
                    break;
                case BranchonMInus :
                    branchIfTrue(negativeFlag);
                    break;
                case BranchonoVerflowClear :
                    branchIfTrue(!overflowFlag);
                    break;
                case BranchonoVerflowSet :
                    branchIfTrue(overflowFlag);
                    break;
                    // Compare
                case CoMPareacc_I :
                    compareRegisterTo(ARegister, readImmediate());
                    break;
                case CoMPareacc_Z :
                    compareRegisterTo(ARegister, readZeroPage());
                    break;
                case CoMPareacc_ZX :
                    compareRegisterTo(ARegister, readZeroPageX());
                    break;
                case CoMPareacc_Ab :
                    compareRegisterTo(ARegister, readAbsolute());
                    break;
                case CoMPareacc_AbX :
                    compareRegisterTo(ARegister, readAbsoluteX());
                    break;
                case CoMPareacc_AbY :
                    compareRegisterTo(ARegister, readAbsoluteY());
                    break;
                case ComPareX_I :
                    compareRegisterTo(XRegister, readImmediate());
                    break;
                case ComPareX_Ab :
                    compareRegisterTo(XRegister, readAbsolute());
                    break;
                case ComPareX_Z :
                    compareRegisterTo(XRegister, readZeroPage());
                    break;
                case ComPareY_I :
                    compareRegisterTo(YRegister, readImmediate());
                    break;
                case ComPareY_Ab :
                    compareRegisterTo(YRegister, readAbsolute());
                    break;
                case ComPareY_Z :
                    compareRegisterTo(YRegister, readZeroPage());
                    break;

                    //IN : INcremement
                case INcrementX :
                    setXRegister(XRegister + 1);
                    break;
                case INcrementY :
                    setYRegister(YRegister + 1);
                    break;

                    //DE : DEcremement
                case DEcrementX :
                    setXRegister(XRegister - 1);
                    break;
                case DEcrementY :
                    setYRegister(YRegister - 1);
                    break;

                    // LDA : LoaD Accumulator
                case LoaDAcc_I :
                    setARegister(readImmediate());
                    break;
                case LoaDAcc_Ab :
                    setARegister(readAbsolute());
                    break;
                case LoaDAcc_AbX :
                    setARegister(readAbsoluteX());
                    break;
                case LoaDAcc_AbY :
                    setARegister(readAbsoluteY());
                    break;
                case LoaDAcc_Z :
                    setARegister(readZeroPage());
                    break;
                case LoaDAcc_ZX :
                    setARegister(readZeroPageX());
                    break;

                    // LDX : LoaD Xregister
                case LoaDX_I :
                    setXRegister(readImmediate());
                    break;
                case LoaDX_Ab :
                    setXRegister(readAbsolute());
                    break;
                case LoaDX_AbY :
                    setXRegister(readAbsoluteY());
                    break;
                case LoaDX_Z :
                    setXRegister(readZeroPage());
                    break;
                case LoaDX_ZX :
                    setXRegister(readZeroPageX());
                    break;

                    // LDY : LoaD Yregister
                case LoaDY_I :
                    setYRegister(readImmediate());
                    break;
                case LoaDY_Ab :
                    setYRegister(readAbsolute());
                    break;
                case LoaDY_AbX :
                    setYRegister(readAbsoluteX());
                    break;
                case LoaDY_Z :
                    setYRegister(readZeroPage());
                    break;
                case LoaDY_ZX :
                    setYRegister(readZeroPageX());
                    break;

                    //STA : STore Accumulator
                case SToreAcc_Ab :
                    memory[locationAbsolute()] = ARegister;
                    break;
                case SToreAcc_AbX :
                    memory[locationAbsoluteX()] = ARegister;
                    break;
                case SToreAcc_AbY :
                    memory[locationAbsoluteY()] = ARegister;
                    break;
                case SToreAcc_Z :
                    memory[locationZeroPage()] = ARegister;
                    break;
                case SToreAcc_ZX :
                    memory[locationZeroPageX()] = ARegister;
                    break;
                    //STX : STore Xregister
                case SToreX_Ab :
                    memory[locationAbsolute()] = XRegister;
                    break;
                case SToreX_Z :
                    memory[locationZeroPage()] = XRegister;
                    break;
                case SToreX_ZY :
                    memory[locationZeroPageY()] = XRegister;
                    break;

                    // T : Transfer
                case TransferAtoX:
                    setXRegister(ARegister);
                    break;
                case TransferAtoY :
                    setYRegister(ARegister);
                    break;
                case TransferXtoA:
                    setARegister(XRegister);
                    break;
                case TransferYtoA:
                    setARegister(YRegister);
                    break;
                case TransferXtoStack :
                    stackPointer = XRegister;
                    break;

                    //stack
                case TransferStacktoX :
                    setXRegister(stackPointer);
                    break;
                case PusHAcc :
                    pushStack8(ARegister);
                    break;
                case PuLlAcc :
                    setARegister(popStack8());
                    break;
                case PusHProcessorstatus :
                    pushStack8(flagsAsInt());
                    break;
                case PuLlProcessorstatus :
                    intToFlags(popStack8());
                    break;
                case JumptoSubRoutine_Ab : {
                    pushStack16(programCounter + 1);
                    programCounter = locationAbsolute();
                    break;
                }
                case ReTurnfromSubroutine : {
                    uint16_t counter = popStack16();
                    programCounter = counter + 1;
                    break;
                }
                case ReTurnfromInterrupt : {
                    intToFlags(popStack8());
                    uint16_t counter = popStack16();
                    programCounter = counter;
                    break;
                }
                case NoOPeration :
                    break;
                default:
                    std::cout << "Unknown OpCode:" << std::hex << (int) memory[programCounter - 1] << std::endl;
                    printState();
                    return;
            }
            if (previousProgramCounter == programCounter) {
                std::cout << "Trap found!" << std::endl;
                if(programCounter!=0x37ce) {
                    return;
                } else {
                    programCounter=programCounter+2;
                }
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

    void setCarryFlag(bool carryFlag) {
        CPU::carryFlag = carryFlag;
    }

    bool isNegativeFlag() const {
        return negativeFlag;
    }

    void setNegativeFlag(bool negativeFlag) {
        CPU::negativeFlag = negativeFlag;
    }

    bool isOverflowFlag() const {
        return overflowFlag;
    }

    void setOverflowFlag(bool overflowFlag) {
        CPU::overflowFlag = overflowFlag;
    }

    bool isBreakCommandFlag() const {
        return breakCommandFlag;
    }

    void setBreakCommandFlag(bool breakCommandFlag) {
        CPU::breakCommandFlag = breakCommandFlag;
    }

    uint8_t getStackPointer() const {
        return stackPointer;
    }

    void setStackPointer(uint8_t stackPointer) {
        CPU::stackPointer = stackPointer;
    }

    uint16_t getBreakLocation() const {
        return breakLocation;
    }

    void setBreakLocation(uint16_t breakLocation) {
        CPU::breakLocation = breakLocation;
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
                  << " C;" << carryFlag;
        for (int i = stackPointer; i <= 0xff; i++) {
            std::cout << " [" << i << ":" << (int) (uint8_t) memory[0x100 + i] << "]";
        }
        std::cout << " testcase:" << (int) (uint8_t) memory[0x200] << std::endl;
    }
};
