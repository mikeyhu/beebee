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

// ADC : ADd with Carry
TEST(CPUTest, ADC_I_nocarry) {
    std::array<uint8_t, 5> mem = {LDA_I, 0x10, ADC_I, 0x0f, BRK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x1f, cpu.getARegister());
    EXPECT_FALSE(cpu.isCarryFlag());
}

// ADC : ADd with Carry
TEST(CPUTest, ADC_I_carry) {
    std::array<uint8_t, 5> mem = {LDA_I, 0xc0, ADC_I, 0xc4, BRK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x84, cpu.getARegister());
    EXPECT_TRUE(cpu.isCarryFlag());
}

TEST(CPUTest, ADC_Z) {
    std::array<uint8_t, 6> mem = {LDA_I, 0x10, ADC_Z, 0x05, BRK, 0x0f};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x1f, cpu.getARegister());
    EXPECT_FALSE(cpu.isCarryFlag());
}

TEST(CPUTest, ADC_ZX) {
    std::array<uint8_t, 8> mem = {LDX_I, 0x02, LDA_I, 0x10, ADC_ZX, 0x05, BRK, 0x0f};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x1f, cpu.getARegister());
    EXPECT_FALSE(cpu.isCarryFlag());
}

TEST(CPUTest, ADC_Ab) {
    std::array<uint8_t, 7> mem = {LDA_I, 0x10, ADC_Ab, 0x06, 0x00, BRK, 0x0f};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x1f, cpu.getARegister());
    EXPECT_FALSE(cpu.isCarryFlag());
}

TEST(CPUTest, ADC_AbX) {
    std::array<uint8_t, 9> mem = {LDX_I, 0x02, LDA_I, 0x10, ADC_AbX, 0x06, 0x00, BRK, 0x0f};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x1f, cpu.getARegister());
    EXPECT_FALSE(cpu.isCarryFlag());
}

TEST(CPUTest, ADC_AbY) {
    std::array<uint8_t, 9> mem = {LDY_I, 0x02, LDA_I, 0x10, ADC_AbY, 0x06, 0x00, BRK, 0x0f};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x1f, cpu.getARegister());
    EXPECT_FALSE(cpu.isCarryFlag());
}

// AND : bitwise AND with accumulator
TEST(CPUTest, AND_I) {
    std::array<uint8_t, 5> mem = {LDA_I, 0xF0, AND_I, 0x8F, BRK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
}

TEST(CPUTest, AND_Ab) {
    std::array<uint8_t, 7> mem = {LDA_I, 0xF0, AND_Ab, 0x06, 0x00, BRK, 0x8F};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
}

TEST(CPUTest, AND_AbX) {
    std::array<uint8_t, 9> mem = {LDX_I, 0x02, LDA_I, 0xF0, AND_AbX, 0x06, 0x00, BRK, 0x8F};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
}

TEST(CPUTest, AND_AbY) {
    std::array<uint8_t, 9> mem = {LDY_I, 0x02, LDA_I, 0xF0, AND_AbY, 0x06, 0x00, BRK, 0x8F};
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

// EOR : bitwise EOR with accumulator
TEST(CPUTest, EOR_I) {
    std::array<uint8_t, 5> mem = {LDA_I, 0xF0, EOR_I, 0x8F, BRK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x7F, cpu.getARegister());
}

TEST(CPUTest, EOR_Ab) {
    std::array<uint8_t, 7> mem = {LDA_I, 0xF0, EOR_Ab, 0x06, 0x00, BRK, 0x8F};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x7F, cpu.getARegister());
}

TEST(CPUTest, EOR_AbX) {
    std::array<uint8_t, 9> mem = {LDX_I, 0x02, LDA_I, 0xF0, EOR_AbX, 0x06, 0x00, BRK, 0x8F};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x7F, cpu.getARegister());
}

TEST(CPUTest, EOR_AbY) {
    std::array<uint8_t, 9> mem = {LDY_I, 0x02, LDA_I, 0xF0, EOR_AbY, 0x06, 0x00, BRK, 0x8F};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x7F, cpu.getARegister());
}

TEST(CPUTest, EOR_Z) {
    std::array<uint8_t, 6> mem = {LDA_I, 0xF0, EOR_Z, 0x05, BRK, 0x8F};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x7F, cpu.getARegister());
}

