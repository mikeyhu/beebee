#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../m6502_lib/CPU.cpp"
#include <cstdint>
#include <array>
#include "Helpers.cpp"

class CPUCompare : public ::testing::Test {

};

// CPX : ComPare Xregister
TEST(CPUCompare, CPX_I_false) {
    std::array<uint8_t, 16> mem = {LoaDX_I, 0x08, ComPareX_I, 0x07, 0x00};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.run();
    EXPECT_FALSE(cpu.isZeroFlag());
}

TEST(CPUCompare, CPX_I_true) {
    std::array<uint8_t, 16> mem = {LoaDX_I, 0x08, ComPareX_I, 0x08, 0x00};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.run();
    EXPECT_TRUE(cpu.isZeroFlag());
}

TEST(CPUCompare, CPX_Ab_true) {
    std::array<uint8_t, 16> mem = {LoaDX_I, 0x08, ComPareX_Ab, 0x06, 0x00, 0x00, 0x08};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.run();
    EXPECT_TRUE(cpu.isZeroFlag());
}

TEST(CPUCompare, CPX_Z_true) {
    std::array<uint8_t, 16> mem = {LoaDX_I, 0x08, ComPareX_Z, 0x05, 0x00, 0x08};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.run();
    EXPECT_TRUE(cpu.isZeroFlag());
}

// CPY : ComPare Yregister
TEST(CPUCompare, CPY_I_false) {
    std::array<uint8_t, 16> mem = {LoaDY_I, 0x08, ComPareY_I, 0x07, 0x00};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.run();
    EXPECT_FALSE(cpu.isZeroFlag());
}

TEST(CPUCompare, CPY_I_true) {
    std::array<uint8_t, 16> mem = {LoaDY_I, 0x08, ComPareY_I, 0x08, 0x00};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.run();
    EXPECT_TRUE(cpu.isZeroFlag());
}

TEST(CPUCompare, CPY_Ab_true) {
    std::array<uint8_t, 16> mem = {LoaDY_I, 0x08, ComPareY_Ab, 0x06, 0x00, 0x00, 0x08};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.run();
    EXPECT_TRUE(cpu.isZeroFlag());
}

TEST(CPUCompare, CPY_Z_true) {
    std::array<uint8_t, 16> mem = {LoaDY_I, 0x08, ComPareY_Z, 0x05, 0x00, 0x08};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.run();
    EXPECT_TRUE(cpu.isZeroFlag());
}

// CMP : CoMPare Accumulator
TEST(CPUCompare, CMP_I_CarryOnly) {
    std::array<uint8_t, 16> mem = {LoaDAcc_I, 0x08, CoMPareacc_I, 0x07, 0x00};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.run();
    EXPECT_FALSE(cpu.isZeroFlag());
    EXPECT_TRUE(cpu.isCarryFlag());
}

TEST(CPUCompare, CMP_I_CarryAndZero) {
    std::array<uint8_t, 16> mem = {LoaDAcc_I, 0x07, CoMPareacc_I, 0x07, 0x00};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.run();
    EXPECT_TRUE(cpu.isZeroFlag());
    EXPECT_TRUE(cpu.isCarryFlag());
}

TEST(CPUCompare, CMP_I_None) {
    std::array<uint8_t, 16> mem = {LoaDAcc_I, 0x07, CoMPareacc_I, 0x08, 0x00};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.run();
    EXPECT_FALSE(cpu.isZeroFlag());
    EXPECT_FALSE(cpu.isCarryFlag());
}

TEST(CPUCompare, CMP_Z_CarryAndZero) {
    std::array<uint8_t, 16> mem = {LoaDAcc_I, 0xff, CoMPareacc_Z, 0x05, 0x00, 0xff};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.run();
    EXPECT_TRUE(cpu.isZeroFlag());
    EXPECT_TRUE(cpu.isCarryFlag());
}

TEST(CPUCompare, CMP_ZX_CarryAndZero) {
    std::array<uint8_t, 16> mem = {LoaDAcc_I, 0xff, LoaDX_I, 0x02, CoMPareacc_ZX, 0x05, 0x00, 0xff};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.run();
    EXPECT_TRUE(cpu.isZeroFlag());
    EXPECT_TRUE(cpu.isCarryFlag());
}

TEST(CPUCompare, CMP_Ab_CarryAndZero) {
    std::array<uint8_t, 16> mem = {LoaDAcc_I, 0xff, CoMPareacc_Ab, 0x06, 0x00, 0x00, 0xff};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.run();
    EXPECT_TRUE(cpu.isZeroFlag());
    EXPECT_TRUE(cpu.isCarryFlag());
}

TEST(CPUCompare, CMP_AbX_CarryAndZero) {
    std::array<uint8_t, 16> mem = {LoaDAcc_I, 0xff, LoaDX_I, 0x02, CoMPareacc_AbX, 0x06, 0x00, 0x00, 0xff};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.run();
    EXPECT_TRUE(cpu.isZeroFlag());
    EXPECT_TRUE(cpu.isCarryFlag());
}

TEST(CPUCompare, CMP_AbY_CarryAndZero) {
    std::array<uint8_t, 16> mem = {LoaDAcc_I, 0xff, LoaDY_I, 0x02, CoMPareacc_AbY, 0x06, 0x00, 0x00, 0xff};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.run();
    EXPECT_TRUE(cpu.isZeroFlag());
    EXPECT_TRUE(cpu.isCarryFlag());
}

TEST(CPUCompare, CoMPareacc_IndirIndex) {
    std::array<uint8_t, 16> mem = {LoaDAcc_I, 0xff, LoaDY_I, 0x03, CoMPareacc_IndirIndex, 0x07, BReaK, 0x06, 0x00, 0xff};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.run();
    EXPECT_TRUE(cpu.isZeroFlag());
    EXPECT_TRUE(cpu.isCarryFlag());
}

TEST(CPUCompare, CoMPareacc_IndexIndir) {
    std::array<uint8_t, 16> mem = {LoaDAcc_I, 0xff, LoaDX_I, 0x03, CoMPareacc_IndexIndir, 0x04, BReaK, 0x09, 0x00, 0xff};
    auto cpu = CPU(0, mem, cycleCallback);
    cpu.run();
    EXPECT_TRUE(cpu.isZeroFlag());
    EXPECT_TRUE(cpu.isCarryFlag());
}