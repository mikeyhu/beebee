#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../m6502_lib/CPU.cpp"
#include "Helpers.cpp"
#include <cstdint>
#include <array>

class CPUBitwise : public ::testing::Test {

};

// AND : bitwise AND with accumulator
TEST(CPUBitwise, AND_I) {
std::array<uint8_t, 5> mem = {LoaDAcc_I, 0xF0, AND_I, 0x8F, BReaK};
auto cpu = CPU(0, mem, cycleCallback);
cpu.run();
EXPECT_EQ(0x80, cpu.getARegister());
}

TEST(CPUBitwise, AND_Ab) {
std::array<uint8_t, 7> mem = {LoaDAcc_I, 0xF0, AND_Ab, 0x06, 0x00, BReaK, 0x8F};
auto cpu = CPU(0, mem, cycleCallback);
cpu.run();
EXPECT_EQ(0x80, cpu.getARegister());
}

TEST(CPUBitwise, AND_AbX) {
std::array<uint8_t, 9> mem = {LoaDX_I, 0x02, LoaDAcc_I, 0xF0, AND_AbX, 0x06, 0x00, BReaK, 0x8F};
auto cpu = CPU(0, mem, cycleCallback);
cpu.run();
EXPECT_EQ(0x80, cpu.getARegister());
}

TEST(CPUBitwise, AND_AbY) {
std::array<uint8_t, 9> mem = {LoaDY_I, 0x02, LoaDAcc_I, 0xF0, AND_AbY, 0x06, 0x00, BReaK, 0x8F};
auto cpu = CPU(0, mem, cycleCallback);
cpu.run();
EXPECT_EQ(0x80, cpu.getARegister());
}

TEST(CPUBitwise, AND_Z) {
std::array<uint8_t, 6> mem = {LoaDAcc_I, 0xF0, AND_Z, 0x05, BReaK, 0x8F};
auto cpu = CPU(0, mem, cycleCallback);
cpu.run();
EXPECT_EQ(0x80, cpu.getARegister());
}

TEST(CPUBitwise, AND_ZX) {
std::array<uint8_t, 9> mem = {LoaDX_I, 0x02, LoaDAcc_I, 0xF0, AND_ZX, 0x05, BReaK, 0x8F};
auto cpu = CPU(0, mem, cycleCallback);
cpu.run();
EXPECT_EQ(0x80, cpu.getARegister());
}

// EOR : bitwise EOR with accumulator
TEST(CPUBitwise, ExclusiveOR_I) {
std::array<uint8_t, 5> mem = {LoaDAcc_I, 0xF0, ExclusiveOR_I, 0x8F, BReaK};
auto cpu = CPU(0, mem, cycleCallback);
cpu.run();
EXPECT_EQ(0x7F, cpu.getARegister());
}

TEST(CPUBitwise, ExclusiveOR_Ab) {
std::array<uint8_t, 7> mem = {LoaDAcc_I, 0xF0, ExclusiveOR_Ab, 0x06, 0x00, BReaK, 0x8F};
auto cpu = CPU(0, mem, cycleCallback);
cpu.run();
EXPECT_EQ(0x7F, cpu.getARegister());
}

TEST(CPUBitwise, ExclusiveOR_AbX) {
std::array<uint8_t, 9> mem = {LoaDX_I, 0x02, LoaDAcc_I, 0xF0, ExclusiveOR_AbX, 0x06, 0x00, BReaK, 0x8F};
auto cpu = CPU(0, mem, cycleCallback);
cpu.run();
EXPECT_EQ(0x7F, cpu.getARegister());
}

TEST(CPUBitwise, ExclusiveOR_AbY) {
std::array<uint8_t, 9> mem = {LoaDY_I, 0x02, LoaDAcc_I, 0xF0, ExclusiveOR_AbY, 0x06, 0x00, BReaK, 0x8F};
auto cpu = CPU(0, mem, cycleCallback);
cpu.run();
EXPECT_EQ(0x7F, cpu.getARegister());
}

TEST(CPUBitwise, ExclusiveOR_Z) {
std::array<uint8_t, 6> mem = {LoaDAcc_I, 0xF0, ExclusiveOR_Z, 0x05, BReaK, 0x8F};
auto cpu = CPU(0, mem, cycleCallback);
cpu.run();
EXPECT_EQ(0x7F, cpu.getARegister());
}

