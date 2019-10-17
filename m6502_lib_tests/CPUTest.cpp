#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../m6502_lib/CPU.cpp"
#include <cstdint>
#include <array>

class CPUTest : public ::testing::Test {

};


TEST(CPUTest, FoundBRK) {
    std::array<uint8_t, 1> mem = {BRK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(1,cpu.getProgramCounter());
}

TEST(CPUTest, LDA_I) {
    std::array<uint8_t, 3> mem = {LDA_I, 0x80, BRK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80,cpu.getARegister());
}

TEST(CPUTest, LDX_I) {
    std::array<uint8_t, 3> mem = {LDX_I, 0x80, BRK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80,cpu.getXRegister());
}

TEST(CPUTest, LDY_I) {
    std::array<uint8_t, 3> mem = {LDY_I, 0x80, BRK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80,cpu.getYRegister());
}

TEST(CPUTest, STA_Z) {
    std::array<uint8_t, 6> mem = {LDA_I, 0x80, STA_Z, 0x05, BRK, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80,cpu.getARegister());
    EXPECT_EQ(0x80,cpu.getMemory()[5]);
}