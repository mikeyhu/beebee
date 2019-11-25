#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../m6502_lib/CPU.cpp"
#include <cstdint>
#include <array>
#include "Helpers.cpp"

class CPUBranch : public ::testing::Test {

};

// BNE : Branch on Not Equal (backwards is relative is > 0x80, otherwise forwards)
TEST(CPUBranch, BNE_backwards) {
    std::array<uint8_t, 16> mem = {LoaDX_I, 0x08, DEcrementX, SToreX_Ab, 0x0e, 0x00, ComPareX_I, 0x03, BranchonNotEqual,
                                   0xf8, SToreX_Ab, 0x0f, 0x00,
                                   0x00, 0x00, 0x00};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x03, cpu.getMemoryAt(14));
    EXPECT_EQ(0x03, cpu.getMemoryAt(15));
}

TEST(CPUBranch, BNE_forwards) {
    std::array<uint8_t, 16> mem = {LoaDX_I, 0x08, ComPareX_I, 0x07, BranchonNotEqual, 0x02, LoaDY_I, 0x01, LoaDAcc_I,
                                   0x01, 0x00};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x00, cpu.getYRegister());
    EXPECT_EQ(0x01, cpu.getARegister());
}

TEST(CPUBranch, BEQ_forwards) {
    std::array<uint8_t, 16> mem = {LoaDX_I, 0x08, ComPareX_I, 0x08, BranchonEQual, 0x02, LoaDY_I, 0x01, LoaDAcc_I, 0x01,
                                   0x00};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x00, cpu.getYRegister());
    EXPECT_EQ(0x01, cpu.getARegister());
}

TEST(CPUBranch, BPL_if_positive) {
    std::array<uint8_t, 16> mem = {LoaDX_I, 0x08, BranchonPLus, 0x02, LoaDY_I, 0x01, LoaDAcc_I, 0x01, 0x00};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x00, cpu.getYRegister());
    EXPECT_EQ(0x01, cpu.getARegister());
}

TEST(CPUBranch, BPL_if_negative) {
    std::array<uint8_t, 16> mem = {LoaDX_I, 0x88, BranchonPLus, 0x02, LoaDY_I, 0x01, LoaDAcc_I, 0x01, 0x00};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x01, cpu.getYRegister());
    EXPECT_EQ(0x01, cpu.getARegister());
}

TEST(CPUBranch, BCC_if_true) {
    std::array<uint8_t, 16> mem = {BranchonCarryClear, 0x02, LoaDY_I, 0x01, LoaDAcc_I, 0x01, 0x00};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.setCarryFlag(true);
    cpu.run();
    EXPECT_EQ(0x01, cpu.getYRegister());
    EXPECT_EQ(0x01, cpu.getARegister());
}

TEST(CPUBranch, BCC_if_false) {
    std::array<uint8_t, 16> mem = {BranchonCarryClear, 0x02, LoaDY_I, 0x01, LoaDAcc_I, 0x01, 0x00};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.setCarryFlag(false);
    cpu.run();
    EXPECT_EQ(0x00, cpu.getYRegister());
    EXPECT_EQ(0x01, cpu.getARegister());
}

TEST(CPUBranch, BCS_if_true) {
    std::array<uint8_t, 16> mem = {BranchonCarrySet, 0x02, LoaDY_I, 0x01, LoaDAcc_I, 0x01, 0x00};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.setCarryFlag(true);
    cpu.run();
    EXPECT_EQ(0x00, cpu.getYRegister());
    EXPECT_EQ(0x01, cpu.getARegister());
}

TEST(CPUBranch, BCS_if_false) {
    std::array<uint8_t, 16> mem = {BranchonCarrySet, 0x02, LoaDY_I, 0x01, LoaDAcc_I, 0x01, 0x00};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.setCarryFlag(false);
    cpu.run();
    EXPECT_EQ(0x01, cpu.getYRegister());
    EXPECT_EQ(0x01, cpu.getARegister());
}

TEST(CPUBranch, BMI_if_true) {
    std::array<uint8_t, 16> mem = {BranchonMInus, 0x02, LoaDY_I, 0x01, LoaDAcc_I, 0x01, 0x00};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.setNegativeFlag(true);
    cpu.run();
    EXPECT_EQ(0x00, cpu.getYRegister());
    EXPECT_EQ(0x01, cpu.getARegister());
}

TEST(CPUBranch, BMI_if_false) {
    std::array<uint8_t, 16> mem = {BranchonMInus, 0x02, LoaDY_I, 0x01, LoaDAcc_I, 0x01, 0x00};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.setNegativeFlag(false);
    cpu.run();
    EXPECT_EQ(0x01, cpu.getYRegister());
    EXPECT_EQ(0x01, cpu.getARegister());
}

TEST(CPUBranch, BVC_if_false) {
    std::array<uint8_t, 16> mem = {BranchonoVerflowClear, 0x02, LoaDY_I, 0x01, LoaDAcc_I, 0x01, 0x00};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.setOverflowFlag(false);
    cpu.run();
    EXPECT_EQ(0x00, cpu.getYRegister());
    EXPECT_EQ(0x01, cpu.getARegister());
}

TEST(CPUBranch, BVC_if_true) {
    std::array<uint8_t, 16> mem = {BranchonoVerflowClear, 0x02, LoaDY_I, 0x01, LoaDAcc_I, 0x01, 0x00};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.setOverflowFlag(true);
    cpu.run();
    EXPECT_EQ(0x01, cpu.getYRegister());
    EXPECT_EQ(0x01, cpu.getARegister());
}

TEST(CPUBranch, BVS_if_false) {
    std::array<uint8_t, 16> mem = {BranchonoVerflowSet, 0x02, LoaDY_I, 0x01, LoaDAcc_I, 0x01, 0x00};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.setOverflowFlag(false);
    cpu.run();
    EXPECT_EQ(0x01, cpu.getYRegister());
    EXPECT_EQ(0x01, cpu.getARegister());
}

TEST(CPUBranch, BVS_if_true) {
    std::array<uint8_t, 16> mem = {BranchonoVerflowSet, 0x02, LoaDY_I, 0x01, LoaDAcc_I, 0x01, 0x00};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.setOverflowFlag(true);
    cpu.run();
    EXPECT_EQ(0x00, cpu.getYRegister());
    EXPECT_EQ(0x01, cpu.getARegister());
}