TEST(CPUBitwise, ExclusiveOR_ZX) {
std::array<uint8_t, 9> mem = {LoaDX_I, 0x02, LoaDAcc_I, 0xF0, ExclusiveOR_ZX, 0x05, BReaK, 0x8F};
auto cpu = CPU(0, mem, cycleCallback);
cpu.run();
EXPECT_EQ(0x7F, cpu.getARegister());
}

// ORA : bitwise OR with accumulator
TEST(CPUBitwise, ORwithAcc_I) {
std::array<uint8_t, 5> mem = {LoaDAcc_I, 0xF0, ORwithAcc_I, 0x8F, BReaK};
auto cpu = CPU(0, mem, cycleCallback);
cpu.run();
EXPECT_EQ(0xFF, cpu.getARegister());
}

TEST(CPUBitwise, ORwithAcc_Ab) {
std::array<uint8_t, 7> mem = {LoaDAcc_I, 0xF0, ORwithAcc_Ab, 0x06, 0x00, BReaK, 0x8F};
auto cpu = CPU(0, mem, cycleCallback);
cpu.run();
EXPECT_EQ(0xFF, cpu.getARegister());
}

TEST(CPUBitwise, ORwithAcc_AbX) {
std::array<uint8_t, 9> mem = {LoaDX_I, 0x02, LoaDAcc_I, 0xF0, ORwithAcc_AbX, 0x06, 0x00, BReaK, 0x8F};
auto cpu = CPU(0, mem, cycleCallback);
cpu.run();
EXPECT_EQ(0xFF, cpu.getARegister());
}

TEST(CPUBitwise, ORwithAcc_AbY) {
std::array<uint8_t, 9> mem = {LoaDY_I, 0x02, LoaDAcc_I, 0xF0, ORwithAcc_AbY, 0x06, 0x00, BReaK, 0x8F};
auto cpu = CPU(0, mem, cycleCallback);
cpu.run();
EXPECT_EQ(0xFF, cpu.getARegister());
}

TEST(CPUBitwise, ORwithAcc_Z) {
std::array<uint8_t, 6> mem = {LoaDAcc_I, 0xF0, ORwithAcc_Z, 0x05, BReaK, 0x8F};
auto cpu = CPU(0, mem, cycleCallback);
cpu.run();
EXPECT_EQ(0xFF, cpu.getARegister());
}

TEST(CPUBitwise, ORwithAcc_ZX) {
std::array<uint8_t, 9> mem = {LoaDX_I, 0x02, LoaDAcc_I, 0xF0, ORwithAcc_ZX, 0x05, BReaK, 0x8F};
auto cpu = CPU(0, mem, cycleCallback);
cpu.run();
EXPECT_EQ(0xFF, cpu.getARegister());
}

TEST(CPUBitwise, BIT_Z) {
std::array<uint8_t, 16> mem = {LoaDAcc_I, 0xff, BIT_Z, 0x05, BReaK, 0xff};
auto cpu = CPU(0, mem, cycleCallback);
cpu.run();
EXPECT_FALSE(cpu.isZeroFlag());
EXPECT_TRUE(cpu.isNegativeFlag());
EXPECT_TRUE(cpu.isOverflowFlag());
}

TEST(CPUBitwise, BIT_Ab) {
std::array<uint8_t, 16> mem = {LoaDAcc_I, 0xff, BIT_Ab, 0x06, 0x00, BReaK, 0xff};
auto cpu = CPU(0, mem, cycleCallback);
cpu.run();
EXPECT_FALSE(cpu.isZeroFlag());
EXPECT_TRUE(cpu.isNegativeFlag());
EXPECT_TRUE(cpu.isOverflowFlag());
}

TEST(CPUBitwise, ASL_Ac) {
std::array<uint8_t, 16> mem = {LoaDAcc_I, 0x01, ArithmeticShiftLeft_Ac, BReaK};
auto cpu = CPU(0, mem, cycleCallback);
cpu.run();
EXPECT_EQ(0x02, cpu.getARegister());
}
