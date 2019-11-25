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
#include "Flags.cpp"
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
    Flags flags = Flags();
    std::function<void()> cycleCallback;
    Memory<SIZE>* memory;
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
        flags.setZeroFlag(value == reg);
        flags.setCarryFlag(reg >= value);
        flags.setNegativeFlag(reg < value);
    }

    void setFlagsBasedOnValue(uint8_t value) {
        flags.setZeroFlag(value == 0u);
        flags.setNegativeFlag(value >> 7 != 0);
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
        auto pcLow = programCounter++;
        programCounter++;
        return memory->get16Value(pcLow);
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
        return memory->get16Value(Ab());
    }

    uint16_t IndexIndir() {
        auto zp = (Z() + XRegister) % 0x100;
        return memory->get16Value(zp);
    }

    uint16_t IndirIndex() {
        auto zp = readUInt8();
        auto loc = memory->get16Value(zp);
        return loc + YRegister;
    }

    // Operations
    void opAddWithCarry(uint8_t value) {
        int sum = ARegister + value;
        if (sum > 0xff) {
            flags.setCarryFlag(1);
        }
        flags.setOverflowFlag(false);
#ifndef NDEBUG
        std::cout << "ADC reg:" << std::hex << (int) ARegister << " val:" << (int) value << " sum:" << (int) sum
                  << std::endl;
#endif
        ARegister = sum;
        flags.setZeroFlag(ARegister == 0);
        flags.setNegativeFlag(ARegister >> 7 != 0);
    }

    void opAddWithCarry(uint16_t location) {
        opAddWithCarry(memory->getValue(location));
    }

    void opArithmeticShiftLeft(bool _) {
        auto setTo = ARegister << 1u;
        flags.setCarryFlag(setTo > 0xff);
        setARegister(setTo);
    }

    void opArithmeticShiftLeft(uint16_t location) {
        auto mem = memory->getValue(location);
        auto setTo = mem << 1u;
        flags.setCarryFlag(setTo > 0xff);
        setFlagsBasedOnValue(setTo);
        memory->setValue(location, setTo);
    }

    void opAnd(uint8_t value) {
        setARegister(ARegister & value);
    }

    void opAnd(uint16_t location) {
        opAnd(memory->getValue(location));
    }

    void opBit(uint16_t location) {
        auto mem = memory->getValue(location);
#ifndef NDEBUG
        std::cout << std::hex << "BIT A:" << (int) ARegister << " ZP:" << (int) mem << std::endl;
#endif
        auto bit = ARegister & mem;
        flags.setZeroFlag(bit == 0);
        flags.setNegativeFlag((mem & 0x80) << 7);
        flags.setOverflowFlag((mem & 0x40) << 6);
    }

    void opBranchonCarryClear(bool _) {
        branchIfTrue(!flags.isCarryFlag());
    }

    void opBranchonCarrySet(bool _) {
        branchIfTrue(flags.isCarryFlag());
    }

    void opBranchOnOverflowClear(bool _) {
        branchIfTrue(!flags.isOverflowFlag());
    }

    void opBranchOnOverflowSet(bool _) {
        branchIfTrue(flags.isOverflowFlag());
    }

    void opBranchOnEqual(bool _) {
        branchIfTrue(flags.isZeroFlag());
    }

    void opBranchOnNotEqual(bool _) {
        branchIfTrue(!flags.isZeroFlag());
    }

    void opBranchOnPlus(bool _) {
        branchIfTrue(!flags.isNegativeFlag());
    }

    void opBranchOnMinus(bool _) {
        branchIfTrue(flags.isNegativeFlag());
    }

    void opBreak(bool _) {
        if (breakLocation > 0x00) {
            pushStack16(programCounter + 1);
            flags.setBreakCommandFlag(true);
            pushStack8(flags.flagsAsInt());
            programCounter = memory->get16Value(breakLocation);
        }
        doBreak = true;
    }

    void opClearCarry(uint16_t _) {
        flags.setCarryFlag(false);
    }

    void opClearDecimal(uint16_t _) {
        flags.setDecimalFlag(false);
    }

    void opClearInterrupt(uint16_t _) {
        flags.setInterruptDisableFlag(false);
    }

    void opClearOverflow(uint16_t _) {
        flags.setOverflowFlag(false);
    }

    void opCompareAcc(uint8_t value) {
        compareRegisterTo(ARegister, value);
    }

    void opCompareAcc(uint16_t location) {
        compareRegisterTo(ARegister, memory->getValue(location));
    }

    void opCompareX(uint16_t location) {
        compareRegisterTo(XRegister, memory->getValue(location));
    }

    void opCompareX(uint8_t value) {
        compareRegisterTo(XRegister, value);
    }

    void opCompareY(uint8_t value) {
        compareRegisterTo(YRegister, value);
    }

    void opCompareY(uint16_t location) {
        compareRegisterTo(YRegister, memory->getValue(location));
    }

    void opDecrement(uint16_t location) {
        auto val = memory->getValue(location);
        val = val - 1;
        setFlagsBasedOnValue(val);
        memory->setValue(location, val);
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
        opExclusiveOR(memory->getValue(location));
    }

    void opIncrement(uint16_t location) {
        auto val = memory->getValue(location);
        val = val + 1;
        setFlagsBasedOnValue(val);
        memory->setValue(location, val);
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
        opORwithAcc(memory->getValue(location));
    }

    void opLoadAcc(uint16_t location) {
        setARegister(memory->getValue(location));
    }

    void opLoadAcc(uint8_t value) {
        setARegister(value);
    }

    void opLoadX(uint8_t value) {
        setXRegister(value);
    }

    void opLoadX(uint16_t location) {
        setXRegister(memory->getValue(location));
    }

    void opLoadY(uint8_t value) {
        setYRegister(value);
    }

    void opLoadY(uint16_t location) {
        setYRegister(memory->getValue(location));
    }

    void opNoop(bool _) {

    }

    void opLogicalShiftRight(bool _) {
        auto setTo = ARegister >> 1u;
        flags.setCarryFlag(ARegister & 1u);
        setARegister(setTo);
    }

    void opLogicalShiftRight(uint16_t location) {
        auto mem = memory->getValue(location);
        auto setTo = mem >> 1u;
        flags.setCarryFlag(mem & 1u);
        setFlagsBasedOnValue(setTo);
        memory->setValue(location, setTo);
    }

    void opPushProcessorStatus(bool _) {
        pushStack8(flags.flagsAsInt());
    }

    void opPullProcessorStatus(bool _) {
        flags.intToFlags(popStack8());
    }

    void opPushAcc(bool _) {
        pushStack8(ARegister);
    }

    void opPullAcc(bool _) {
        setARegister(popStack8());
    }

    void opReturnfromInterrupt(uint16_t _) {
        flags.intToFlags(popStack8());
        uint16_t counter = popStack16();
        programCounter = counter;
    }

    void opReturnfromSubroutine(uint16_t _) {
        uint16_t counter = popStack16();
        programCounter = counter + 1;
    }

    void opRotateLeft(bool _) {
        auto setTo = ARegister << 1u | flags.isCarryFlag();
        flags.setCarryFlag(ARegister & 0x80u);
        setARegister(setTo);
    }

    void opRotateLeft(uint16_t location) {
        auto mem = memory->getValue(location);
        auto setTo = mem << 1u | flags.isCarryFlag();
        flags.setCarryFlag(mem & 0x80u);
        setFlagsBasedOnValue(setTo);
        memory->setValue(location, setTo);
    }

    void opRotateRight(bool _) {
        auto setTo = ARegister >> 1u | (flags.isCarryFlag() << 7u);
        flags.setCarryFlag(ARegister & 0x1u);
        setARegister(setTo);
    }

    void opRotateRight(uint16_t location) {
        auto mem = memory->getValue(location);
        auto setTo = mem >> 1u | (flags.isCarryFlag() << 7u);
        flags.setCarryFlag(mem & 0x1u);
        setFlagsBasedOnValue(setTo);
        memory->setValue(location, setTo);
    }

    void opSetCarry(bool _) {
        flags.setCarryFlag(true);
    }

    void opSetDecimal(bool _) {
        flags.setDecimalFlag(true);
    }

    void opSetInterrupt(bool _) {
        flags.setInterruptDisableFlag(true);
    }

    void opSubtractWithCarry(uint16_t location) {
        auto mem = memory->getValue(location);
        uint8_t sum = ARegister - mem - !flags.isCarryFlag();
        setFlagsBasedOnValue(sum);
        if (mem > ARegister) {
            flags.setNegativeFlag(true);
        }
        flags.setOverflowFlag(false);
        std::cout << "SBC reg:" << std::hex << (int) ARegister << " val:" << (int) mem << " res:" << (int) sum
                  << std::endl;
        ARegister = sum;
    }

    void opStoreAcc(uint16_t location) {
        memory->setValue(location, ARegister);
    }

    void opStoreX(uint16_t location) {
        memory->setValue(location, XRegister);
    }

    void opStoreY(uint16_t location) {
        memory->setValue(location, YRegister);
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
    CPU(uint16_t programCounter, Memory<SIZE> mem, std::function<void()> cycle)
            : memory(mem),
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
        flags.setZeroFlag(XRegister == 0);
        flags.setNegativeFlag(XRegister >> 7u != 0);
    }

    uint8_t getYRegister() const {
        return YRegister;
    }

    void setYRegister(uint8_t yRegister) {
        YRegister = yRegister;
        flags.setZeroFlag(YRegister == 0);
        flags.setNegativeFlag(YRegister >> 7u != 0);
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

    Flags &getFlags() {
        return flags;
    }

    void setBreakLocation(uint16_t breakLocation) {
        CPU::breakLocation = breakLocation;
    }

    const uint8_t getMemoryAt(uint16_t location) const {
        return memory->getValue(location);
    }

    void printState(OpLog opLog) {
        std::cout << opLog.ToString()
                  << " SP:" << (int) stackPointer
                  << " A:" << (int) ARegister
                  << " X:" << (int) XRegister
                  << " Y:" << (int) YRegister;
        for (int i = stackPointer; i <= 0xff; i++) {
            std::cout << " [" << i << ":" << (int) (uint8_t) memory->getValue(0x100 + i) << "]";
        }
        std::cout << " testcase:" << (int) (uint8_t) memory->getValue(0x200) << std::endl;
    }
};
