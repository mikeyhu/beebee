#include <iostream>
#include <fstream>
#include <array>
#include "m6502_lib/CPU.cpp"
#include "m6502_lib/PageableMemory.cpp"

static const uint16_t RAM_SIZE = 0x8000;
static const uint16_t OS_SIZE = 0x4000;
static const uint16_t PAGE_SIZE = 0x4000;

std::array<uint8_t, OS_SIZE> loadFile(std::string filename) {
    std::ifstream t;

    t.open(filename);
    auto buffer = new char[OS_SIZE];
    t.read(buffer, OS_SIZE);
    t.close();

    std::array<uint8_t, OS_SIZE> mem = {};

    for (int i = 0; i < OS_SIZE; ++i) {
        mem[i] = buffer[i];
    }
    delete buffer;
    return mem;
}

int main() {
    auto os = loadFile("./OS-1.0.ROM");

    std::array<uint8_t, 0x8000> mem={};
    int32_t cycles = 0;

    auto cycleCallback = [&cycles]() -> void
    {
        cycles++;
    };

    auto memory = new PageableMemory<0x8000>(mem);
    memory->setPageOS(os);
    auto programCounter = memory->get16Value(0xFFFE);
    auto cpu = CPU(programCounter, *memory, cycleCallback);
    cpu.setBreakLocation(0xfffe);
    cpu.run();
    std::cout << std::dec << "cycles:" << cycles << std::endl;
    delete memory;
    return 0;
}