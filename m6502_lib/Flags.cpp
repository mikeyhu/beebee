#include <cstdint>
#include <string>
#include <sstream>

class Flags {
    bool carryFlag = false;
    bool zeroFlag = false;
    bool interruptDisableFlag = false;
    bool breakCommandFlag = true;
    bool decimalFlag = false;
    bool overflowFlag = false;
    bool negativeFlag = false;


public:
    Flags() {}

    bool isCarryFlag() const {
        return carryFlag;
    }

    void setCarryFlag(bool carryFlag) {
        Flags::carryFlag = carryFlag;
    }

    bool isZeroFlag() const {
        return zeroFlag;
    }

    void setZeroFlag(bool zeroFlag) {
        Flags::zeroFlag = zeroFlag;
    }

    bool isInterruptDisableFlag() const {
        return interruptDisableFlag;
    }

    void setInterruptDisableFlag(bool interruptDisableFlag) {
        Flags::interruptDisableFlag = interruptDisableFlag;
    }

    bool isBreakCommandFlag() const {
        return breakCommandFlag;
    }

    void setBreakCommandFlag(bool breakCommandFlag) {
        Flags::breakCommandFlag = breakCommandFlag;
    }

    bool isDecimalFlag() const {
        return decimalFlag;
    }

    void setDecimalFlag(bool decimalFlag) {
        Flags::decimalFlag = decimalFlag;
    }

    bool isOverflowFlag() const {
        return overflowFlag;
    }

    void setOverflowFlag(bool overflowFlag) {
        Flags::overflowFlag = overflowFlag;
    }

    bool isNegativeFlag() const {
        return negativeFlag;
    }

    void setNegativeFlag(bool negativeFlag) {
        Flags::negativeFlag = negativeFlag;
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
        buffer << " flags N;" << negativeFlag
                       << " V;" << overflowFlag
                       << " -B;" << breakCommandFlag
                       << " D;" << decimalFlag
                       << " I;" << interruptDisableFlag
                       << " Z;" << zeroFlag
                       << " C;" << carryFlag;
        return buffer.str();
    }
};

