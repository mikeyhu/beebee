#include <cstdint>
#include "Memory.cpp"

class PageableMemory: public Memory<0x8000>{
    /*
     * Address space:
     * 0x0000-0x7FFF - Ram
     * 0x8000-0xBFFF - Paged/Sideways
     * 0xC000-0xFFFF - OS
     */

    std::array<uint8_t, 0x4000> os;
public:
    explicit PageableMemory(std::array<uint8_t, 0x8000> &mem)
            : Memory(mem) {}

    void setPageOS(std::array<uint8_t, 0x4000> &mem) {
        os = mem;
    }

    uint8_t getValue(uint16_t location) {
        if(location<0x8000) {
            return memory[location];
        } else if(location>=0xC000) {
            return os[location-0xC000];
        } else {
            exit(1); // Fail paged memory not implemented
        }
    }

    void setValue(uint16_t location, uint8_t value) {
        if(location<0x8000) {
            memory[location] = value;
        } else if(location>=0xC000) {
            os[location-0xC000] = value;
        } else {
            exit(1); // Fail paged memory not implemented
        }
    }
};