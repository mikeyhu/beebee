#include <cstdint>
#include <cstring>
#include <array>
#ifndef BEEBEE_UTILITIES
#define BEEBEE_UTILITIES
#include "Utilities.cpp"

#endif


#ifndef BEEBEE_MEMORY
template<std::size_t SIZE>
#define BEEBEE_MEMORY

class Memory {


protected:
    std::array<uint8_t, SIZE> memory;
public:
    explicit Memory(std::array<uint8_t, SIZE> &mem)
            : memory(mem) {}

    virtual uint8_t getValue(uint16_t location) {
        return memory[location];
    }

    virtual void setValue(uint16_t location, uint8_t value) {
        memory[location] = value;
    }

    uint16_t get16Value(uint16_t location) {
        uint8_t upper = getValue(location);
        uint8_t lower = getValue(location + 1);
        return toUInt16(upper, lower);
    }
};

#endif //BEEBEE_MEMORY
