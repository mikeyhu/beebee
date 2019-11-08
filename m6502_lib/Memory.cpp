#include <cstdint>
#include <array>
#include <iostream>
template<std::size_t SIZE>

class Memory {
    std::array <uint8_t, SIZE> mem;

    uint16_t toUInt16(uint8_t a, uint8_t b) {
        return b << 8u | a;
    }

public:
    Memory(std::array <uint8_t, SIZE> mem): mem(mem) {};

    uint8_t readUInt8(uint16_t location) {
        return mem[location];
    }

    uint8_t locationZeroPage(uint16_t location) {
        return readUInt8(location);
    }

    uint8_t readZeroPage(uint16_t location) {
        return readUInt8(locationZeroPage(location));
    }

    uint8_t locationZeroPage(uint16_t location, uint8_t reg) {
        return (readUInt8(location) + reg)%0x100;
    }

    uint8_t readZeroPage(uint16_t location, uint8_t reg) {
        return readUInt8(locationZeroPage(location, reg));
    }

    uint16_t readUint16(uint16_t location) {
        auto pcLow = location;
        auto pcHigh = location+1;
        return toUInt16(readUInt8(pcLow), readUInt8(pcHigh));
    }

    void writeUInt8(uint16_t location, uint8_t value) {
        mem[location]=value;
    }

    const std::array<uint8_t, SIZE> &getMemory() const {
        return mem;
    }
};