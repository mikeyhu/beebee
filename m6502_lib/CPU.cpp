#include <cstdint>
#include <cstring>
#include <array>
#include <iostream>
#include <functional>
#include <map>

#ifndef CLASS_OPCODE
#define CLASS_OPCODE

#include "OpCode.cpp"

#endif

#include "OpLog.cpp"

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
    std::function<void()> cycleCallback;
    std::array<uint8_t, SIZE> memory;
    uint16_t breakLocation = 0;
    bool doBreak = false;

    uint16_t toUInt16(uint8_t a, uint8_t b) {
        return b << 8u | a;
    }

    uint16_t readUInt16() {
        auto pcLow = programCounter++;
        auto pcHigh = programCounter++;
        return toUInt16(memory[pcLow], memory[pcHigh]);
    }

    uint8_t readUInt8() {
        return memory[programCounter++];
    }

    OpCode readOpCode() {
        auto opCode = (OpCode) readUInt8();
        return opCode;
    }

    uint16_t read16From(uint16_t location) {
        uint8_t upper = memory[location];
        uint8_t lower = memory[location + 1];
        return toUInt16(upper, lower);
    }

    void pushStack8(uint8_t value) {
        memory[STACK_START + stackPointer--] = value;
    }

    void pushStack16(uint16_t value) {
        uint8_t lower = value >> 8u;
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
        uint8_t location = I(); //always read immediate to move counter anyway
        if (check) {
            if (location >= 0x80) {
                programCounter = programCounter - 0x100 + location;
            } else {
                programCounter = programCounter + location;
            }
        }
    }

    void compareRegisterTo(uint8_t reg, uint8_t value) {
#ifndef NDEBUG
        std::cout << "CMP reg:" << std::hex << (int) reg << " val:" << (int) value << std::endl;
#endif
        zeroFlag = value == reg;
        carryFlag = reg >= value;
        negativeFlag = reg < value;
    }

    uint8_t flagsAsInt() {
        return carryFlag |
               (zeroFlag << 1u) |
               (interruptDisableFlag << 2u) |
               (decimalFlag << 3u) |
               (true << 4u) |
               (true << 5u) |
               (overflowFlag << 6u) |
               (negativeFlag << 7u);
    }

    void intToFlags(uint8_t flags) {
        carryFlag = flags & 1u;
        zeroFlag = flags >> 1u & 1u;
        interruptDisableFlag = flags >> 2u & 1u;
        decimalFlag = flags >> 3u & 1u;
        breakCommandFlag = true;
        overflowFlag = flags >> 6u & 1u;
        negativeFlag = flags >> 7u & 1u;
    }

    void setFlagsBasedOnValue(uint8_t value) {
        zeroFlag = value == 0u;
        negativeFlag = value >> 7 != 0;
    }

    // Memory Modes
    bool ACC() {
        return true;
    }

    uint8_t I() {
        return readUInt8();
    }

    uint16_t Z() {
        return readUInt8();
    }

    uint16_t ZX() {
        return (Z() + XRegister) % 0x100;
    }

    uint16_t ZY() {
        return (Z() + YRegister) % 0x100;
    }

    uint16_t Ab() {
        return readUInt16();
    }

    uint16_t AbX() {
        return Ab() + XRegister;
    }

    uint16_t AbY() {
        return Ab() + YRegister;
    }

    bool IMP() {
        return false;
    }

    uint16_t INDIR() {
        return read16From(Ab());
    }

    uint16_t IndexIndir() {
        auto zp = (Z() + XRegister) % 0x100;
        return read16From(zp);
    }

    uint16_t IndirIndex() {
        auto zp = readUInt8();
        auto loc = read16From(zp);
        return loc + YRegister;
    }

    // Operations
    void opAddWithCarry(uint8_t value) {
        int sum = ARegister + value;
        if (sum > 0xff) {
            carryFlag = 1;
        }
        overflowFlag = false;
#ifndef NDEBUG
        std::cout << "ADC reg:" << std::hex << (int) ARegister << " val:" << (int) value << " sum:" << (int) sum
                  << std::endl;
#endif
        ARegister = sum;
        zeroFlag = ARegister == 0;
        negativeFlag = ARegister >> 7 != 0;
    }

    void opAddWithCarry(uint16_t location) {
        opAddWithCarry(memory[location]);
    }

    void opArithmeticShiftLeft(bool _) {
        auto setTo = ARegister << 1u;
        setCarryFlag(setTo > 0xff);
        setARegister(setTo);
    }

    void opArithmeticShiftLeft(uint16_t location) {
        auto mem = memory[location];
        auto setTo = mem << 1u;
        setCarryFlag(setTo > 0xff);
        setFlagsBasedOnValue(setTo);
        memory[location] = setTo;
    }

    void opAnd(uint8_t value) {
        setARegister(ARegister & value);
    }

    void opAnd(uint16_t location) {
        opAnd(memory[location]);
    }

    void opBit(uint16_t location) {
        auto mem = memory[location];
#ifndef NDEBUG
        std::cout << std::hex << "BIT A:" << (int) ARegister << " ZP:" << (int) mem << std::endl;
#endif
        auto bit = ARegister & mem;
        setZeroFlag(bit == 0);
        setNegativeFlag((mem & 0x80) << 7);
        setOverflowFlag((mem & 0x40) << 6);
    }

    void opBranchonCarryClear(bool _) {
        branchIfTrue(!carryFlag);
    }

    void opBranchonCarrySet(bool _) {
        branchIfTrue(carryFlag);
    }

    void opBranchOnOverflowClear(bool _) {
        branchIfTrue(!overflowFlag);
    }

    void opBranchOnOverflowSet(bool _) {
        branchIfTrue(overflowFlag);
    }

    void opBranchOnEqual(bool _) {
        branchIfTrue(zeroFlag);
    }

    void opBranchOnNotEqual(bool _) {
        branchIfTrue(!zeroFlag);
    }

    void opBranchOnPlus(bool _) {
        branchIfTrue(!negativeFlag);
    }

    void opBranchOnMinus(bool _) {
        branchIfTrue(negativeFlag);
    }

    void opBreak(bool _) {
        if (breakLocation > 0x00) {
            pushStack16(programCounter + 1);
            breakCommandFlag = true;
            pushStack8(flagsAsInt());
            programCounter = read16From(breakLocation);
        }
        doBreak = true;
    }

    void opClearCarry(uint16_t _) {
        carryFlag = false;
    }

    void opClearDecimal(uint16_t _) {
        decimalFlag = false;
    }

    void opClearInterrupt(uint16_t _) {
        interruptDisableFlag = false;
    }

    void opClearOverflow(uint16_t _) {
        overflowFlag = false;
    }

    void opCompareAcc(uint8_t value) {
        compareRegisterTo(ARegister, value);
    }

    void opCompareAcc(uint16_t location) {
        compareRegisterTo(ARegister, memory[location]);
    }

    void opCompareX(uint16_t location) {
        compareRegisterTo(XRegister, memory[location]);
    }

    void opCompareX(uint8_t value) {
        compareRegisterTo(XRegister, value);
    }

    void opCompareY(uint8_t value) {
        compareRegisterTo(YRegister, value);
    }

    void opCompareY(uint16_t location) {
        compareRegisterTo(YRegister, memory[location]);
    }

    void opDecrement(uint16_t location) {
        auto val = memory[location];
        val = val - 1;
        setFlagsBasedOnValue(val);
        memory[location] = val;
    }

    void opDecrementX(bool _) {
        setXRegister(XRegister - 1);
    }

    void opDecrementY(bool _) {
        setYRegister(YRegister - 1);
    }

    void opExclusiveOR(uint8_t value) {
        setARegister(ARegister ^ value);
    }

    void opExclusiveOR(uint16_t location) {
        opExclusiveOR(memory[location]);
    }

    void opIncrement(uint16_t location) {
        auto val = memory[location];
        val = val + 1;
        setFlagsBasedOnValue(val);
        memory[location] = val;
    }

    void opIncrementX(bool _) {
        setXRegister(XRegister + 1);
    }

    void opIncrementY(bool _) {
        setYRegister(YRegister + 1);
    }

    void opJump(uint16_t location) {
        programCounter = location;
    }

    void opJumpToSubroutine(uint16_t location) {
        pushStack16(programCounter - 1);
        programCounter = location;
    }

    void opORwithAcc(uint8_t value) {
        setARegister(ARegister | value);
    }

    void opORwithAcc(uint16_t location) {
        opORwithAcc(memory[location]);
    }

    void opLoadAcc(uint16_t location) {
        setARegister(memory[location]);
    }

    void opLoadAcc(uint8_t value) {
        setARegister(value);
    }

    void opLoadX(uint8_t value) {
        setXRegister(value);
    }

    void opLoadX(uint16_t location) {
        setXRegister(memory[location]);
    }

    void opLoadY(uint8_t value) {
        setYRegister(value);
    }

    void opLoadY(uint16_t location) {
        setYRegister(memory[location]);
    }

    void opNoop(bool _) {

    }

    void opLogicalShiftRight(bool _) {
        auto setTo = ARegister >> 1u;
        setCarryFlag(ARegister & 1u);
        setARegister(setTo);
    }

    void opLogicalShiftRight(uint16_t location) {
        auto mem = memory[location];
        auto setTo = mem >> 1u;
        setCarryFlag(mem & 1u);
        setFlagsBasedOnValue(setTo);
        memory[location] = setTo;
    }

    void opPushProcessorStatus(bool _) {
        pushStack8(flagsAsInt());
    }

    void opPullProcessorStatus(bool _) {
        intToFlags(popStack8());
    }

    void opPushAcc(bool _) {
        pushStack8(ARegister);
    }

    void opPullAcc(bool _) {
        setARegister(popStack8());
    }

    void opReturnfromInterrupt(uint16_t _) {
        intToFlags(popStack8());
        uint16_t counter = popStack16();
        programCounter = counter;
    }

    void opReturnfromSubroutine(uint16_t _) {
        uint16_t counter = popStack16();
        programCounter = counter + 1;
    }

    void opRotateLeft(bool _) {
        auto setTo = ARegister << 1u | carryFlag;
        setCarryFlag(ARegister & 0x80u);
        setARegister(setTo);
    }

    void opRotateLeft(uint16_t location) {
        auto mem = memory[location];
        auto setTo = mem << 1u | carryFlag;
        setCarryFlag(mem & 0x80u);
        setFlagsBasedOnValue(setTo);
        memory[location] = setTo;
    }

    void opRotateRight(bool _) {
        auto setTo = ARegister >> 1u | (carryFlag << 7u);
        setCarryFlag(ARegister & 0x1u);
        setARegister(setTo);
    }

    void opRotateRight(uint16_t location) {
        auto mem = memory[location];
        auto setTo = mem >> 1u | (carryFlag << 7u);
        setCarryFlag(mem & 0x1u);
        setFlagsBasedOnValue(setTo);
        memory[location] = setTo;
    }

    void opSetCarry(bool _) {
        carryFlag = true;
    }

    void opSetDecimal(bool _) {
        decimalFlag = true;
    }

    void opSetInterrupt(bool _) {
        interruptDisableFlag = true;
    }

    void opSubtractWithCarry(uint16_t location) {
        auto mem = memory[location];
        uint8_t sum = ARegister - mem - !isCarryFlag();
        setFlagsBasedOnValue(sum);
        if (mem > ARegister) {
            setNegativeFlag(true);
        }
        setOverflowFlag(false);
        std::cout << "SBC reg:" << std::hex << (int) ARegister << " val:" << (int) mem << " res:" << (int) sum
                  << std::endl;
        ARegister = sum;
    }

    void opStoreAcc(uint16_t location) {
        memory[location] = ARegister;
    }

    void opStoreX(uint16_t location) {
        memory[location] = XRegister;
    }

    void opStoreY(uint16_t location) {
        memory[location] = YRegister;
    }

    void opTransferAtoX(bool _) {
        setXRegister(ARegister);
    }

    void opTransferAtoY(bool _) {
        setYRegister(ARegister);
    }

    void opTransferStacktoX(bool _) {
        setXRegister(stackPointer);
    }

    void opTransferXtoA(bool _) {
        setARegister(XRegister);
    }

    void opTransferXtoStack(bool _) {
        stackPointer = XRegister;
    }

    void opTransferYtoA(bool _) {
        setARegister(YRegister);
    }

