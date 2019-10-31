#include <iostream>
#include <fstream>
#include <array>
#include "../m6502_lib/CPU.cpp"

int main() {
    std::ifstream t;
    int length = 65536;

    // from: https://github.com/Klaus2m5/6502_65C02_functional_tests
    t.open("../../m6502_lib_suite/6502_functional_test.bin");

    auto buffer = new char[length];
    t.read(buffer, length);
    t.close();

    std::array<uint8_t, 65536> mem = {};

    for (int i = 0; i < length; ++i) {
        mem[i] = buffer[i];
    }

    auto cpu = CPU(0x400, mem);
    cpu.setBreakLocation(0xfffe);
    cpu.run();
    cpu.run(); //return from break for test 11.
    cpu.run(); //return from break for test 11 at 9f5.
    return 0;
}