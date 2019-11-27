#include <cstdint>
#include <cstring>
#include <array>
#include <iostream>
#include <functional>

#ifndef CLASS_OPCODE
#define CLASS_OPCODE

#include "OpCode.cpp"

#endif

#ifndef BEEBEE_UTILITIES
#define BEEBEE_UTILITIES

#include "Utilities.cpp"

#endif

#include "Memory.cpp"
#include "CPUState.cpp"
#include "OpLog.cpp"

template<std::size_t SIZE>

class CPU {
    const uint16_t STACK_START = 0x100;
    uint8_t stackPointer = 0xff;
    uint16_t programCounter;
    uint16_t previousProgramCounter;
    CPUState cpuState = CPUState();
    std::function<void()> cycleCallback;
    Memory<SIZE> *memory;
    uint16_t breakLocation = 0;
    bool doBreak = false;

    uint8_t readUInt8() {
        return memory->getValue(programCounter++);
    }

    OpCode readOpCode() {
        auto opCode = (OpCode) readUInt8();
        return opCode;
    }

    void pushStack8(uint8_t value) {
        memory->setValue(STACK_START + stackPointer--, value);
    }

    void pushStack16(uint16_t value) {
        uint8_t lower = value >> 8u;
        uint8_t upper = (uint8_t) value;
        pushStack8(lower);
        pushStack8(upper);
    }

    uint8_t popStack8() {
        return memory->getValue(STACK_START + ++stackPointer);
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
        cpuState.setZeroFlag(value == reg);
        cpuState.setCarryFlag(reg >= value);
        cpuState.setNegativeFlag(reg < value);
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
        return (Z() + cpuState.getXRegister()) % 0x100;
    }

    uint16_t ZY() {
        return (Z() + cpuState.getYRegister()) % 0x100;
    }

    uint16_t Ab() {
        auto pcLow = programCounter++;
        programCounter++;
        return memory->get16Value(pcLow);
    }

    uint16_t AbX() {
        return Ab() + cpuState.getXRegister();
    }

    uint16_t AbY() {
        return Ab() + cpuState.getYRegister();
    }

    bool IMP() {
        return false;
    }

    uint16_t INDIR() {
        return memory->get16Value(Ab());
    }

    uint16_t IndexIndir() {
        auto zp = (Z() + cpuState.getXRegister()) % 0x100;
        return memory->get16Value(zp);
    }

    uint16_t IndirIndex() {
        auto zp = readUInt8();
        auto loc = memory->get16Value(zp);
        return loc + cpuState.getYRegister();
    }

    // Operations
    void opAddWithCarry(uint8_t value) {
        int sum = cpuState.getARegister() + value;
        if (sum > 0xff) {
            cpuState.setCarryFlag(1);
        }
        cpuState.setOverflowFlag(false);
#ifndef NDEBUG
        std::cout << "ADC reg:" << std::hex << (int) cpuState.getARegister() << " val:" << (int) value << " sum:"
                  << (int) sum
                  << std::endl;
#endif
        cpuState.setARegister(sum);
        cpuState.setZeroFlag(cpuState.getARegister() == 0);
        cpuState.setNegativeFlag(cpuState.getARegister() >> 7 != 0);
    }

    void opAddWithCarry(uint16_t location) {
        opAddWithCarry(memory->getValue(location));
    }

    void opArithmeticShiftLeft(bool _) {
        auto setTo = cpuState.getARegister() << 1u;
        cpuState.setCarryFlag(setTo > 0xff);
        cpuState.setARegister(setTo);
    }

    void opArithmeticShiftLeft(uint16_t location) {
        auto mem = memory->getValue(location);
        auto setTo = mem << 1u;
        cpuState.setCarryFlag(setTo > 0xff);
        cpuState.setFlagsBasedOnValue(setTo);
        memory->setValue(location, setTo);
    }

    void opAnd(uint8_t value) {
        cpuState.setARegister(cpuState.getARegister() & value);
    }

    void opAnd(uint16_t location) {
        opAnd(memory->getValue(location));
    }

    void opBit(uint16_t location) {
        auto mem = memory->getValue(location);
#ifndef NDEBUG
        std::cout << std::hex << "BIT A:" << (int) cpuState.getARegister() << " ZP:" << (int) mem << std::endl;
#endif
        auto bit = cpuState.getARegister() & mem;
        cpuState.setZeroFlag(bit == 0);
        cpuState.setNegativeFlag((mem & 0x80) << 7);
        cpuState.setOverflowFlag((mem & 0x40) << 6);
    }

    void opBranchonCarryClear(bool _) {
        branchIfTrue(!cpuState.isCarryFlag());
    }

    void opBranchonCarrySet(bool _) {
        branchIfTrue(cpuState.isCarryFlag());
    }