TEST(CPUTest, EOR_ZX) {
    std::array<uint8_t, 9> mem = {LDX_I, 0x02, LDA_I, 0xF0, EOR_ZX, 0x05, BRK, 0x8F};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x7F, cpu.getARegister());
}

// LDA : LoaD Accumulator

TEST(CPUTest, LDA_I) {
    std::array<uint8_t, 3> mem = {LDA_I, 0x08, BRK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x08, cpu.getARegister());
    EXPECT_FALSE(cpu.isNegativeFlag());
}

TEST(CPUTest, LDA_I_Negative) {
    std::array<uint8_t, 3> mem = {LDA_I, 0x80, BRK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
    EXPECT_TRUE(cpu.isNegativeFlag());
}

TEST(CPUTest, LDA_Ab) {
    std::array<uint8_t, 5> mem = {LDA_Ab, 0x04, 0x00, BRK, 0x80};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
    EXPECT_EQ(0x04, cpu.getProgramCounter());
}

TEST(CPUTest, LDA_AbX) {
    std::array<uint8_t, 7> mem = {LDX_I, 0x01, LDA_AbX, 0x5, 0x0, BRK, 0x80};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
    EXPECT_EQ(0x06, cpu.getProgramCounter());
}

TEST(CPUTest, LDA_AbY) {
    std::array<uint8_t, 7> mem = {LDY_I, 0x01, LDA_AbY, 0x5, 0x0, BRK, 0x80};
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
    std::array<uint8_t, 5> mem = {LDX_Ab, 0x04, 0x00, BRK, 0x80};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getXRegister());
    EXPECT_EQ(0x04, cpu.getProgramCounter());
}

TEST(CPUTest, LDX_AbY) {
    std::array<uint8_t, 7> mem = {LDY_I, 0x01, LDX_AbY, 0x5, 0x0, BRK, 0x80};
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
    std::array<uint8_t, 5> mem = {LDY_Ab, 0x04, 0x00, BRK, 0x80};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getYRegister());
    EXPECT_EQ(0x04, cpu.getProgramCounter());
}

