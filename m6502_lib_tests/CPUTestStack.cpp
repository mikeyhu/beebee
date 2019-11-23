#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../m6502_lib/CPU.cpp"
#include <cstdint>
#include <array>
#include "Helpers.cpp"

class CPUStack : public ::testing::Test {

};

TEST(CPUStack, TransferXtoStack) {
    std::array<uint8_t, 4> mem = {LoaDX_I, 0xff, TransferXtoStack, BReaK};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.run();
    EXPECT_EQ(0xff, cpu.getStackPointer());
}
// PHA : PusH Accumulator
TEST(CPUStack, PusHAcc) {
    std::array<uint8_t, 0x200> mem = {LoaDX_I, 0xff, TransferXtoStack, LoaDAcc_I, 0x01, PusHAcc, BReaK};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.run();
    EXPECT_EQ(0xfe, cpu.getStackPointer());
    EXPECT_EQ(0x01, cpu.getMemory()[0x1ff]);
}
// PLA : PuLl Accumulator
TEST(CPUStack, PuLlAcc) {
    std::array<uint8_t, 0x200> mem = {LoaDX_I, 0xff, TransferXtoStack, LoaDAcc_I, 0x01, PusHAcc, LoaDAcc_I, 0x02, PuLlAcc, BReaK};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.run();
    EXPECT_EQ(0xff, cpu.getStackPointer());
    EXPECT_EQ(0x01, cpu.getARegister());
    EXPECT_EQ(0x01, cpu.getMemory()[0x1ff]);
}

TEST(CPUStack, TransferStacktoX) {
    std::array<uint8_t, 0x200> mem = {LoaDX_I, 0xfe, TransferXtoStack, LoaDX_I, 0xff, TransferStacktoX, BReaK};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.run();
    EXPECT_EQ(0xfe, cpu.getStackPointer());
    EXPECT_EQ(0xfe, cpu.getXRegister());
}

TEST(CPUStack, PHP_PLP) {
    std::array<uint8_t, 0x5> mem = {PusHProcessorstatus, LoaDAcc_I, 0x01, PuLlProcessorstatus, BReaK};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.setCarryFlag(true);
    cpu.setZeroFlag(true);
    cpu.setDecimalFlag(true);
    cpu.setOverflowFlag(true);
    cpu.setNegativeFlag(true);
    cpu.run();
    EXPECT_EQ(0x05, cpu.getProgramCounter());
    EXPECT_TRUE(cpu.isCarryFlag());
    EXPECT_TRUE(cpu.isZeroFlag());
    EXPECT_TRUE(cpu.isDecimalFlag());
    EXPECT_TRUE(cpu.isOverflowFlag());
    EXPECT_TRUE(cpu.isNegativeFlag());
}

TEST(CPUStack, JumptoSubRoutine_Ab) {
    std::array<uint8_t, 0x200> mem = {LoaDX_I, 0xff, TransferXtoStack, JumptoSubRoutine_Ab, 0x08, 0x00, LoaDAcc_I, 0xff, BReaK};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x00, cpu.getARegister());
    EXPECT_EQ(0xfd, cpu.getStackPointer());
    EXPECT_EQ(0x00, cpu.getMemory()[0x1ff]);
    EXPECT_EQ(0x05, cpu.getMemory()[0x1fe]);
}

TEST(CPUStack, ReTurnfromSubroutine) {
    std::array<uint8_t, 0x200> mem = {LoaDX_I, 0xff, TransferXtoStack, JumptoSubRoutine_Ab, 0x09, 0x00, LoaDAcc_I, 0xff, BReaK, ReTurnfromSubroutine};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.run();
    EXPECT_EQ(0xff, cpu.getARegister());
    EXPECT_EQ(0xff, cpu.getStackPointer());
}

TEST(CPUStack, ReTurnfromInterrupt) {
    std::array<uint8_t, 0x10> mem = {LoaDAcc_I, 0x00, PusHAcc, LoaDAcc_I, 0x0b, PusHAcc, LoaDAcc_I, 0xff, PusHAcc, ReTurnfromInterrupt, BReaK, LoaDX_I, 0xff};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x0e, cpu.getProgramCounter());
    EXPECT_TRUE(cpu.isCarryFlag());
    EXPECT_FALSE(cpu.isZeroFlag());
    EXPECT_TRUE(cpu.isDecimalFlag());
    EXPECT_TRUE(cpu.isOverflowFlag());
    EXPECT_TRUE(cpu.isNegativeFlag());

    EXPECT_EQ(0xff, cpu.getXRegister());
}

