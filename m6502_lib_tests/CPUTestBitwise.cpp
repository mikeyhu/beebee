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

TEST(CPUBitwise, ArithmeticShiftLeft_Acc) {
    std::array<uint8_t, 16> mem = {LoaDAcc_I, 0x01, ArithmeticShiftLeft_Acc, BReaK};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x02, cpu.getARegister());
}

TEST(CPUBitwise, ArithmeticShiftLeft_Z) {
    std::array<uint8_t, 16> mem = {ArithmeticShiftLeft_Z, 0x03, BReaK, 0x01};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x0, cpu.getARegister());
    EXPECT_EQ(0x2, cpu.getMemoryAt(0x03));
}

TEST(CPUBitwise, ArithmeticShiftLeft_ZX) {
    std::array<uint8_t, 16> mem = {LoaDX_I, 0x02, ArithmeticShiftLeft_ZX, 0x03, BReaK, 0x01};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x0, cpu.getARegister());
    EXPECT_EQ(0x2, cpu.getMemoryAt(0x05));
}

TEST(CPUBitwise, ArithmeticShiftLeft_Ab) {
    std::array<uint8_t, 16> mem = {ArithmeticShiftLeft_Ab, 0x04, 0x00, BReaK, 0x01};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x0, cpu.getARegister());
    EXPECT_EQ(0x2, cpu.getMemoryAt(0x04));
}

TEST(CPUBitwise, ArithmeticShiftLeft_AbX) {
    std::array<uint8_t, 16> mem = {LoaDX_I, 0x02, ArithmeticShiftLeft_AbX, 0x04, 0x00, BReaK, 0x01};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x0, cpu.getARegister());
    EXPECT_EQ(0x2, cpu.getMemoryAt(0x06));
}

TEST(CPUBitwise, LogicalShiftRight_Acc_nonzero) {
    std::array<uint8_t, 16> mem = {LoaDAcc_I, 0x03, LogicalShiftRight_Acc, BReaK};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x01, cpu.getARegister());
    EXPECT_TRUE(cpu.isCarryFlag());
}

TEST(CPUBitwise, LogicalShiftRight_Acc_zero) {
    std::array<uint8_t, 16> mem = {LoaDAcc_I, 0x01, LogicalShiftRight_Acc, BReaK};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x0, cpu.getARegister());
    EXPECT_TRUE(cpu.isZeroFlag());
    EXPECT_TRUE(cpu.isCarryFlag());
}

TEST(CPUBitwise, LogicalShiftRight_Z) {
    std::array<uint8_t, 16> mem = {LogicalShiftRight_Z, 0x03, BReaK, 0x03};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x00, cpu.getARegister());
    EXPECT_EQ(0x01, cpu.getMemoryAt(0x03));
    EXPECT_TRUE(cpu.isCarryFlag());
}

TEST(CPUBitwise, LogicalShiftRight_ZX) {
    std::array<uint8_t, 16> mem = {LoaDX_I, 0x02, LogicalShiftRight_ZX, 0x03, BReaK, 0x03};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x00, cpu.getARegister());
    EXPECT_EQ(0x01, cpu.getMemoryAt(0x05));
    EXPECT_TRUE(cpu.isCarryFlag());
}

TEST(CPUBitwise, LogicalShiftRight_Ab) {
    std::array<uint8_t, 16> mem = {LogicalShiftRight_Ab, 0x04, 0x00, BReaK, 0x03};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x00, cpu.getARegister());
    EXPECT_EQ(0x01, cpu.getMemoryAt(0x04));
    EXPECT_TRUE(cpu.isCarryFlag());
}

TEST(CPUBitwise, LogicalShiftRight_AbX) {
    std::array<uint8_t, 16> mem = {LoaDX_I, 0x02, LogicalShiftRight_AbX, 0x04, 0x00, BReaK, 0x03};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x00, cpu.getARegister());
    EXPECT_EQ(0x01, cpu.getMemoryAt(0x06));
    EXPECT_TRUE(cpu.isCarryFlag());
}

