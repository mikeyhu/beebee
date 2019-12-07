#include <cstdint>
#include <iostream>
#include "Memory.cpp"

#ifndef BEEBEE_PAGEABLEMEMORY
#define BEEBEE_PAGEABLEMEMORY
#endif

class PageableMemory: public Memory<0x8000>{
    static const uint8_t NUM_PAGES=0x10;
    static const uint16_t PAGE_SWITCH_LOCATION=0xFE30;

    /*
     * Address space:
     * 0x0000-0x7FFF - Ram
     * 0x8000-0xBFFF - Paged/Sideways
     * 0xC000-0xFFFF - OS
     *
     * Reference: http://beebwiki.mdfs.net/Paged_ROM
     */

    uint8_t currentPage=NUM_PAGES-1;
    std::array<uint8_t, 0x4000> os;
    std::array<std::array<uint8_t, 0x4000>, NUM_PAGES> pages;
public:
    explicit PageableMemory(std::array<uint8_t, 0x8000> &mem)
            : Memory(mem) {}

    void setPageOS(std::array<uint8_t, 0x4000> &mem) {
        os = mem;
    }

    void setPage(std::array<uint8_t, 0x4000> &mem, uint8_t id) {
        if(id>=NUM_PAGES) {
            exit(1002); // Page out of range
        }
        pages[id]=mem;
    }

    uint8_t getValue(uint16_t location) {

        if(location<0x8000) {
#ifndef NDEBUG
            std::cout << "memory read:" << std::hex << (int)memory[location] << " from " << (int)location<<std::endl;
#endif
            return memory[location];
        } else if(location>=0xC000) {
#ifndef NDEBUG
            std::cout << "os read:" << std::hex << (int)os[location-0xC000] << " from " << (int)location<<std::endl;
#endif
            return os[location-0xC000];
        } else {
#ifndef NDEBUG
            std::cout << "page read:" << std::hex << (int)pages[currentPage][location-0x8000] << " from " << (int)location<< " page:" << (int)currentPage << std::endl;
#endif
            return pages[currentPage][location-0x8000];
        }
    }

    void setValue(uint16_t location, uint8_t value) {
#ifndef NDEBUG
        if(location >= 0x7C00 && location <= 0x7FFF) {
            std::cout << "Mode 7 memory write:" << std::hex << (int)value << " to " << (int)location<<std::endl;
        } else {
            std::cout << "memory write:" << std::hex << (int)value << " to " << (int)location<<std::endl;
        }
#endif
        if(location<0x8000) {
            memory[location] = value;
        } else if(location>=0xC000) {
            if(location==PAGE_SWITCH_LOCATION) {
#ifndef NDEBUG
                std::cout << "Page Switch to:" << std::hex << (long)value << std::endl;
#endif
                if(value>=NUM_PAGES) {
                    exit(1003); // Page out of range
                }
                currentPage = value;
            }
            os[location-0xC000] = value;
        } else {
#ifndef NDEBUG
            std::cout << "ERROR write to paged rom:" << std::hex << (int)pages[currentPage][location-0x8000] << " to " << (int)location<< " page:" << (int)currentPage << std::endl;
#endif
        }
    }
};