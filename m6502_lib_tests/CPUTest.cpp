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
    EXPECT_EQ(1, cpu.getProgramCounter());
}

// AND : bitwise AND with accumulator

TEST(CPUTest, AND_I) {
    std::array<uint8_t, 5> mem = {LDA_I, 0xF0, AND_I, 0x8F, BRK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
}

TEST(CPUTest, AND_Ab) {
    std::array<uint8_t, 7> mem = {LDA_I, 0xF0, AND_Ab, 0x00, 0x06, BRK, 0x8F};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
}

TEST(CPUTest, AND_AbX) {
    std::array<uint8_t, 9> mem = {LDX_I, 0x02, LDA_I, 0xF0, AND_AbX, 0x00, 0x06, BRK, 0x8F};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
}

TEST(CPUTest, AND_AbY) {
    std::array<uint8_t, 9> mem = {LDY_I, 0x02, LDA_I, 0xF0, AND_AbY, 0x00, 0x06, BRK, 0x8F};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
}

TEST(CPUTest, AND_Z) {
    std::array<uint8_t, 6> mem = {LDA_I, 0xF0, AND_Z, 0x05, BRK, 0x8F};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
}

TEST(CPUTest, AND_ZX) {
    std::array<uint8_t, 9> mem = {LDX_I, 0x02, LDA_I, 0xF0, AND_ZX, 0x05, BRK, 0x8F};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
}

// LDA : LoaD Accumulator

TEST(CPUTest, LDA_I) {
    std::array<uint8_t, 3> mem = {LDA_I, 0x80, BRK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
}

TEST(CPUTest, LDA_Ab) {
    std::array<uint8_t, 5> mem = {LDA_Ab, 0x00, 0x04, BRK, 0x80};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
    EXPECT_EQ(0x04, cpu.getProgramCounter());
}

TEST(CPUTest, LDA_AbX) {
    std::array<uint8_t, 7> mem = {LDX_I, 0x01, LDA_AbX, 0x0, 0x5, BRK, 0x80};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
    EXPECT_EQ(0x06, cpu.getProgramCounter());
}

TEST(CPUTest, LDA_AbY) {
    std::array<uint8_t, 7> mem = {LDY_I, 0x01, LDA_AbY, 0x0, 0x5, BRK, 0x80};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
    EXPECT_EQ(0x06, cpu.getProgramCounter());
}

TEST(CPUTest, LDA_Z) {
    std::array<uint8_t, 4> mem = {LDA_Z, 0x03, BRK, 0x80};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
    EXPECT_EQ(0x03, cpu.getProgramCounter());
}

TEST(CPUTest, LDA_ZX) {
    std::array<uint8_t, 6> mem = {LDX_I, 0x02, LDA_ZX, 0x3, BRK, 0x80};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
    EXPECT_EQ(0x05, cpu.getProgramCounter());
}


// LDX : LoaD Xregister

TEST(CPUTest, LDX_I) {
    std::array<uint8_t, 3> mem = {LDX_I, 0x80, BRK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getXRegister());
}

TEST(CPUTest, LDX_Ab) {
    std::array<uint8_t, 5> mem = {LDX_Ab, 0x00, 0x04, BRK, 0x80};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getXRegister());
    EXPECT_EQ(0x04, cpu.getProgramCounter());
}

TEST(CPUTest, LDX_AbY) {
    std::array<uint8_t, 7> mem = {LDY_I, 0x01, LDX_AbY, 0x0, 0x5, BRK, 0x80};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getXRegister());
    EXPECT_EQ(0x06, cpu.getProgramCounter());
}

TEST(CPUTest, LDX_Z) {
    std::array<uint8_t, 4> mem = {LDX_Z, 0x03, BRK, 0x80};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getXRegister());
    EXPECT_EQ(0x03, cpu.getProgramCounter());
}

TEST(CPUTest, LDX_ZX) {
    std::array<uint8_t, 6> mem = {LDX_I, 0x02, LDX_ZX, 0x3, BRK, 0x80};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getXRegister());
    EXPECT_EQ(0x05, cpu.getProgramCounter());
}

// LDY : LoaD Yregister

TEST(CPUTest, LDY_I) {
    std::array<uint8_t, 3> mem = {LDY_I, 0x80, BRK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getYRegister());
}

TEST(CPUTest, LDY_Ab) {
    std::array<uint8_t, 5> mem = {LDY_Ab, 0x00, 0x04, BRK, 0x80};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getYRegister());
    EXPECT_EQ(0x04, cpu.getProgramCounter());
}

TEST(CPUTest, LDY_AbX) {
    std::array<uint8_t, 7> mem = {LDX_I, 0x01, LDY_AbX, 0x0, 0x5, BRK, 0x80};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getYRegister());
    EXPECT_EQ(0x06, cpu.getProgramCounter());
}

TEST(CPUTest, LDY_Z) {
    std::array<uint8_t, 4> mem = {LDY_Z, 0x03, BRK, 0x80};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getYRegister());
    EXPECT_EQ(0x03, cpu.getProgramCounter());
}

TEST(CPUTest, LDY_ZX) {
    std::array<uint8_t, 6> mem = {LDX_I, 0x02, LDY_ZX, 0x3, BRK, 0x80};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getYRegister());
    EXPECT_EQ(0x05, cpu.getProgramCounter());
}

// STA : STore Accumulator

TEST(CPUTest, STA_Ab) {
    std::array<uint8_t, 7> mem = {LDA_I, 0x80, STA_Ab, 0x00, 0x06, BRK, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
    EXPECT_EQ(0x80, cpu.getMemory()[6]);
}

TEST(CPUTest, STA_AbX) {
    std::array<uint8_t, 9> mem = {LDA_I, 0x80, LDX_I, 0x01, STA_AbX, 0x00, 0x07, BRK, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
    EXPECT_EQ(0x80, cpu.getMemory()[8]);
}

TEST(CPUTest, STA_AbY) {
    std::array<uint8_t, 9> mem = {LDA_I, 0x80, LDY_I, 0x01, STA_AbY, 0x00, 0x07, BRK, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
    EXPECT_EQ(0x80, cpu.getMemory()[8]);
}

TEST(CPUTest, STA_Z) {
    std::array<uint8_t, 6> mem = {LDA_I, 0x80, STA_Z, 0x05, BRK, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
    EXPECT_EQ(0x80, cpu.getMemory()[5]);
}

TEST(CPUTest, STA_ZX) {
    std::array<uint8_t, 8> mem = {LDA_I, 0x80, LDX_I, 0x02, STA_ZX, 0x05, BRK, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
    EXPECT_EQ(0x80, cpu.getMemory()[7]);
}

TEST(CPUTest, CLD) {
    std::array<uint8_t, 2> mem = {CLD, BRK};
    auto cpu = CPU(0, mem);
    cpu.setDecimalFlag(true);
    cpu.run();
    EXPECT_FALSE(cpu.isDecimalFlag());
}

TEST(CPUTest, TXS) {
    std::array<uint8_t, 4> mem = {LDX_I, 0xff, TXS, BRK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0xff, cpu.getStackPointer());
}

TEST(CPUTest, JMP_Ab) {
    std::array<uint8_t, 6> mem = {JMP_Ab, 0x00, 0x05, LDX_I, 0xff, BRK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x00, cpu.getXRegister());
    EXPECT_EQ(0x06, cpu.getProgramCounter());
}