TEST(CPUBitwise, ROtateLeft_Acc) {
    std::array<uint8_t, 16> mem = {LoaDAcc_I, 0x81, ROtateLeft_Acc, BReaK};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x2, cpu.getARegister());
    EXPECT_FALSE(cpu.isZeroFlag());
    EXPECT_TRUE(cpu.isCarryFlag());
}

TEST(CPUBitwise, ROtateLeft_Z) {
    std::array<uint8_t, 16> mem = {ROtateLeft_Z, 0x03, BReaK, 0x81};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x0, cpu.getARegister());
    EXPECT_EQ(0x2, cpu.getMemoryAt(0x03));
    EXPECT_FALSE(cpu.isZeroFlag());
    EXPECT_TRUE(cpu.isCarryFlag());
}

TEST(CPUBitwise, ROtateLeft_ZX) {
    std::array<uint8_t, 16> mem = {LoaDX_I, 0x02, ROtateLeft_ZX, 0x03, BReaK, 0x81};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x0, cpu.getARegister());
    EXPECT_EQ(0x2, cpu.getMemoryAt(0x05));
    EXPECT_FALSE(cpu.isZeroFlag());
    EXPECT_TRUE(cpu.isCarryFlag());
}

TEST(CPUBitwise, ROtateLeft_Ab) {
    std::array<uint8_t, 16> mem = {ROtateLeft_Ab, 0x04, 0x00, BReaK, 0x81};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x0, cpu.getARegister());
    EXPECT_EQ(0x2, cpu.getMemoryAt(0x04));
    EXPECT_FALSE(cpu.isZeroFlag());
    EXPECT_TRUE(cpu.isCarryFlag());
}

TEST(CPUBitwise, ROtateLeft_AbX) {
    std::array<uint8_t, 16> mem = {LoaDX_I, 0x02, ROtateLeft_AbX, 0x04, 0x00, BReaK, 0x81};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x0, cpu.getARegister());
    EXPECT_EQ(0x2, cpu.getMemoryAt(0x06));
    EXPECT_FALSE(cpu.isZeroFlag());
    EXPECT_TRUE(cpu.isCarryFlag());
}

TEST(CPUBitwise, ROtateRight_Acc) {
    std::array<uint8_t, 16> mem = {LoaDAcc_I, 0x3, ROtateRight_Acc, BReaK};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x1, cpu.getARegister());
    EXPECT_FALSE(cpu.isZeroFlag());
    EXPECT_TRUE(cpu.isCarryFlag());
}

TEST(CPUBitwise, ROtateRight_Z) {
    std::array<uint8_t, 16> mem = {ROtateRight_Z, 0x3, BReaK, 0x3};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x0, cpu.getARegister());
    EXPECT_EQ(0x01, cpu.getMemoryAt(0x03));
    EXPECT_FALSE(cpu.isZeroFlag());
    EXPECT_TRUE(cpu.isCarryFlag());
}

TEST(CPUBitwise, ROtateRight_ZX) {
    std::array<uint8_t, 16> mem = {LoaDX_I, 0x02, ROtateRight_ZX, 0x3, BReaK, 0x3};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x0, cpu.getARegister());
    EXPECT_EQ(0x01, cpu.getMemoryAt(0x05));
    EXPECT_FALSE(cpu.isZeroFlag());
    EXPECT_TRUE(cpu.isCarryFlag());
}

TEST(CPUBitwise, ROtateRight_Ab) {
    std::array<uint8_t, 16> mem = {ROtateRight_Ab, 0x4, 0x00, BReaK, 0x3};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x0, cpu.getARegister());
    EXPECT_EQ(0x01, cpu.getMemoryAt(0x04));
    EXPECT_FALSE(cpu.isZeroFlag());
    EXPECT_TRUE(cpu.isCarryFlag());
}

TEST(CPUBitwise, ROtateRight_AbX) {
    std::array<uint8_t, 16> mem = {LoaDX_I, 0x02, ROtateRight_AbX, 0x4, 0x00, BReaK, 0x3};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x0, cpu.getARegister());
    EXPECT_EQ(0x01, cpu.getMemoryAt(0x06));
    EXPECT_FALSE(cpu.isZeroFlag());
    EXPECT_TRUE(cpu.isCarryFlag());
}