    void opBranchOnOverflowClear(bool _) {
        branchIfTrue(!cpuState.isOverflowFlag());
    }

    void opBranchOnOverflowSet(bool _) {
        branchIfTrue(cpuState.isOverflowFlag());
    }

    void opBranchOnEqual(bool _) {
        branchIfTrue(cpuState.isZeroFlag());
    }

    void opBranchOnNotEqual(bool _) {
        branchIfTrue(!cpuState.isZeroFlag());
    }

    void opBranchOnPlus(bool _) {
        branchIfTrue(!cpuState.isNegativeFlag());
    }

    void opBranchOnMinus(bool _) {
        branchIfTrue(cpuState.isNegativeFlag());
    }

    void opBreak(bool _) {
        if (breakLocation > 0x00) {
            pushStack16(programCounter + 1);
            cpuState.setBreakCommandFlag(true);
            pushStack8(cpuState.flagsAsInt());
            programCounter = memory->get16Value(breakLocation);
        }
        doBreak = true;
    }

    void opClearCarry(uint16_t _) {
        cpuState.setCarryFlag(false);
    }

    void opClearDecimal(uint16_t _) {
        cpuState.setDecimalFlag(false);
    }

    void opClearInterrupt(uint16_t _) {
        cpuState.setInterruptDisableFlag(false);
    }

    void opClearOverflow(uint16_t _) {
        cpuState.setOverflowFlag(false);
    }

    void opCompareAcc(uint8_t value) {
        compareRegisterTo(cpuState.getARegister(), value);
    }

    void opCompareAcc(uint16_t location) {
        compareRegisterTo(cpuState.getARegister(), memory->getValue(location));
    }

    void opCompareX(uint16_t location) {
        compareRegisterTo(cpuState.getXRegister(), memory->getValue(location));
    }

    void opCompareX(uint8_t value) {
        compareRegisterTo(cpuState.getXRegister(), value);
    }

    void opCompareY(uint8_t value) {
        compareRegisterTo(cpuState.getYRegister(), value);
    }

    void opCompareY(uint16_t location) {
        compareRegisterTo(cpuState.getYRegister(), memory->getValue(location));
    }

    void opDecrement(uint16_t location) {
        auto val = memory->getValue(location);
        val = val - 1;
        cpuState.setFlagsBasedOnValue(val);
        memory->setValue(location, val);
    }

    void opDecrementX(bool _) {
        cpuState.setXRegister(cpuState.getXRegister() - 1);
    }

    void opDecrementY(bool _) {
        cpuState.setYRegister(cpuState.getYRegister() - 1);
    }

    void opExclusiveOR(uint8_t value) {
        cpuState.setARegister(cpuState.getARegister() ^ value);
    }

    void opExclusiveOR(uint16_t location) {
        opExclusiveOR(memory->getValue(location));
    }

    void opIncrement(uint16_t location) {
        auto val = memory->getValue(location);
        val = val + 1;
        cpuState.setFlagsBasedOnValue(val);
        memory->setValue(location, val);
    }

    void opIncrementX(bool _) {
        cpuState.setXRegister(cpuState.getXRegister() + 1);
    }

    void opIncrementY(bool _) {
        cpuState.setYRegister(cpuState.getYRegister() + 1);
    }

    void opJump(uint16_t location) {
        programCounter = location;
    }

    void opJumpToSubroutine(uint16_t location) {
        pushStack16(programCounter - 1);
        programCounter = location;
    }

    void opORwithAcc(uint8_t value) {
        cpuState.setARegister(cpuState.getARegister() | value);
    }

    void opORwithAcc(uint16_t location) {
        opORwithAcc(memory->getValue(location));
    }

    void opLoadAcc(uint16_t location) {
        cpuState.setARegister(memory->getValue(location));
    }

    void opLoadAcc(uint8_t value) {
        cpuState.setARegister(value);
    }

    void opLoadX(uint8_t value) {
        cpuState.setXRegister(value);
    }

    void opLoadX(uint16_t location) {
        cpuState.setXRegister(memory->getValue(location));
    }

    void opLoadY(uint8_t value) {
        cpuState.setYRegister(value);
    }

    void opLoadY(uint16_t location) {
        cpuState.setYRegister(memory->getValue(location));
    }

    void opNoop(bool _) {

    }

    void opLogicalShiftRight(bool _) {
        auto setTo = cpuState.getARegister() >> 1u;
        cpuState.setCarryFlag(cpuState.getARegister() & 1u);
        cpuState.setARegister(setTo);
    }

    void opLogicalShiftRight(uint16_t location) {
        auto mem = memory->getValue(location);
        auto setTo = mem >> 1u;
        cpuState.setCarryFlag(mem & 1u);
        cpuState.setFlagsBasedOnValue(setTo);
        memory->setValue(location, setTo);
    }