public:
    CPU(uint16_t programCounter, std::array<uint8_t, SIZE> mem, std::function<void()> cycle)
            : memory(mem),
              cycleCallback(cycle) {
        this->programCounter = programCounter;
        this->previousProgramCounter = programCounter;
    }

    void run() {
        for (;;) {
            previousProgramCounter = programCounter;
            auto opCode = readOpCode();
            auto opLog = OpLog(opCode, previousProgramCounter);
            switch (opCode) {
#define OPCODE(name, code, function, mode) case name : function(mode());break;

#include "OpCodeMacro.cpp"

                default:
                    std::cout << "Unknown OpCode:" << std::endl;
#ifndef NDEBUG
                    printState(opLog);
#endif
                    return;
            }
            if (doBreak) {
                doBreak = false;
                return;
            }
            if (previousProgramCounter == programCounter) {
                std::cout << "Trap found!" << std::endl;
                if (programCounter != 0x37ce
                    && programCounter != 0x35c9) {
                    return;
                } else {
                    programCounter = programCounter + 2;
                }
            }
#ifndef NDEBUG
            printState(opLog);
#endif
            cycleCallback();
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
        setFlagsBasedOnValue(aRegister);
    }

    uint8_t getXRegister() const {
        return XRegister;
    }

    void setXRegister(uint8_t xRegister) {
        XRegister = xRegister;
        zeroFlag = XRegister == 0;
        negativeFlag = XRegister >> 7u != 0;
    }

    uint8_t getYRegister() const {
        return YRegister;
    }

    void setYRegister(uint8_t yRegister) {
        YRegister = yRegister;
        zeroFlag = YRegister == 0;
        negativeFlag = YRegister >> 7u != 0;
    }

    bool isDecimalFlag() const {
        return decimalFlag;
    }

    void setDecimalFlag(bool flag) {
        CPU::decimalFlag = flag;
    }

    bool isZeroFlag() const {
        return zeroFlag;
    }

    void setZeroFlag(bool flag) {
        CPU::zeroFlag = flag;
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

    bool isInterruptDisableFlag() const {
        return interruptDisableFlag;
    }

    void setInterruptDisableFlag(bool interruptDisableFlag) {
        CPU::interruptDisableFlag = interruptDisableFlag;
    }

    const std::array<uint8_t, SIZE> &getMemory() const {
        return memory;
    }

    void printState(OpLog opLog) {
        std::cout << opLog.ToString()
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
