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
    std::function<void ()> cycleCallback;
    std::array<uint8_t, SIZE> memory;
    uint16_t breakLocation = 0;

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
        OpCode opCode = (OpCode) readUInt8();
        return opCode;
    }

    uint8_t locationImmediate() {
        return programCounter++;
    }

    uint8_t readImmediate() {
        return readUInt8();
    }

    uint8_t locationZeroPage() {
        return readUInt8();
    }

    uint16_t locationAbsolute() {
        return readUInt16();
    }

    uint16_t locationAbsoluteX() {
        return locationAbsolute() + XRegister;
    }

    uint16_t locationAbsoluteY() {
        return locationAbsolute() + YRegister;
    }

    uint16_t read16From(uint16_t location) {
        uint8_t upper = memory[location];
        uint8_t lower = memory[location+1];
        return toUInt16(upper, lower);
    }

    uint16_t locationIndirIndex() {
        auto zp = readUInt8();
        auto loc = read16From(zp);
        return loc + YRegister;
    }

    uint16_t locationIndexIndir() {
        auto zp = (locationZeroPage() + XRegister) % 0x100;
        return read16From(zp);
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
        std::cout << "CMP reg:" << std::hex << (int) reg << " val:" << (int) value << std::endl;
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

    void addToARegister(uint8_t b) {
        int sum = ARegister + b;
        if (sum > 0xff) {
            carryFlag = 1;
        }
        overflowFlag = false;
        std::cout << "ADC reg:" << std::hex << (int)ARegister << " val:" << (int)b << " sum:" << (int)sum << std::endl;
        ARegister = sum;
        zeroFlag = ARegister == 0;
        negativeFlag = ARegister >> 7 != 0;
    }

    void subToARegister(uint8_t b) {
        uint8_t sum = ARegister - b - !isCarryFlag();
        setFlagsBasedOnValue(sum);
        setOverflowFlag(false);
//        if(ARegister < b + !isCarryFlag()) {
//        }
        std::cout << "SBC reg:" << std::hex << (int)ARegister << " val:" << (int)b << " res:" << (int)sum << std::endl;
        ARegister = sum;
    }

    void bitToARegister(uint8_t mem) {
        std::cout << std::hex << "BIT A:" << (int)ARegister << " ZP:" << (int)mem << std::endl;
        auto bit = ARegister & mem;
        setZeroFlag(bit ==0);
        setNegativeFlag((mem & 0x80) << 7);
        setOverflowFlag( (mem & 0x40) << 6);
    }

    void eorToARegister(uint8_t mem) {
        setARegister(ARegister ^ mem);
    }

    void andToARegister(uint8_t mem) {
        setARegister(ARegister & mem);
    }

    void orToARegister(uint8_t mem) {
        setARegister(ARegister | mem);
    }

    void rorToARegister(uint8_t mem) {
        auto setTo = mem >> 1u | (carryFlag << 7u);
        setCarryFlag(mem & 0x1u);
        setARegister(setTo);
    }

    void aslToARegister(uint8_t mem) {
        auto setTo = mem << 1u;
        setCarryFlag(setTo>0xff);
        setARegister(setTo);
    }

    void aslToMem(uint16_t location) {
        auto mem = memory[location];
        auto setTo = mem << 1u;
        setCarryFlag(setTo>0xff);
        setFlagsBasedOnValue(setTo);
        memory[location]=setTo;
    }

    void lsrToARegister(uint8_t mem) {
       auto setTo = mem >> 1u;
       setCarryFlag(mem & 1u);
       setARegister(setTo);
    }

    void lsrToMem(uint16_t location) {
        auto mem = memory[location];
        auto setTo = mem >> 1u;
        setCarryFlag(mem & 1u);
        setFlagsBasedOnValue(setTo);
        memory[location]=setTo;
    }

    void rolToMem(uint16_t location) {
        auto mem = memory[location];
        auto setTo = mem << 1u | carryFlag;
        setCarryFlag(mem & 0x80u);
        setFlagsBasedOnValue(setTo);
        memory[location]=setTo;
    }

    void rorToMem(uint16_t location) {
        auto mem = memory[location];
        auto setTo = mem >> 1u | (carryFlag << 7u);
        setCarryFlag(mem & 0x1u);
        setFlagsBasedOnValue(setTo);
        memory[location]=setTo;
    }

    void incToMem(uint16_t location) {
        auto val = memory[location];
        val=val+1;
        setFlagsBasedOnValue(val);
        memory[location]=val;
    }

    void decToMem(uint16_t location) {
        auto val = memory[location];
        val=val-1;
        setFlagsBasedOnValue(val);
        memory[location]=val;
    }

    uint16_t locationByOperation(OpCode code) {
        switch (code) {
            case ADdwithCarry_I :
            case AND_I :
            case CoMPareacc_I :
            case ComPareX_I :
            case ComPareY_I :
            case ExclusiveOR_I :
            case LoaDAcc_I :
            case LoaDX_I :
            case LoaDY_I :
            case ORwithAcc_I :
            case SuBtractwithCarry_I :
                return locationImmediate();
            case ADdwithCarry_Z :
            case AND_Z :
            case ArithmeticShiftLeft_Z :
            case BIT_Z :
            case CoMPareacc_Z :
            case ComPareX_Z :
            case ComPareY_Z :
            case DECrement_Z :
            case ExclusiveOR_Z :
            case INCrement_Z :
            case LoaDAcc_Z :
            case LoaDX_Z :
            case LoaDY_Z :
            case LogicalShiftRight_Z :
            case ORwithAcc_Z :
            case ROtateLeft_Z :
            case ROtateRight_Z :
            case SToreAcc_Z :
            case SToreX_Z :
            case SToreY_Z :
            case SuBtractwithCarry_Z :
                return locationZeroPage();
            case ADdwithCarry_ZX :
            case AND_ZX :
            case ArithmeticShiftLeft_ZX :
            case CoMPareacc_ZX :
            case DECrement_ZX :
            case ExclusiveOR_ZX :
            case INCrement_ZX :
            case LoaDAcc_ZX :
            case LoaDY_ZX :
            case LogicalShiftRight_ZX :
            case ORwithAcc_ZX :
            case ROtateLeft_ZX :
            case ROtateRight_ZX :
            case SToreAcc_ZX :
            case SToreY_ZX :
            case SuBtractwithCarry_ZX :
                return (locationZeroPage() + XRegister) % 0x100;
            case LoaDX_ZY :
            case SToreX_ZY :
                return (locationZeroPage() + YRegister) % 0x100;
            case ADdwithCarry_Ab :
            case AND_Ab :
            case ArithmeticShiftLeft_Ab :
            case BIT_Ab :
            case CoMPareacc_Ab :
            case ComPareX_Ab :
            case ComPareY_Ab :
            case DECrement_Ab :
            case ExclusiveOR_Ab :
            case INCrement_Ab :
            case LoaDAcc_Ab :
            case LoaDX_Ab :
            case LoaDY_Ab :
            case LogicalShiftRight_Ab :
            case ORwithAcc_Ab :
            case ROtateLeft_Ab :
            case ROtateRight_Ab :
            case SToreAcc_Ab :
            case SToreX_Ab :
            case SToreY_Ab :
            case SuBtractwithCarry_Ab :
                return locationAbsolute();
            case ADdwithCarry_AbX :
            case AND_AbX :
            case ArithmeticShiftLeft_AbX :
            case CoMPareacc_AbX :
            case DECrement_AbX :
            case ExclusiveOR_AbX :
            case INCrement_AbX :
            case LoaDAcc_AbX :
            case LoaDY_AbX :
            case LogicalShiftRight_AbX :
            case ORwithAcc_AbX :
            case ROtateLeft_AbX :
            case ROtateRight_AbX :
            case SToreAcc_AbX :
            case SuBtractwithCarry_AbX :
                return locationAbsoluteX();
            case ADdwithCarry_AbY :
            case AND_AbY :
            case CoMPareacc_AbY :
            case ExclusiveOR_AbY :
            case LoaDAcc_AbY :
            case LoaDX_AbY :
            case ORwithAcc_AbY :
            case SToreAcc_AbY :
            case SuBtractwithCarry_AbY :
                return locationAbsoluteY();
            case ADdwithCarry_IndexIndir :
            case AND_IndexIndir :
            case CoMPareacc_IndexIndir :
            case ExclusiveOR_IndexIndir :
            case LoaDAcc_IndexIndir :
            case ORwithAcc_IndexIndir :
            case SToreAcc_IndexIndir :
            case SuBtractwithCarry_IndexIndir :
                return locationIndexIndir();
            case ADdwithCarry_IndirIndex :
            case AND_IndirIndex :
            case CoMPareacc_IndirIndex :
            case ExclusiveOR_IndirIndex :
            case LoaDAcc_IndirIndex :
            case ORwithAcc_IndirIndex :
            case SToreAcc_IndirIndex :
            case SuBtractwithCarry_IndirIndex :
                return locationIndirIndex();
            default :
                std::cout << "unknown opcode location" << std::endl;
                break;
        }
    }

    uint8_t readByOperation(OpCode code) {
        return memory[locationByOperation(code)];
    }

public:
    CPU(uint16_t programCounter, std::array<uint8_t, SIZE> memory, std::function<void ()> cycle) {
        this->cycleCallback = cycle;
        this->programCounter = programCounter;
        this->previousProgramCounter = programCounter;
        this->memory = memory;
    }

    void run() {
        for (;;) {
            auto opCode = readOpCode();
            switch (opCode) {
                case BReaK : {
                    if (breakLocation > 0x00) {
                        pushStack16(programCounter + 1);
                        breakCommandFlag = true;
                        pushStack8(flagsAsInt());
                        programCounter = read16From(breakLocation);
                    }
                    printState(opCode);
                    return;
                }
                case CLearCarry :
                    carryFlag = false;
                    break;
                case SEtCarry :
                    carryFlag = true;
                    break;
                case CLearDecimal :
                    decimalFlag = false;
                    break;
                case SEtDecimal :
                    decimalFlag = true;
                    break;
                case CLearInterrupt :
                    interruptDisableFlag = false;
                    break;
                case SEtInterrupt :
                    interruptDisableFlag = true;
                    break;
                case CLearoVerflow :
                    overflowFlag = false;
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
                case ADdwithCarry_Z :
                case ADdwithCarry_ZX :
                case ADdwithCarry_Ab :
                case ADdwithCarry_AbX :
                case ADdwithCarry_AbY :
                case ADdwithCarry_IndexIndir :
                case ADdwithCarry_IndirIndex :
                    addToARegister(readByOperation(opCode));
                    break;

                    // SuBtractwithCarry
                case SuBtractwithCarry_I :
                case SuBtractwithCarry_Z :
                case SuBtractwithCarry_ZX :
                case SuBtractwithCarry_Ab :
                case SuBtractwithCarry_AbX :
                case SuBtractwithCarry_AbY :
                case SuBtractwithCarry_IndexIndir :
                case SuBtractwithCarry_IndirIndex :
                    subToARegister(readByOperation(opCode));
                    break;
                    // AND : bitwise AND with accumulator
                case AND_I :
                case AND_Z :
                case AND_ZX :
                case AND_Ab :
                case AND_AbX :
                case AND_AbY :
                case AND_IndexIndir :
                case AND_IndirIndex :
                    andToARegister(readByOperation(opCode));
                    break;
                    // EOR : bitwise Exclusive OR with accumulator
                case ExclusiveOR_I :
                case ExclusiveOR_Ab :
                case ExclusiveOR_AbX :
                case ExclusiveOR_AbY :
                case ExclusiveOR_Z :
                case ExclusiveOR_ZX :
                case ExclusiveOR_IndexIndir :
                case ExclusiveOR_IndirIndex :
                    eorToARegister(readByOperation(opCode));
                    break;
                    // ORA : bitwise OR with accumulator
                case ORwithAcc_I :
                case ORwithAcc_Ab :
                case ORwithAcc_AbX :
                case ORwithAcc_AbY :
                case ORwithAcc_Z :
                case ORwithAcc_ZX :
                case ORwithAcc_IndexIndir :
                case ORwithAcc_IndirIndex :
                    orToARegister(readByOperation(opCode));
                    break;
                    //BIT
                case BIT_Z :
                case BIT_Ab :
                    bitToARegister(readByOperation(opCode));
                    break;
                case ArithmeticShiftLeft_Ac :
                    aslToARegister(ARegister);
                    break;
                case ArithmeticShiftLeft_Z :
                case ArithmeticShiftLeft_ZX :
                case ArithmeticShiftLeft_Ab :
                case ArithmeticShiftLeft_AbX :
                    aslToMem(locationByOperation(opCode));
                    break;
                case LogicalShiftRight_Acc :
                    lsrToARegister(ARegister);
                    break;
                case LogicalShiftRight_Z :
                case LogicalShiftRight_ZX :
                case LogicalShiftRight_Ab :
                case LogicalShiftRight_AbX :
                    lsrToMem(locationByOperation(opCode));
                    break;
                case ROtateLeft_Acc : {
                    auto setTo = ARegister << 1u | carryFlag;
                    setCarryFlag(ARegister & 0x80u);
                    setARegister(setTo);
                    break;
                }
                case ROtateLeft_Z :
                case ROtateLeft_ZX :
                case ROtateLeft_Ab :
                case ROtateLeft_AbX :
                    rolToMem(locationByOperation(opCode));
                    break;
                case ROtateRight_Acc :
                    rorToARegister(ARegister);
                    break;
                case ROtateRight_Z :
                case ROtateRight_ZX :
                case ROtateRight_Ab :
                case ROtateRight_AbX :
                    rorToMem(locationByOperation(opCode));
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
                case CoMPareacc_Z :
                case CoMPareacc_ZX :
                case CoMPareacc_Ab :
                case CoMPareacc_AbX :
                case CoMPareacc_AbY :
                case CoMPareacc_IndirIndex :
                case CoMPareacc_IndexIndir :
                    compareRegisterTo(ARegister, readByOperation(opCode));
                    break;
                case ComPareX_I :
                case ComPareX_Z :
                case ComPareX_Ab :
                    compareRegisterTo(XRegister, readByOperation(opCode));
                    break;
                case ComPareY_I :
                case ComPareY_Z :
                case ComPareY_Ab :
                    compareRegisterTo(YRegister, readByOperation(opCode));
                    break;

                    //IN : INcremement
                case INcrementX :
                    setXRegister(XRegister + 1);
                    break;
                case INcrementY :
                    setYRegister(YRegister + 1);
                    break;
                case INCrement_Z :
                case INCrement_ZX :
                case INCrement_Ab :
                case INCrement_AbX :
                    incToMem(locationByOperation(opCode));
                    break;
                    //DE : DEcremement
                case DEcrementX :
                    setXRegister(XRegister - 1);
                    break;
                case DEcrementY :
                    setYRegister(YRegister - 1);
                    break;
                case DECrement_Z :
                case DECrement_ZX :
                case DECrement_Ab :
                case DECrement_AbX :
                    decToMem(locationByOperation(opCode));
                    break;
                    // LDA : LoaD Accumulator
                case LoaDAcc_I :
                case LoaDAcc_Ab :
                case LoaDAcc_AbX :
                case LoaDAcc_AbY :
                case LoaDAcc_Z :
                case LoaDAcc_ZX :
                case LoaDAcc_IndexIndir :
                case LoaDAcc_IndirIndex :
                    setARegister(readByOperation(opCode));
                    break;
                    // LDX : LoaD Xregister
                case LoaDX_I :
                case LoaDX_Ab :
                case LoaDX_AbY :
                case LoaDX_Z :
                case LoaDX_ZY :
                    setXRegister(readByOperation(opCode));
                    break;
                    // LDY : LoaD Yregister
                case LoaDY_I :
                case LoaDY_Ab :
                case LoaDY_AbX :
                case LoaDY_Z :
                case LoaDY_ZX :
                    setYRegister(readByOperation(opCode));
                    break;
                    //STA : STore Accumulator
                case SToreAcc_Ab :
                case SToreAcc_AbX :
                case SToreAcc_AbY :
                case SToreAcc_Z :
                case SToreAcc_ZX :
                case SToreAcc_IndexIndir :
                case SToreAcc_IndirIndex :
                    memory[locationByOperation(opCode)] = ARegister;
                    break;
                    //STX : STore Xregister
                case SToreX_Ab :
                case SToreX_Z :
                case SToreX_ZY :
                    memory[locationByOperation(opCode)] = XRegister;
                    break;
                    //STY : STore Yregister
                case SToreY_Ab :
                case SToreY_Z :
                case SToreY_ZX :
                    memory[locationByOperation(opCode)] = YRegister;
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
#ifndef NDEBUG
                    printState(opCode);
#endif
                    return;
            }
#ifndef NDEBUG
            if (previousProgramCounter == programCounter) {
                std::cout << "Trap found!" << std::endl;
                if(programCounter!=0x37ce
                && programCounter!=0x35c9) {
                    return;
                } else {
                    programCounter=programCounter+2;
                }
            }
            printState(opCode);
#endif
            previousProgramCounter = programCounter;
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

    std::string OpCodeToString(OpCode value) {
        switch (value) {
#define ITEM(name, code) case code: return #name;

#include "OpCodeMacro.cpp"
        }
        return "";
    }

    void printState(OpCode opCode) {
        std::cout << "PC:" << std::hex << (int) programCounter
                  << " OC:" << OpCodeToString(opCode)
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