    void opPushProcessorStatus(bool _) {
        pushStack8(cpuState.flagsAsInt());
    }

    void opPullProcessorStatus(bool _) {
        cpuState.intToFlags(popStack8());
    }

    void opPushAcc(bool _) {
        pushStack8(cpuState.getARegister());
    }

    void opPullAcc(bool _) {
        cpuState.setARegister(popStack8());
    }

    void opReturnfromInterrupt(uint16_t _) {
        cpuState.intToFlags(popStack8());
        uint16_t counter = popStack16();
        programCounter = counter;
    }

    void opReturnfromSubroutine(uint16_t _) {
        uint16_t counter = popStack16();
        programCounter = counter + 1;
    }

    void opRotateLeft(bool _) {
        auto setTo = cpuState.getARegister() << 1u | cpuState.isCarryFlag();
        cpuState.setCarryFlag(cpuState.getARegister() & 0x80u);
        cpuState.setARegister(setTo);
    }

    void opRotateLeft(uint16_t location) {
        auto mem = memory->getValue(location);
        auto setTo = mem << 1u | cpuState.isCarryFlag();
        cpuState.setCarryFlag(mem & 0x80u);
        cpuState.setFlagsBasedOnValue(setTo);
        memory->setValue(location, setTo);
    }

    void opRotateRight(bool _) {
        auto setTo = cpuState.getARegister() >> 1u | (cpuState.isCarryFlag() << 7u);
        cpuState.setCarryFlag(cpuState.getARegister() & 0x1u);
        cpuState.setARegister(setTo);
    }

    void opRotateRight(uint16_t location) {
        auto mem = memory->getValue(location);
        auto setTo = mem >> 1u | (cpuState.isCarryFlag() << 7u);
        cpuState.setCarryFlag(mem & 0x1u);
        cpuState.setFlagsBasedOnValue(setTo);
        memory->setValue(location, setTo);
    }

    void opSetCarry(bool _) {
        cpuState.setCarryFlag(true);
    }

    void opSetDecimal(bool _) {
        cpuState.setDecimalFlag(true);
    }

    void opSetInterrupt(bool _) {
        cpuState.setInterruptDisableFlag(true);
    }

    void opSubtractWithCarry(uint16_t location) {
        auto mem = memory->getValue(location);
        auto previousA = cpuState.getARegister();
        uint8_t sum = previousA - mem - !cpuState.isCarryFlag();
        cpuState.setARegister(sum);
        cpuState.setFlagsBasedOnValue(sum);
        if (mem > previousA) {
            cpuState.setNegativeFlag(true);
        }
        cpuState.setOverflowFlag(false);
        std::cout << "SBC reg:" << std::hex << (int) cpuState.getARegister() << " val:" << (int) mem << " res:"
                  << (int) sum
                  << std::endl;
    }

    void opStoreAcc(uint16_t location) {
        memory->setValue(location, cpuState.getARegister());
    }

    void opStoreX(uint16_t location) {
        memory->setValue(location, cpuState.getXRegister());
    }

    void opStoreY(uint16_t location) {
        memory->setValue(location, cpuState.getYRegister());
    }

    void opTransferAtoX(bool _) {
        cpuState.setXRegister(cpuState.getARegister());
    }

    void opTransferAtoY(bool _) {
        cpuState.setYRegister(cpuState.getARegister());
    }

    void opTransferStacktoX(bool _) {
        cpuState.setXRegister(stackPointer);
    }

    void opTransferXtoA(bool _) {
        cpuState.setARegister(cpuState.getXRegister());
    }

    void opTransferXtoStack(bool _) {
        stackPointer = cpuState.getXRegister();
    }

    void opTransferYtoA(bool _) {
        cpuState.setARegister(cpuState.getYRegister());
    }

public:
    CPU(uint16_t programCounter, Memory<SIZE> &mem, std::function<void()> cycle)
            : memory(&mem),
              cycleCallback(cycle) {
        this->programCounter = programCounter;
        this->previousProgramCounter = programCounter;
    }

    CPU(uint16_t programCounter, std::array<uint8_t, SIZE> mem, std::function<void()> cycle)
            : cycleCallback(cycle) {
        this->memory = new Memory(mem);
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

    uint8_t getStackPointer() const {
        return stackPointer;
    }

    void setStackPointer(uint8_t stackPointer) {
        CPU::stackPointer = stackPointer;
    }

    uint16_t getBreakLocation() const {
        return breakLocation;
    }

    CPUState &getCPUState() {
        return cpuState;
    }

    void setBreakLocation(uint16_t breakLocation) {
        CPU::breakLocation = breakLocation;
    }

    const uint8_t getMemoryAt(uint16_t location) const {
        return memory->getValue(location);
    }

    void printState(OpLog opLog) {
        std::cout << opLog.ToString()
                  << " SP:" << (int) stackPointer;
    }
};
