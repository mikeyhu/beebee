#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../m6502_lib/CPU.cpp"
#include <cstdint>
#include <array>

class CPUGeneral : public ::testing::Test {

};

TEST(CPUGeneral, FoundBRK) {
    std::array<uint8_t, 1> mem = {BRK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(1, cpu.getProgramCounter());
}

// ADC : ADd with Carry
TEST(CPUGeneral, ADC_I_nocarry) {
    std::array<uint8_t, 5> mem = {LDA_I, 0x10, ADC_I, 0x0f, BRK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x1f, cpu.getARegister());
    EXPECT_FALSE(cpu.isCarryFlag());
}

// ADC : ADd with Carry
TEST(CPUGeneral, ADC_I_carry) {
    std::array<uint8_t, 5> mem = {LDA_I, 0xc0, ADC_I, 0xc4, BRK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x84, cpu.getARegister());
    EXPECT_TRUE(cpu.isCarryFlag());
}

TEST(CPUGeneral, ADC_Z) {
    std::array<uint8_t, 6> mem = {LDA_I, 0x10, ADC_Z, 0x05, BRK, 0x0f};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x1f, cpu.getARegister());
    EXPECT_FALSE(cpu.isCarryFlag());
}

TEST(CPUGeneral, ADC_ZX) {
    std::array<uint8_t, 8> mem = {LDX_I, 0x02, LDA_I, 0x10, ADC_ZX, 0x05, BRK, 0x0f};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x1f, cpu.getARegister());
    EXPECT_FALSE(cpu.isCarryFlag());
}

TEST(CPUGeneral, ADC_Ab) {
    std::array<uint8_t, 7> mem = {LDA_I, 0x10, ADC_Ab, 0x06, 0x00, BRK, 0x0f};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x1f, cpu.getARegister());
    EXPECT_FALSE(cpu.isCarryFlag());
}

TEST(CPUGeneral, ADC_AbX) {
    std::array<uint8_t, 9> mem = {LDX_I, 0x02, LDA_I, 0x10, ADC_AbX, 0x06, 0x00, BRK, 0x0f};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x1f, cpu.getARegister());
    EXPECT_FALSE(cpu.isCarryFlag());
}

TEST(CPUGeneral, ADC_AbY) {
    std::array<uint8_t, 9> mem = {LDY_I, 0x02, LDA_I, 0x10, ADC_AbY, 0x06, 0x00, BRK, 0x0f};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x1f, cpu.getARegister());
    EXPECT_FALSE(cpu.isCarryFlag());
}

// LDA : LoaD Accumulator

TEST(CPUGeneral, LDA_I) {
    std::array<uint8_t, 3> mem = {LDA_I, 0x08, BRK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x08, cpu.getARegister());
    EXPECT_FALSE(cpu.isNegativeFlag());
}

TEST(CPUGeneral, LDA_I_Negative) {
    std::array<uint8_t, 3> mem = {LDA_I, 0x80, BRK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
    EXPECT_TRUE(cpu.isNegativeFlag());
}

TEST(CPUGeneral, LDA_Ab) {
    std::array<uint8_t, 5> mem = {LDA_Ab, 0x04, 0x00, BRK, 0x80};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
    EXPECT_EQ(0x04, cpu.getProgramCounter());
}

TEST(CPUGeneral, LDA_AbX) {
    std::array<uint8_t, 7> mem = {LDX_I, 0x01, LDA_AbX, 0x5, 0x0, BRK, 0x80};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
    EXPECT_EQ(0x06, cpu.getProgramCounter());
}

TEST(CPUGeneral, LDA_AbY) {
    std::array<uint8_t, 7> mem = {LDY_I, 0x01, LDA_AbY, 0x5, 0x0, BRK, 0x80};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
    EXPECT_EQ(0x06, cpu.getProgramCounter());
}

TEST(CPUGeneral, LDA_Z) {
    std::array<uint8_t, 4> mem = {LDA_Z, 0x03, BRK, 0x80};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
    EXPECT_EQ(0x03, cpu.getProgramCounter());
}

TEST(CPUGeneral, LDA_ZX) {
    std::array<uint8_t, 6> mem = {LDX_I, 0x02, LDA_ZX, 0x3, BRK, 0x80};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
    EXPECT_EQ(0x05, cpu.getProgramCounter());
}

// LDX : LoaD Xregister

TEST(CPUGeneral, LDX_I) {
    std::array<uint8_t, 3> mem = {LDX_I, 0x80, BRK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getXRegister());
}

TEST(CPUGeneral, LDX_Ab) {
    std::array<uint8_t, 5> mem = {LDX_Ab, 0x04, 0x00, BRK, 0x80};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getXRegister());
    EXPECT_EQ(0x04, cpu.getProgramCounter());
}

