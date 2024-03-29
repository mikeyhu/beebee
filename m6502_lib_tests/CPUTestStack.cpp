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
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0xff, cpu.getStackPointer());
}
// PHA : PusH Accumulator
TEST(CPUStack, PusHAcc) {
    std::array<uint8_t, 0x200> mem = {LoaDX_I, 0xff, TransferXtoStack, LoaDAcc_I, 0x01, PusHAcc, BReaK};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0xfe, cpu.getStackPointer());
    EXPECT_EQ(0x01, cpu.getMemoryAt(0x1ff));
}
// PLA : PuLl Accumulator
TEST(CPUStack, PuLlAcc) {
    std::array<uint8_t, 0x200> mem = {LoaDX_I, 0xff, TransferXtoStack, LoaDAcc_I, 0x01, PusHAcc, LoaDAcc_I, 0x02, PuLlAcc, BReaK};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0xff, cpu.getStackPointer());
    EXPECT_EQ(0x01, cpu.getCPUState().getARegister());
    EXPECT_EQ(0x01, cpu.getMemoryAt(0x1ff));
}

TEST(CPUStack, TransferStacktoX) {
    std::array<uint8_t, 0x200> mem = {LoaDX_I, 0xfe, TransferXtoStack, LoaDX_I, 0xff, TransferStacktoX, BReaK};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0xfe, cpu.getStackPointer());
    EXPECT_EQ(0xfe, cpu.getCPUState().getXRegister());
}

TEST(CPUStack, PHP_PLP) {
    std::array<uint8_t, 0x200> mem = {PusHProcessorstatus, LoaDAcc_I, 0x01, PuLlProcessorstatus, BReaK};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.getCPUState().setCarryFlag(true);
    cpu.getCPUState().setZeroFlag(true);
    cpu.getCPUState().setDecimalFlag(true);
    cpu.getCPUState().setOverflowFlag(true);
    cpu.getCPUState().setNegativeFlag(true);
    cpu.run();
    EXPECT_EQ(0x05, cpu.getCPUState().getProgramCounter());
    EXPECT_TRUE(cpu.getCPUState().isCarryFlag());
    EXPECT_TRUE(cpu.getCPUState().isZeroFlag());
    EXPECT_TRUE(cpu.getCPUState().isDecimalFlag());
    EXPECT_TRUE(cpu.getCPUState().isOverflowFlag());
    EXPECT_TRUE(cpu.getCPUState().isNegativeFlag());
}

TEST(CPUStack, JumptoSubRoutine_Ab) {
    std::array<uint8_t, 0x200> mem = {LoaDX_I, 0xff, TransferXtoStack, JumptoSubRoutine_Ab, 0x08, 0x00, LoaDAcc_I, 0xff, BReaK};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x00, cpu.getCPUState().getARegister());
    EXPECT_EQ(0xfd, cpu.getStackPointer());
    EXPECT_EQ(0x00, cpu.getMemoryAt(0x1ff));
    EXPECT_EQ(0x05, cpu.getMemoryAt(0x1fe));
}

TEST(CPUStack, ReTurnfromSubroutine) {
    std::array<uint8_t, 0x200> mem = {LoaDX_I, 0xff, TransferXtoStack, JumptoSubRoutine_Ab, 0x09, 0x00, LoaDAcc_I, 0xff, BReaK, ReTurnfromSubroutine};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0xff, cpu.getCPUState().getARegister());
    EXPECT_EQ(0xff, cpu.getStackPointer());
}

TEST(CPUStack, ReTurnfromInterrupt) {
    std::array<uint8_t, 0x200> mem = {LoaDAcc_I, 0x00, PusHAcc, LoaDAcc_I, 0x0b, PusHAcc, LoaDAcc_I, 0xff, PusHAcc, ReTurnfromInterrupt, BReaK, LoaDX_I, 0xff};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x0e, cpu.getCPUState().getProgramCounter());
    EXPECT_TRUE(cpu.getCPUState().isCarryFlag());
    EXPECT_FALSE(cpu.getCPUState().isZeroFlag());
    EXPECT_TRUE(cpu.getCPUState().isDecimalFlag());
    EXPECT_TRUE(cpu.getCPUState().isOverflowFlag());
    EXPECT_TRUE(cpu.getCPUState().isNegativeFlag());

    EXPECT_EQ(0xff, cpu.getCPUState().getXRegister());
}

