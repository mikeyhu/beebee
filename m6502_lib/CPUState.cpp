#include <cstdint>
#include <string>
#include <sstream>

class CPUState {
    bool carryFlag = false;
    bool zeroFlag = false;
    bool interruptDisableFlag = false;
    bool breakCommandFlag = true;
    bool decimalFlag = false;
    bool overflowFlag = false;
    bool negativeFlag = false;
    uint8_t ARegister = 0;
    uint8_t XRegister = 0;
    uint8_t YRegister = 0;
    uint8_t stackPointer = 0xff;
    uint16_t programCounter;
    uint16_t previousProgramCounter;

public:
    CPUState() {}

    void setFlagsBasedOnValue(uint8_t value) {
        setZeroFlag(value == 0u);
        setNegativeFlag(value >> 7 != 0);
    }

    bool isCarryFlag() const {
        return carryFlag;
    }

    void setCarryFlag(bool carryFlag) {
        CPUState::carryFlag = carryFlag;
    }

    bool isZeroFlag() const {
        return zeroFlag;
    }

    void setZeroFlag(bool zeroFlag) {
        CPUState::zeroFlag = zeroFlag;
    }

    bool isInterruptDisableFlag() const {
        return interruptDisableFlag;
    }

    void setInterruptDisableFlag(bool interruptDisableFlag) {
        CPUState::interruptDisableFlag = interruptDisableFlag;
    }

    bool isBreakCommandFlag() const {
        return breakCommandFlag;
    }

    void setBreakCommandFlag(bool breakCommandFlag) {
        CPUState::breakCommandFlag = breakCommandFlag;
    }

    bool isDecimalFlag() const {
        return decimalFlag;
    }

    void setDecimalFlag(bool decimalFlag) {
        CPUState::decimalFlag = decimalFlag;
    }

    bool isOverflowFlag() const {
        return overflowFlag;
    }

    void setOverflowFlag(bool overflowFlag) {
        CPUState::overflowFlag = overflowFlag;
    }

    bool isNegativeFlag() const {
        return negativeFlag;
    }

    void setNegativeFlag(bool negativeFlag) {
        CPUState::negativeFlag = negativeFlag;
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

    std::string ToString() {
        std::stringstream buffer;
        buffer << " cpuState N;" << negativeFlag
                       << " V;" << overflowFlag
                       << " -B;" << breakCommandFlag
                       << " D;" << decimalFlag
                       << " I;" << interruptDisableFlag
                       << " Z;" << zeroFlag
                       << " C;" << carryFlag;
        return buffer.str();
    }

    uint8_t getARegister() const {
        return ARegister;
    }

    void setARegister(uint8_t aRegister) {
        ARegister = aRegister;
        setFlagsBasedOnValue(ARegister);
    }

    uint8_t getXRegister() const {
        return XRegister;
    }

    void setXRegister(uint8_t xRegister) {
        XRegister = xRegister;
        setZeroFlag(XRegister == 0);
        setNegativeFlag(XRegister >> 7u != 0);

    }

    uint8_t getYRegister() const {
        return YRegister;
    }

    void setYRegister(uint8_t yRegister) {
        YRegister = yRegister;
        setZeroFlag(YRegister == 0);
        setNegativeFlag(YRegister >> 7u != 0);
    }

    uint8_t getStackPointer() const {
        return stackPointer;
    }

    void setStackPointer(uint8_t stackPointer) {
        CPUState::stackPointer = stackPointer;
    }

    uint16_t getProgramCounter() const {
        return programCounter;
    }

    uint16_t getProgramCounterAndIncrement() {
        return programCounter++;
    }

    void setProgramCounter(uint16_t programCounter) {
        CPUState::programCounter = programCounter;
    }

    uint16_t getPreviousProgramCounter() const {
        return previousProgramCounter;
    }

    void setPreviousProgramCounter(uint16_t previousProgramCounter) {
        CPUState::previousProgramCounter = previousProgramCounter;
    }
};