TEST(CPUGeneral, LDX_AbY) {
    std::array<uint8_t, 7> mem = {LDY_I, 0x01, LDX_AbY, 0x5, 0x0, BRK, 0x80};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getXRegister());
    EXPECT_EQ(0x06, cpu.getProgramCounter());
}

TEST(CPUGeneral, LDX_Z) {
    std::array<uint8_t, 4> mem = {LDX_Z, 0x03, BRK, 0x80};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getXRegister());
    EXPECT_EQ(0x03, cpu.getProgramCounter());
}

TEST(CPUGeneral, LDX_ZX) {
    std::array<uint8_t, 6> mem = {LDX_I, 0x02, LDX_ZX, 0x3, BRK, 0x80};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getXRegister());
    EXPECT_EQ(0x05, cpu.getProgramCounter());
}

// LDY : LoaD Yregister

TEST(CPUGeneral, LDY_I) {
    std::array<uint8_t, 3> mem = {LDY_I, 0x80, BRK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getYRegister());
}

TEST(CPUGeneral, LDY_Ab) {
    std::array<uint8_t, 5> mem = {LDY_Ab, 0x04, 0x00, BRK, 0x80};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getYRegister());
    EXPECT_EQ(0x04, cpu.getProgramCounter());
}

TEST(CPUGeneral, LDY_AbX) {
    std::array<uint8_t, 7> mem = {LDX_I, 0x01, LDY_AbX, 0x5, 0x0, BRK, 0x80};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getYRegister());
    EXPECT_EQ(0x06, cpu.getProgramCounter());
}

TEST(CPUGeneral, LDY_Z) {
    std::array<uint8_t, 4> mem = {LDY_Z, 0x03, BRK, 0x80};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getYRegister());
    EXPECT_EQ(0x03, cpu.getProgramCounter());
}

TEST(CPUGeneral, LDY_ZX) {
    std::array<uint8_t, 6> mem = {LDX_I, 0x02, LDY_ZX, 0x3, BRK, 0x80};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getYRegister());
    EXPECT_EQ(0x05, cpu.getProgramCounter());
}

// STA : STore Accumulator