TEST(CPUTest, LDY_AbX) {
    std::array<uint8_t, 7> mem = {LDX_I, 0x01, LDY_AbX, 0x5, 0x0, BRK, 0x80};
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
    std::array<uint8_t, 7> mem = {LDA_I, 0x80, STA_Ab, 0x06, 0x00, BRK, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
    EXPECT_EQ(0x80, cpu.getMemory()[6]);
}

TEST(CPUTest, STA_AbX) {
    std::array<uint8_t, 9> mem = {LDA_I, 0x80, LDX_I, 0x01, STA_AbX, 0x07, 0x00, BRK, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
    EXPECT_EQ(0x80, cpu.getMemory()[8]);
}

TEST(CPUTest, STA_AbY) {
    std::array<uint8_t, 9> mem = {LDA_I, 0x80, LDY_I, 0x01, STA_AbY, 0x07, 0x00, BRK, 0x00};
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

// STX : STore Xregister

TEST(CPUTest, STX_Ab) {
    std::array<uint8_t, 7> mem = {LDX_I, 0x80, STX_Ab, 0x06, 0x00, BRK, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getMemory()[6]);
}

TEST(CPUTest, STX_Z) {
    std::array<uint8_t, 6> mem = {LDX_I, 0x80, STX_Z, 0x05, BRK, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getMemory()[5]);
}

TEST(CPUTest, STX_ZY) {
    std::array<uint8_t, 8> mem = {LDX_I, 0x80, LDY_I, 0x02, STX_ZY, 0x05, BRK, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getMemory()[7]);
}

TEST(CPUTest, CLC) {
    std::array<uint8_t, 2> mem = {CLC, BRK};
    auto cpu = CPU(0, mem);
    cpu.setCarryFlag(true);
    cpu.run();
    EXPECT_FALSE(cpu.isCarryFlag());
}

TEST(CPUTest, CLD) {
    std::array<uint8_t, 2> mem = {CLD, BRK};
    auto cpu = CPU(0, mem);
    cpu.setDecimalFlag(true);
    cpu.run();
    EXPECT_FALSE(cpu.isDecimalFlag());
}

TEST(CPUTest, JMP_Ab) {
    std::array<uint8_t, 6> mem = {JMP_Ab, 0x05, 0x00, LDX_I, 0xff, BRK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x00, cpu.getXRegister());
    EXPECT_EQ(0x06, cpu.getProgramCounter());
}

// INcrement

TEST(CPUTest, INX) {
    std::array<uint8_t, 4> mem = {LDX_I, 0x01, INX, BRK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x02, cpu.getXRegister());
}

TEST(CPUTest, INY) {
    std::array<uint8_t, 4> mem = {LDY_I, 0x01, INY, BRK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x02, cpu.getYRegister());
}

// DEcrement

TEST(CPUTest, DEX) {
    std::array<uint8_t, 4> mem = {LDX_I, 0x02, DEX, BRK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x01, cpu.getXRegister());
    EXPECT_FALSE(cpu.isZeroFlag());
}

TEST(CPUTest, DEX_zeroflag) {
    std::array<uint8_t, 4> mem = {LDX_I, 0x01, DEX, BRK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x00, cpu.getXRegister());
    EXPECT_TRUE(cpu.isZeroFlag());
}

TEST(CPUTest, DEY) {
    std::array<uint8_t, 4> mem = {LDY_I, 0x02, DEY, BRK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x01, cpu.getYRegister());
}

TEST(CPUTest, DEY_zeroflag) {
    std::array<uint8_t, 4> mem = {LDY_I, 0x01, DEY, BRK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x00, cpu.getYRegister());
    EXPECT_TRUE(cpu.isZeroFlag());
}

// T Transfer

TEST(CPUTest, TAX) {
    std::array<uint8_t, 4> mem = {LDA_I, 0x02, TAX, BRK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x02, cpu.getXRegister());
}

TEST(CPUTest, TAY) {
    std::array<uint8_t, 4> mem = {LDA_I, 0x02, TAY, BRK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x02, cpu.getYRegister());
}

TEST(CPUTest, TXA) {
    std::array<uint8_t, 4> mem = {LDX_I, 0x02, TXA, BRK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x02, cpu.getARegister());
}

TEST(CPUTest, TYA) {
    std::array<uint8_t, 4> mem = {LDY_I, 0x02, TYA, BRK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x02, cpu.getARegister());
}

TEST(CPUTest, TXS) {
    std::array<uint8_t, 4> mem = {LDX_I, 0xff, TXS, BRK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0xff, cpu.getStackPointer());
}

// CPX : ComPare Xregister
TEST(CPUTest, CPX_I_false) {
    std::array<uint8_t, 16> mem = {LDX_I, 0x08, CPX_I, 0x07, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_FALSE(cpu.isZeroFlag());
}

TEST(CPUTest, CPX_I_true) {
    std::array<uint8_t, 16> mem = {LDX_I, 0x08, CPX_I, 0x08, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_TRUE(cpu.isZeroFlag());
}

TEST(CPUTest, CPX_Ab_true) {
    std::array<uint8_t, 16> mem = {LDX_I, 0x08, CPX_Ab, 0x06, 0x00, 0x00, 0x08};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_TRUE(cpu.isZeroFlag());
}

TEST(CPUTest, CPX_Z_true) {
    std::array<uint8_t, 16> mem = {LDX_I, 0x08, CPX_Z, 0x05, 0x00, 0x08};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_TRUE(cpu.isZeroFlag());
}

// CPY : ComPare Yregister
TEST(CPUTest, CPY_I_false) {
    std::array<uint8_t, 16> mem = {LDY_I, 0x08, CPY_I, 0x07, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_FALSE(cpu.isZeroFlag());
}

TEST(CPUTest, CPY_I_true) {
    std::array<uint8_t, 16> mem = {LDY_I, 0x08, CPY_I, 0x08, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_TRUE(cpu.isZeroFlag());
}

TEST(CPUTest, CPY_Ab_true) {
    std::array<uint8_t, 16> mem = {LDY_I, 0x08, CPY_Ab, 0x06, 0x00, 0x00, 0x08};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_TRUE(cpu.isZeroFlag());
}

TEST(CPUTest, CPY_Z_true) {
    std::array<uint8_t, 16> mem = {LDY_I, 0x08, CPY_Z, 0x05, 0x00, 0x08};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_TRUE(cpu.isZeroFlag());
}

// CMP : CoMPare Accumulator
TEST(CPUTest, CMP_I_CarryOnly) {
    std::array<uint8_t, 16> mem = {LDA_I, 0x08, CMP_I, 0x07, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_FALSE(cpu.isZeroFlag());
    EXPECT_TRUE(cpu.isCarryFlag());
}

TEST(CPUTest, CMP_I_CarryAndZero) {
    std::array<uint8_t, 16> mem = {LDA_I, 0x07, CMP_I, 0x07, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_TRUE(cpu.isZeroFlag());
    EXPECT_TRUE(cpu.isCarryFlag());
}

TEST(CPUTest, CMP_I_None) {
    std::array<uint8_t, 16> mem = {LDA_I, 0x07, CMP_I, 0x08, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_FALSE(cpu.isZeroFlag());
    EXPECT_FALSE(cpu.isCarryFlag());
}

TEST(CPUTest, CMP_Z_CarryAndZero) {
    std::array<uint8_t, 16> mem = {LDA_I, 0xff, CMP_Z, 0x05, 0x00, 0xff};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_TRUE(cpu.isZeroFlag());
    EXPECT_TRUE(cpu.isCarryFlag());
}

TEST(CPUTest, CMP_ZX_CarryAndZero) {
    std::array<uint8_t, 16> mem = {LDA_I, 0xff, LDX_I, 0x02, CMP_ZX, 0x05, 0x00, 0xff};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_TRUE(cpu.isZeroFlag());
    EXPECT_TRUE(cpu.isCarryFlag());
}

TEST(CPUTest, CMP_Ab_CarryAndZero) {
    std::array<uint8_t, 16> mem = {LDA_I, 0xff, CMP_Ab, 0x06, 0x00, 0x00, 0xff};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_TRUE(cpu.isZeroFlag());
    EXPECT_TRUE(cpu.isCarryFlag());
}

TEST(CPUTest, CMP_AbX_CarryAndZero) {
    std::array<uint8_t, 16> mem = {LDA_I, 0xff, LDX_I, 0x02, CMP_AbX, 0x06, 0x00, 0x00, 0xff};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_TRUE(cpu.isZeroFlag());
    EXPECT_TRUE(cpu.isCarryFlag());
}

TEST(CPUTest, CMP_AbY_CarryAndZero) {
    std::array<uint8_t, 16> mem = {LDA_I, 0xff, LDY_I, 0x02, CMP_AbY, 0x06, 0x00, 0x00, 0xff};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_TRUE(cpu.isZeroFlag());
    EXPECT_TRUE(cpu.isCarryFlag());
}

// BNE : Branch on Not Equal (backwards is relative is > 0x80, otherwise forwards)
TEST(CPUTest, BNE_backwards) {
    std::array<uint8_t, 16> mem = {LDX_I, 0x08, DEX, STX_Ab, 0x0e, 0x00, CPX_I, 0x03, BNE_Re, 0xf8, STX_Ab, 0x0f, 0x00,
                                   0x00, 0x00, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x03, cpu.getMemory()[14]);
    EXPECT_EQ(0x03, cpu.getMemory()[15]);
}

TEST(CPUTest, BNE_forwards) {
    std::array<uint8_t, 16> mem = {LDX_I, 0x08, CPX_I, 0x07, BNE_Re, 0x02, LDY_I, 0x01, LDA_I, 0x01, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x00, cpu.getYRegister());
    EXPECT_EQ(0x01, cpu.getARegister());
}

TEST(CPUTest, BEQ_forwards) {
    std::array<uint8_t, 16> mem = {LDX_I, 0x08, CPX_I, 0x08, BEQ_Re, 0x02, LDY_I, 0x01, LDA_I, 0x01, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x00, cpu.getYRegister());
    EXPECT_EQ(0x01, cpu.getARegister());
}

TEST(CPUTest, BPL_if_positive) {
    std::array<uint8_t, 16> mem = {LDX_I, 0x08, BPL_Re, 0x02, LDY_I, 0x01, LDA_I, 0x01, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x00, cpu.getYRegister());
    EXPECT_EQ(0x01, cpu.getARegister());
}

TEST(CPUTest, BPL_if_negative) {
    std::array<uint8_t, 16> mem = {LDX_I, 0x88, BPL_Re, 0x02, LDY_I, 0x01, LDA_I, 0x01, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x01, cpu.getYRegister());
    EXPECT_EQ(0x01, cpu.getARegister());
}


