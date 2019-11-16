#include <iostream>
#include <fstream>
#include <array>
#include "m6502_lib/CPU.cpp"

int main() {
    std::ifstream t;
    int length = 65536;

    t.open("./OS-1.0.ROM");

    auto buffer = new char[length];
    t.read(buffer, length);
    t.close();

    std::array<uint8_t, 65536> mem = {};

    for (int i = 0; i < length; ++i) {
        mem[i] = buffer[i];
    }

    int32_t cycles = 0;

    auto cycleCallback = [&cycles]() -> void
    {
        cycles++;
    };

    auto cpu = CPU(0x440, mem, cycleCallback);
    cpu.setBreakLocation(0xfffe);
    cpu.run();
    std::cout << std::dec << "cycles:" << cycles << std::endl;
    return 0;
}