TEST(CPUGeneral, STA_Ab) {
    std::array<uint8_t, 7> mem = {LDA_I, 0x80, STA_Ab, 0x06, 0x00, BRK, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
    EXPECT_EQ(0x80, cpu.getMemory()[6]);
}

TEST(CPUGeneral, STA_AbX) {
    std::array<uint8_t, 9> mem = {LDA_I, 0x80, LDX_I, 0x01, STA_AbX, 0x07, 0x00, BRK, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
    EXPECT_EQ(0x80, cpu.getMemory()[8]);
}

TEST(CPUGeneral, STA_AbY) {
    std::array<uint8_t, 9> mem = {LDA_I, 0x80, LDY_I, 0x01, STA_AbY, 0x07, 0x00, BRK, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
    EXPECT_EQ(0x80, cpu.getMemory()[8]);
}

TEST(CPUGeneral, STA_Z) {
    std::array<uint8_t, 6> mem = {LDA_I, 0x80, STA_Z, 0x05, BRK, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
    EXPECT_EQ(0x80, cpu.getMemory()[5]);
}

TEST(CPUGeneral, STA_ZX) {
    std::array<uint8_t, 8> mem = {LDA_I, 0x80, LDX_I, 0x02, STA_ZX, 0x05, BRK, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
    EXPECT_EQ(0x80, cpu.getMemory()[7]);
}

// STX : STore Xregister

TEST(CPUGeneral, STX_Ab) {
    std::array<uint8_t, 7> mem = {LDX_I, 0x80, STX_Ab, 0x06, 0x00, BRK, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getMemory()[6]);
}

TEST(CPUGeneral, STX_Z) {
    std::array<uint8_t, 6> mem = {LDX_I, 0x80, STX_Z, 0x05, BRK, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getMemory()[5]);
}

TEST(CPUGeneral, STX_ZY) {
    std::array<uint8_t, 8> mem = {LDX_I, 0x80, LDY_I, 0x02, STX_ZY, 0x05, BRK, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getMemory()[7]);
}

TEST(CPUGeneral, CLC) {
    std::array<uint8_t, 2> mem = {CLC, BRK};
    auto cpu = CPU(0, mem);
    cpu.setCarryFlag(true);
    cpu.run();
    EXPECT_FALSE(cpu.isCarryFlag());
}

TEST(CPUGeneral, CLD) {
    std::array<uint8_t, 2> mem = {CLD, BRK};
    auto cpu = CPU(0, mem);
    cpu.setDecimalFlag(true);
    cpu.run();
    EXPECT_FALSE(cpu.isDecimalFlag());
}

TEST(CPUGeneral, JMP_Ab) {
    std::array<uint8_t, 6> mem = {JMP_Ab, 0x05, 0x00, LDX_I, 0xff, BRK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x00, cpu.getXRegister());
    EXPECT_EQ(0x06, cpu.getProgramCounter());
}

// INcrement

TEST(CPUGeneral, INX) {
    std::array<uint8_t, 4> mem = {LDX_I, 0x01, INX, BRK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x02, cpu.getXRegister());
}

TEST(CPUGeneral, INY) {
    std::array<uint8_t, 4> mem = {LDY_I, 0x01, INY, BRK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x02, cpu.getYRegister());
}

// DEcrement

TEST(CPUGeneral, DEX) {
    std::array<uint8_t, 4> mem = {LDX_I, 0x02, DEX, BRK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x01, cpu.getXRegister());
    EXPECT_FALSE(cpu.isZeroFlag());
}

TEST(CPUGeneral, DEX_zeroflag) {
    std::array<uint8_t, 4> mem = {LDX_I, 0x01, DEX, BRK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x00, cpu.getXRegister());
    EXPECT_TRUE(cpu.isZeroFlag());
}

TEST(CPUGeneral, DEY) {
    std::array<uint8_t, 4> mem = {LDY_I, 0x02, DEY, BRK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x01, cpu.getYRegister());
}

TEST(CPUGeneral, DEY_zeroflag) {
    std::array<uint8_t, 4> mem = {LDY_I, 0x01, DEY, BRK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x00, cpu.getYRegister());
    EXPECT_TRUE(cpu.isZeroFlag());
}

// T Transfer

TEST(CPUGeneral, TAX) {
    std::array<uint8_t, 4> mem = {LDA_I, 0x02, TAX, BRK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x02, cpu.getXRegister());
}

TEST(CPUGeneral, TAY) {
    std::array<uint8_t, 4> mem = {LDA_I, 0x02, TAY, BRK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x02, cpu.getYRegister());
}

TEST(CPUGeneral, TXA) {
    std::array<uint8_t, 4> mem = {LDX_I, 0x02, TXA, BRK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x02, cpu.getARegister());
}

TEST(CPUGeneral, TYA) {
    std::array<uint8_t, 4> mem = {LDY_I, 0x02, TYA, BRK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x02, cpu.getARegister());
}

TEST(CPUGeneral, TXS) {
    std::array<uint8_t, 4> mem = {LDX_I, 0xff, TXS, BRK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0xff, cpu.getStackPointer());
}

class CPUBitwise : public ::testing::Test {

};

// AND : bitwise AND with accumulator
TEST(CPUBitwise, AND_I) {
    std::array<uint8_t, 5> mem = {LDA_I, 0xF0, AND_I, 0x8F, BRK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
}

TEST(CPUBitwise, AND_Ab) {
    std::array<uint8_t, 7> mem = {LDA_I, 0xF0, AND_Ab, 0x06, 0x00, BRK, 0x8F};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
}

TEST(CPUBitwise, AND_AbX) {
    std::array<uint8_t, 9> mem = {LDX_I, 0x02, LDA_I, 0xF0, AND_AbX, 0x06, 0x00, BRK, 0x8F};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
}

TEST(CPUBitwise, AND_AbY) {
    std::array<uint8_t, 9> mem = {LDY_I, 0x02, LDA_I, 0xF0, AND_AbY, 0x06, 0x00, BRK, 0x8F};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
}

TEST(CPUBitwise, AND_Z) {
    std::array<uint8_t, 6> mem = {LDA_I, 0xF0, AND_Z, 0x05, BRK, 0x8F};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
}

TEST(CPUBitwise, AND_ZX) {
    std::array<uint8_t, 9> mem = {LDX_I, 0x02, LDA_I, 0xF0, AND_ZX, 0x05, BRK, 0x8F};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
}

// EOR : bitwise EOR with accumulator
TEST(CPUBitwise, EOR_I) {
    std::array<uint8_t, 5> mem = {LDA_I, 0xF0, EOR_I, 0x8F, BRK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x7F, cpu.getARegister());
}

TEST(CPUBitwise, EOR_Ab) {
    std::array<uint8_t, 7> mem = {LDA_I, 0xF0, EOR_Ab, 0x06, 0x00, BRK, 0x8F};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x7F, cpu.getARegister());
}

TEST(CPUBitwise, EOR_AbX) {
    std::array<uint8_t, 9> mem = {LDX_I, 0x02, LDA_I, 0xF0, EOR_AbX, 0x06, 0x00, BRK, 0x8F};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x7F, cpu.getARegister());
}

TEST(CPUBitwise, EOR_AbY) {
    std::array<uint8_t, 9> mem = {LDY_I, 0x02, LDA_I, 0xF0, EOR_AbY, 0x06, 0x00, BRK, 0x8F};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x7F, cpu.getARegister());
}

TEST(CPUBitwise, EOR_Z) {
    std::array<uint8_t, 6> mem = {LDA_I, 0xF0, EOR_Z, 0x05, BRK, 0x8F};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x7F, cpu.getARegister());
}

TEST(CPUBitwise, EOR_ZX) {
    std::array<uint8_t, 9> mem = {LDX_I, 0x02, LDA_I, 0xF0, EOR_ZX, 0x05, BRK, 0x8F};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x7F, cpu.getARegister());
}

class CPUCompare : public ::testing::Test {

};

// CPX : ComPare Xregister
TEST(CPUCompare, CPX_I_false) {
    std::array<uint8_t, 16> mem = {LDX_I, 0x08, CPX_I, 0x07, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_FALSE(cpu.isZeroFlag());
}

TEST(CPUCompare, CPX_I_true) {
    std::array<uint8_t, 16> mem = {LDX_I, 0x08, CPX_I, 0x08, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_TRUE(cpu.isZeroFlag());
}

TEST(CPUCompare, CPX_Ab_true) {
    std::array<uint8_t, 16> mem = {LDX_I, 0x08, CPX_Ab, 0x06, 0x00, 0x00, 0x08};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_TRUE(cpu.isZeroFlag());
}

TEST(CPUCompare, CPX_Z_true) {
    std::array<uint8_t, 16> mem = {LDX_I, 0x08, CPX_Z, 0x05, 0x00, 0x08};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_TRUE(cpu.isZeroFlag());
}

// CPY : ComPare Yregister
TEST(CPUCompare, CPY_I_false) {
    std::array<uint8_t, 16> mem = {LDY_I, 0x08, CPY_I, 0x07, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_FALSE(cpu.isZeroFlag());
}

TEST(CPUCompare, CPY_I_true) {
    std::array<uint8_t, 16> mem = {LDY_I, 0x08, CPY_I, 0x08, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_TRUE(cpu.isZeroFlag());
}

TEST(CPUCompare, CPY_Ab_true) {
    std::array<uint8_t, 16> mem = {LDY_I, 0x08, CPY_Ab, 0x06, 0x00, 0x00, 0x08};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_TRUE(cpu.isZeroFlag());
}

TEST(CPUCompare, CPY_Z_true) {
    std::array<uint8_t, 16> mem = {LDY_I, 0x08, CPY_Z, 0x05, 0x00, 0x08};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_TRUE(cpu.isZeroFlag());
}

// CMP : CoMPare Accumulator
TEST(CPUCompare, CMP_I_CarryOnly) {
    std::array<uint8_t, 16> mem = {LDA_I, 0x08, CMP_I, 0x07, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_FALSE(cpu.isZeroFlag());
    EXPECT_TRUE(cpu.isCarryFlag());
}

TEST(CPUCompare, CMP_I_CarryAndZero) {
    std::array<uint8_t, 16> mem = {LDA_I, 0x07, CMP_I, 0x07, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_TRUE(cpu.isZeroFlag());
    EXPECT_TRUE(cpu.isCarryFlag());
}

TEST(CPUCompare, CMP_I_None) {
    std::array<uint8_t, 16> mem = {LDA_I, 0x07, CMP_I, 0x08, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_FALSE(cpu.isZeroFlag());
    EXPECT_FALSE(cpu.isCarryFlag());
}

TEST(CPUCompare, CMP_Z_CarryAndZero) {
    std::array<uint8_t, 16> mem = {LDA_I, 0xff, CMP_Z, 0x05, 0x00, 0xff};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_TRUE(cpu.isZeroFlag());
    EXPECT_TRUE(cpu.isCarryFlag());
}

TEST(CPUCompare, CMP_ZX_CarryAndZero) {
    std::array<uint8_t, 16> mem = {LDA_I, 0xff, LDX_I, 0x02, CMP_ZX, 0x05, 0x00, 0xff};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_TRUE(cpu.isZeroFlag());
    EXPECT_TRUE(cpu.isCarryFlag());
}

TEST(CPUCompare, CMP_Ab_CarryAndZero) {
    std::array<uint8_t, 16> mem = {LDA_I, 0xff, CMP_Ab, 0x06, 0x00, 0x00, 0xff};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_TRUE(cpu.isZeroFlag());
    EXPECT_TRUE(cpu.isCarryFlag());
}

TEST(CPUCompare, CMP_AbX_CarryAndZero) {
    std::array<uint8_t, 16> mem = {LDA_I, 0xff, LDX_I, 0x02, CMP_AbX, 0x06, 0x00, 0x00, 0xff};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_TRUE(cpu.isZeroFlag());
    EXPECT_TRUE(cpu.isCarryFlag());
}

TEST(CPUCompare, CMP_AbY_CarryAndZero) {
    std::array<uint8_t, 16> mem = {LDA_I, 0xff, LDY_I, 0x02, CMP_AbY, 0x06, 0x00, 0x00, 0xff};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_TRUE(cpu.isZeroFlag());
    EXPECT_TRUE(cpu.isCarryFlag());
}

class CPUBranch : public ::testing::Test {

};

// BNE : Branch on Not Equal (backwards is relative is > 0x80, otherwise forwards)
TEST(CPUBranch, BNE_backwards) {
    std::array<uint8_t, 16> mem = {LDX_I, 0x08, DEX, STX_Ab, 0x0e, 0x00, CPX_I, 0x03, BNE_Re, 0xf8, STX_Ab, 0x0f, 0x00,
                                   0x00, 0x00, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x03, cpu.getMemory()[14]);
    EXPECT_EQ(0x03, cpu.getMemory()[15]);
}

TEST(CPUBranch, BNE_forwards) {
    std::array<uint8_t, 16> mem = {LDX_I, 0x08, CPX_I, 0x07, BNE_Re, 0x02, LDY_I, 0x01, LDA_I, 0x01, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x00, cpu.getYRegister());
    EXPECT_EQ(0x01, cpu.getARegister());
}

TEST(CPUBranch, BEQ_forwards) {
    std::array<uint8_t, 16> mem = {LDX_I, 0x08, CPX_I, 0x08, BEQ_Re, 0x02, LDY_I, 0x01, LDA_I, 0x01, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x00, cpu.getYRegister());
    EXPECT_EQ(0x01, cpu.getARegister());
}

TEST(CPUBranch, BPL_if_positive) {
    std::array<uint8_t, 16> mem = {LDX_I, 0x08, BPL_Re, 0x02, LDY_I, 0x01, LDA_I, 0x01, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x00, cpu.getYRegister());
    EXPECT_EQ(0x01, cpu.getARegister());
}

TEST(CPUBranch, BPL_if_negative) {
    std::array<uint8_t, 16> mem = {LDX_I, 0x88, BPL_Re, 0x02, LDY_I, 0x01, LDA_I, 0x01, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x01, cpu.getYRegister());
    EXPECT_EQ(0x01, cpu.getARegister());
}

TEST(CPUBranch, BCC_if_positive) {
    std::array<uint8_t, 16> mem = {BCC_Re, 0x02, LDY_I, 0x01, LDA_I, 0x01, 0x00};
    auto cpu = CPU(0, mem);
    cpu.setCarryFlag(true);
    cpu.run();
    EXPECT_EQ(0x01, cpu.getYRegister());
    EXPECT_EQ(0x01, cpu.getARegister());
}

TEST(CPUBranch, BCC_if_negative) {
    std::array<uint8_t, 16> mem = {BCC_Re, 0x02, LDY_I, 0x01, LDA_I, 0x01, 0x00};
    auto cpu = CPU(0, mem);
    cpu.setCarryFlag(false);
    cpu.run();
    EXPECT_EQ(0x00, cpu.getYRegister());
    EXPECT_EQ(0x01, cpu.getARegister());
}

TEST(CPUBranch, BCS_if_positive) {
    std::array<uint8_t, 16> mem = {BCS_Re, 0x02, LDY_I, 0x01, LDA_I, 0x01, 0x00};
    auto cpu = CPU(0, mem);
    cpu.setCarryFlag(true);
    cpu.run();
    EXPECT_EQ(0x00, cpu.getYRegister());
    EXPECT_EQ(0x01, cpu.getARegister());
}

TEST(CPUBranch, BCS_if_negative) {
    std::array<uint8_t, 16> mem = {BCS_Re, 0x02, LDY_I, 0x01, LDA_I, 0x01, 0x00};
    auto cpu = CPU(0, mem);
    cpu.setCarryFlag(false);
    cpu.run();
    EXPECT_EQ(0x01, cpu.getYRegister());
    EXPECT_EQ(0x01, cpu.getARegister());
}
