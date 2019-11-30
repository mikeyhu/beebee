#include <cstdint>
#include <iostream>
#include "Memory.cpp"



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
            return memory[location];
        } else if(location>=0xC000) {
            return os[location-0xC000];
        } else {
            return pages[currentPage][location-0x8000];
        }
    }

    void setValue(uint16_t location, uint8_t value) {
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
            exit(1001); // Fail paged memory not implemented
        }
    }
};