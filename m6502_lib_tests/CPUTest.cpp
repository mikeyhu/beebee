#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../m6502_lib/CPU.cpp"
#include <cstdint>
#include <array>

class CPUGeneral : public ::testing::Test {

};

TEST(CPUGeneral, FoundBRK) {
    std::array<uint8_t, 0xffff> mem = {LoaDAcc_I, 0x0, SToreAcc_Z, 0x09, LoaDAcc_I, 0x01, SToreAcc_Z, 0x0a, BReaK, 0x00, 0x00};
    auto cpu = CPU(0, mem);
    cpu.setBreakLocation(0x09);
    cpu.run();
    EXPECT_TRUE(cpu.isBreakCommandFlag());
    EXPECT_EQ(0x100, cpu.getProgramCounter());
}

// ADC : ADd with Carry
TEST(CPUGeneral, ADC_I_nocarry) {
    std::array<uint8_t, 5> mem = {LoaDAcc_I, 0x10, ADdwithCarry_I, 0x0f, BReaK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x1f, cpu.getARegister());
    EXPECT_FALSE(cpu.isCarryFlag());
}

// ADC : ADd with Carry
TEST(CPUGeneral, ADC_I_carry) {
    std::array<uint8_t, 5> mem = {LoaDAcc_I, 0xc0, ADdwithCarry_I, 0xc4, BReaK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x84, cpu.getARegister());
    EXPECT_TRUE(cpu.isCarryFlag());
}

TEST(CPUGeneral, ADdwithCarry_Z) {
    std::array<uint8_t, 6> mem = {LoaDAcc_I, 0x10, ADdwithCarry_Z, 0x05, BReaK, 0x0f};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x1f, cpu.getARegister());
    EXPECT_FALSE(cpu.isCarryFlag());
}

TEST(CPUGeneral, ADdwithCarry_ZX) {
    std::array<uint8_t, 8> mem = {LoaDX_I, 0x02, LoaDAcc_I, 0x10, ADdwithCarry_ZX, 0x05, BReaK, 0x0f};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x1f, cpu.getARegister());
    EXPECT_FALSE(cpu.isCarryFlag());
}

TEST(CPUGeneral, ADdwithCarry_Ab) {
    std::array<uint8_t, 7> mem = {LoaDAcc_I, 0x10, ADdwithCarry_Ab, 0x06, 0x00, BReaK, 0x0f};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x1f, cpu.getARegister());
    EXPECT_FALSE(cpu.isCarryFlag());
}

TEST(CPUGeneral, ADdwithCarry_AbX) {
    std::array<uint8_t, 9> mem = {LoaDX_I, 0x02, LoaDAcc_I, 0x10, ADdwithCarry_AbX, 0x06, 0x00, BReaK, 0x0f};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x1f, cpu.getARegister());
    EXPECT_FALSE(cpu.isCarryFlag());
}

TEST(CPUGeneral, ADdwithCarry_AbY) {
    std::array<uint8_t, 9> mem = {LoaDY_I, 0x02, LoaDAcc_I, 0x10, ADdwithCarry_AbY, 0x06, 0x00, BReaK, 0x0f};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x1f, cpu.getARegister());
    EXPECT_FALSE(cpu.isCarryFlag());
}

// LDA : LoaD Accumulator

TEST(CPUGeneral, LoaDAcc_I) {
    std::array<uint8_t, 3> mem = {LoaDAcc_I, 0x08, BReaK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x08, cpu.getARegister());
    EXPECT_FALSE(cpu.isNegativeFlag());
}

TEST(CPUGeneral, LDA_I_Negative) {
    std::array<uint8_t, 3> mem = {LoaDAcc_I, 0x80, BReaK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
    EXPECT_TRUE(cpu.isNegativeFlag());
}

TEST(CPUGeneral, LoaDAcc_Ab) {
    std::array<uint8_t, 5> mem = {LoaDAcc_Ab, 0x04, 0x00, BReaK, 0x80};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
    EXPECT_EQ(0x04, cpu.getProgramCounter());
}

TEST(CPUGeneral, LoaDAcc_AbX) {
    std::array<uint8_t, 7> mem = {LoaDX_I, 0x01, LoaDAcc_AbX, 0x5, 0x0, BReaK, 0x80};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
    EXPECT_EQ(0x06, cpu.getProgramCounter());
}

TEST(CPUGeneral, LoaDAcc_AbY) {
    std::array<uint8_t, 7> mem = {LoaDY_I, 0x01, LoaDAcc_AbY, 0x5, 0x0, BReaK, 0x80};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
    EXPECT_EQ(0x06, cpu.getProgramCounter());
}

TEST(CPUGeneral, LoaDAcc_Z) {
    std::array<uint8_t, 4> mem = {LoaDAcc_Z, 0x03, BReaK, 0x80};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
    EXPECT_EQ(0x03, cpu.getProgramCounter());
}

TEST(CPUGeneral, LoaDAcc_ZX) {
    std::array<uint8_t, 6> mem = {LoaDX_I, 0x02, LoaDAcc_ZX, 0x3, BReaK, 0x80};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
    EXPECT_EQ(0x05, cpu.getProgramCounter());
}

// LDX : LoaD Xregister

TEST(CPUGeneral, LoaDX_I) {
    std::array<uint8_t, 3> mem = {LoaDX_I, 0x80, BReaK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getXRegister());
}

TEST(CPUGeneral, LoaDX_Ab) {
    std::array<uint8_t, 5> mem = {LoaDX_Ab, 0x04, 0x00, BReaK, 0x80};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getXRegister());
    EXPECT_EQ(0x04, cpu.getProgramCounter());
}

TEST(CPUGeneral, LoaDX_AbY) {
    std::array<uint8_t, 7> mem = {LoaDY_I, 0x01, LoaDX_AbY, 0x5, 0x0, BReaK, 0x80};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getXRegister());
    EXPECT_EQ(0x06, cpu.getProgramCounter());
}

TEST(CPUGeneral, LoaDX_Z) {
    std::array<uint8_t, 4> mem = {LoaDX_Z, 0x03, BReaK, 0x80};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getXRegister());
    EXPECT_EQ(0x03, cpu.getProgramCounter());
}

TEST(CPUGeneral, LoaDX_ZX) {
    std::array<uint8_t, 6> mem = {LoaDX_I, 0x02, LoaDX_ZX, 0x3, BReaK, 0x80};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getXRegister());
    EXPECT_EQ(0x05, cpu.getProgramCounter());
}

// LDY : LoaD Yregister

TEST(CPUGeneral, LoaDY_I) {
    std::array<uint8_t, 3> mem = {LoaDY_I, 0x80, BReaK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getYRegister());
}

TEST(CPUGeneral, LoaDY_Ab) {
    std::array<uint8_t, 5> mem = {LoaDY_Ab, 0x04, 0x00, BReaK, 0x80};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getYRegister());
    EXPECT_EQ(0x04, cpu.getProgramCounter());
}

TEST(CPUGeneral, LoaDY_AbX) {
    std::array<uint8_t, 7> mem = {LoaDX_I, 0x01, LoaDY_AbX, 0x5, 0x0, BReaK, 0x80};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getYRegister());
    EXPECT_EQ(0x06, cpu.getProgramCounter());
}

TEST(CPUGeneral, LoaDY_Z) {
    std::array<uint8_t, 4> mem = {LoaDY_Z, 0x03, BReaK, 0x80};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getYRegister());
    EXPECT_EQ(0x03, cpu.getProgramCounter());
}

TEST(CPUGeneral, LoaDY_ZX) {
    std::array<uint8_t, 6> mem = {LoaDX_I, 0x02, LoaDY_ZX, 0x3, BReaK, 0x80};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getYRegister());
    EXPECT_EQ(0x05, cpu.getProgramCounter());
}

// STA : STore Accumulator

TEST(CPUGeneral, SToreAcc_Ab) {
    std::array<uint8_t, 7> mem = {LoaDAcc_I, 0x80, SToreAcc_Ab, 0x06, 0x00, BReaK, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
    EXPECT_EQ(0x80, cpu.getMemory()[6]);
}

TEST(CPUGeneral, SToreAcc_AbX) {
    std::array<uint8_t, 9> mem = {LoaDAcc_I, 0x80, LoaDX_I, 0x01, SToreAcc_AbX, 0x07, 0x00, BReaK, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
    EXPECT_EQ(0x80, cpu.getMemory()[8]);
}

TEST(CPUGeneral, SToreAcc_AbY) {
    std::array<uint8_t, 9> mem = {LoaDAcc_I, 0x80, LoaDY_I, 0x01, SToreAcc_AbY, 0x07, 0x00, BReaK, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
    EXPECT_EQ(0x80, cpu.getMemory()[8]);
}

TEST(CPUGeneral, SToreAcc_Z) {
    std::array<uint8_t, 6> mem = {LoaDAcc_I, 0x80, SToreAcc_Z, 0x05, BReaK, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
    EXPECT_EQ(0x80, cpu.getMemory()[5]);
}

TEST(CPUGeneral, SToreAcc_ZX) {
    std::array<uint8_t, 8> mem = {LoaDAcc_I, 0x80, LoaDX_I, 0x02, SToreAcc_ZX, 0x05, BReaK, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
    EXPECT_EQ(0x80, cpu.getMemory()[7]);
}

// STX : STore Xregister

TEST(CPUGeneral, SToreX_Ab) {
    std::array<uint8_t, 7> mem = {LoaDX_I, 0x80, SToreX_Ab, 0x06, 0x00, BReaK, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getMemory()[6]);
}

TEST(CPUGeneral, SToreX_Z) {
    std::array<uint8_t, 6> mem = {LoaDX_I, 0x80, SToreX_Z, 0x05, BReaK, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getMemory()[5]);
}

TEST(CPUGeneral, SToreX_ZY) {
    std::array<uint8_t, 8> mem = {LoaDX_I, 0x80, LoaDY_I, 0x02, SToreX_ZY, 0x05, BReaK, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getMemory()[7]);
}

TEST(CPUGeneral, CLearCarry) {
    std::array<uint8_t, 2> mem = {CLearCarry, BReaK};
    auto cpu = CPU(0, mem);
    cpu.setCarryFlag(true);
    cpu.run();
    EXPECT_FALSE(cpu.isCarryFlag());
}

TEST(CPUGeneral, CLearDecimal) {
    std::array<uint8_t, 2> mem = {CLearDecimal, BReaK};
    auto cpu = CPU(0, mem);
    cpu.setDecimalFlag(true);
    cpu.run();
    EXPECT_FALSE(cpu.isDecimalFlag());
}

TEST(CPUGeneral, JuMP_Ab) {
    std::array<uint8_t, 6> mem = {JuMP_Ab, 0x05, 0x00, LoaDX_I, 0xff, BReaK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x00, cpu.getXRegister());
    EXPECT_EQ(0x06, cpu.getProgramCounter());
}

TEST(CPUGeneral, JuMP_Indir) {
    std::array<uint8_t, 8> mem = {JuMP_Indir, 0x06, 0x00, LoaDX_I, 0xff, BReaK, 0x03, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0xff, cpu.getXRegister());
    EXPECT_EQ(0x06, cpu.getProgramCounter());
}

// INcrement

TEST(CPUGeneral, INcrementX) {
    std::array<uint8_t, 4> mem = {LoaDX_I, 0x01, INcrementX, BReaK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x02, cpu.getXRegister());
}

TEST(CPUGeneral, INcrementY) {
    std::array<uint8_t, 4> mem = {LoaDY_I, 0x01, INcrementY, BReaK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x02, cpu.getYRegister());
}

// DEcrement

TEST(CPUGeneral, DEcrementX) {
    std::array<uint8_t, 4> mem = {LoaDX_I, 0x02, DEcrementX, BReaK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x01, cpu.getXRegister());
    EXPECT_FALSE(cpu.isZeroFlag());
}

TEST(CPUGeneral, DEX_zeroflag) {
    std::array<uint8_t, 4> mem = {LoaDX_I, 0x01, DEcrementX, BReaK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x00, cpu.getXRegister());
    EXPECT_TRUE(cpu.isZeroFlag());
}

TEST(CPUGeneral, DEcrementY) {
    std::array<uint8_t, 4> mem = {LoaDY_I, 0x02, DEcrementY, BReaK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x01, cpu.getYRegister());
}

TEST(CPUGeneral, DEY_zeroflag) {
    std::array<uint8_t, 4> mem = {LoaDY_I, 0x01, DEcrementY, BReaK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x00, cpu.getYRegister());
    EXPECT_TRUE(cpu.isZeroFlag());
}

// T Transfer

TEST(CPUGeneral, TransferAtoX) {
    std::array<uint8_t, 4> mem = {LoaDAcc_I, 0x02, TransferAtoX, BReaK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x02, cpu.getXRegister());
}

TEST(CPUGeneral, TransferAtoY) {
    std::array<uint8_t, 4> mem = {LoaDAcc_I, 0x02, TransferAtoY, BReaK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x02, cpu.getYRegister());
}

TEST(CPUGeneral, TransferXtoA) {
    std::array<uint8_t, 4> mem = {LoaDX_I, 0x02, TransferXtoA, BReaK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x02, cpu.getARegister());
}

TEST(CPUGeneral, TransferYtoA) {
    std::array<uint8_t, 4> mem = {LoaDY_I, 0x02, TransferYtoA, BReaK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x02, cpu.getARegister());
}

class CPUBitwise : public ::testing::Test {

};

// AND : bitwise AND with accumulator
TEST(CPUBitwise, AND_I) {
    std::array<uint8_t, 5> mem = {LoaDAcc_I, 0xF0, AND_I, 0x8F, BReaK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
}

TEST(CPUBitwise, AND_Ab) {
    std::array<uint8_t, 7> mem = {LoaDAcc_I, 0xF0, AND_Ab, 0x06, 0x00, BReaK, 0x8F};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
}

TEST(CPUBitwise, AND_AbX) {
    std::array<uint8_t, 9> mem = {LoaDX_I, 0x02, LoaDAcc_I, 0xF0, AND_AbX, 0x06, 0x00, BReaK, 0x8F};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
}

TEST(CPUBitwise, AND_AbY) {
    std::array<uint8_t, 9> mem = {LoaDY_I, 0x02, LoaDAcc_I, 0xF0, AND_AbY, 0x06, 0x00, BReaK, 0x8F};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
}

TEST(CPUBitwise, AND_Z) {
    std::array<uint8_t, 6> mem = {LoaDAcc_I, 0xF0, AND_Z, 0x05, BReaK, 0x8F};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
}

TEST(CPUBitwise, AND_ZX) {
    std::array<uint8_t, 9> mem = {LoaDX_I, 0x02, LoaDAcc_I, 0xF0, AND_ZX, 0x05, BReaK, 0x8F};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getARegister());
}

// EOR : bitwise EOR with accumulator
TEST(CPUBitwise, ExclusiveOR_I) {
    std::array<uint8_t, 5> mem = {LoaDAcc_I, 0xF0, ExclusiveOR_I, 0x8F, BReaK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x7F, cpu.getARegister());
}

TEST(CPUBitwise, ExclusiveOR_Ab) {
    std::array<uint8_t, 7> mem = {LoaDAcc_I, 0xF0, ExclusiveOR_Ab, 0x06, 0x00, BReaK, 0x8F};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x7F, cpu.getARegister());
}

TEST(CPUBitwise, ExclusiveOR_AbX) {
    std::array<uint8_t, 9> mem = {LoaDX_I, 0x02, LoaDAcc_I, 0xF0, ExclusiveOR_AbX, 0x06, 0x00, BReaK, 0x8F};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x7F, cpu.getARegister());
}

TEST(CPUBitwise, ExclusiveOR_AbY) {
    std::array<uint8_t, 9> mem = {LoaDY_I, 0x02, LoaDAcc_I, 0xF0, ExclusiveOR_AbY, 0x06, 0x00, BReaK, 0x8F};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x7F, cpu.getARegister());
}

TEST(CPUBitwise, ExclusiveOR_Z) {
    std::array<uint8_t, 6> mem = {LoaDAcc_I, 0xF0, ExclusiveOR_Z, 0x05, BReaK, 0x8F};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x7F, cpu.getARegister());
}

TEST(CPUBitwise, ExclusiveOR_ZX) {
    std::array<uint8_t, 9> mem = {LoaDX_I, 0x02, LoaDAcc_I, 0xF0, ExclusiveOR_ZX, 0x05, BReaK, 0x8F};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x7F, cpu.getARegister());
}

class CPUCompare : public ::testing::Test {

};

// CPX : ComPare Xregister
TEST(CPUCompare, CPX_I_false) {
    std::array<uint8_t, 16> mem = {LoaDX_I, 0x08, ComPareX_I, 0x07, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_FALSE(cpu.isZeroFlag());
}

TEST(CPUCompare, CPX_I_true) {
    std::array<uint8_t, 16> mem = {LoaDX_I, 0x08, ComPareX_I, 0x08, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_TRUE(cpu.isZeroFlag());
}

TEST(CPUCompare, CPX_Ab_true) {
    std::array<uint8_t, 16> mem = {LoaDX_I, 0x08, ComPareX_Ab, 0x06, 0x00, 0x00, 0x08};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_TRUE(cpu.isZeroFlag());
}

TEST(CPUCompare, CPX_Z_true) {
    std::array<uint8_t, 16> mem = {LoaDX_I, 0x08, ComPareX_Z, 0x05, 0x00, 0x08};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_TRUE(cpu.isZeroFlag());
}

// CPY : ComPare Yregister
TEST(CPUCompare, CPY_I_false) {
    std::array<uint8_t, 16> mem = {LoaDY_I, 0x08, ComPareY_I, 0x07, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_FALSE(cpu.isZeroFlag());
}

TEST(CPUCompare, CPY_I_true) {
    std::array<uint8_t, 16> mem = {LoaDY_I, 0x08, ComPareY_I, 0x08, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_TRUE(cpu.isZeroFlag());
}

TEST(CPUCompare, CPY_Ab_true) {
    std::array<uint8_t, 16> mem = {LoaDY_I, 0x08, ComPareY_Ab, 0x06, 0x00, 0x00, 0x08};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_TRUE(cpu.isZeroFlag());
}

TEST(CPUCompare, CPY_Z_true) {
    std::array<uint8_t, 16> mem = {LoaDY_I, 0x08, ComPareY_Z, 0x05, 0x00, 0x08};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_TRUE(cpu.isZeroFlag());
}

// CMP : CoMPare Accumulator
TEST(CPUCompare, CMP_I_CarryOnly) {
    std::array<uint8_t, 16> mem = {LoaDAcc_I, 0x08, CoMPareacc_I, 0x07, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_FALSE(cpu.isZeroFlag());
    EXPECT_TRUE(cpu.isCarryFlag());
}

TEST(CPUCompare, CMP_I_CarryAndZero) {
    std::array<uint8_t, 16> mem = {LoaDAcc_I, 0x07, CoMPareacc_I, 0x07, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_TRUE(cpu.isZeroFlag());
    EXPECT_TRUE(cpu.isCarryFlag());
}

TEST(CPUCompare, CMP_I_None) {
    std::array<uint8_t, 16> mem = {LoaDAcc_I, 0x07, CoMPareacc_I, 0x08, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_FALSE(cpu.isZeroFlag());
    EXPECT_FALSE(cpu.isCarryFlag());
}

TEST(CPUCompare, CMP_Z_CarryAndZero) {
    std::array<uint8_t, 16> mem = {LoaDAcc_I, 0xff, CoMPareacc_Z, 0x05, 0x00, 0xff};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_TRUE(cpu.isZeroFlag());
    EXPECT_TRUE(cpu.isCarryFlag());
}

TEST(CPUCompare, CMP_ZX_CarryAndZero) {
    std::array<uint8_t, 16> mem = {LoaDAcc_I, 0xff, LoaDX_I, 0x02, CoMPareacc_ZX, 0x05, 0x00, 0xff};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_TRUE(cpu.isZeroFlag());
    EXPECT_TRUE(cpu.isCarryFlag());
}

TEST(CPUCompare, CMP_Ab_CarryAndZero) {
    std::array<uint8_t, 16> mem = {LoaDAcc_I, 0xff, CoMPareacc_Ab, 0x06, 0x00, 0x00, 0xff};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_TRUE(cpu.isZeroFlag());
    EXPECT_TRUE(cpu.isCarryFlag());
}

TEST(CPUCompare, CMP_AbX_CarryAndZero) {
    std::array<uint8_t, 16> mem = {LoaDAcc_I, 0xff, LoaDX_I, 0x02, CoMPareacc_AbX, 0x06, 0x00, 0x00, 0xff};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_TRUE(cpu.isZeroFlag());
    EXPECT_TRUE(cpu.isCarryFlag());
}

TEST(CPUCompare, CMP_AbY_CarryAndZero) {
    std::array<uint8_t, 16> mem = {LoaDAcc_I, 0xff, LoaDY_I, 0x02, CoMPareacc_AbY, 0x06, 0x00, 0x00, 0xff};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_TRUE(cpu.isZeroFlag());
    EXPECT_TRUE(cpu.isCarryFlag());
}

class CPUBranch : public ::testing::Test {

};

// BNE : Branch on Not Equal (backwards is relative is > 0x80, otherwise forwards)
TEST(CPUBranch, BNE_backwards) {
    std::array<uint8_t, 16> mem = {LoaDX_I, 0x08, DEcrementX, SToreX_Ab, 0x0e, 0x00, ComPareX_I, 0x03, BranchonNotEqual, 0xf8, SToreX_Ab, 0x0f, 0x00,
                                   0x00, 0x00, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x03, cpu.getMemory()[14]);
    EXPECT_EQ(0x03, cpu.getMemory()[15]);
}

TEST(CPUBranch, BNE_forwards) {
    std::array<uint8_t, 16> mem = {LoaDX_I, 0x08, ComPareX_I, 0x07, BranchonNotEqual, 0x02, LoaDY_I, 0x01, LoaDAcc_I, 0x01, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x00, cpu.getYRegister());
    EXPECT_EQ(0x01, cpu.getARegister());
}

TEST(CPUBranch, BEQ_forwards) {
    std::array<uint8_t, 16> mem = {LoaDX_I, 0x08, ComPareX_I, 0x08, BranchonEQual, 0x02, LoaDY_I, 0x01, LoaDAcc_I, 0x01, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x00, cpu.getYRegister());
    EXPECT_EQ(0x01, cpu.getARegister());
}

TEST(CPUBranch, BPL_if_positive) {
    std::array<uint8_t, 16> mem = {LoaDX_I, 0x08, BranchonPLus, 0x02, LoaDY_I, 0x01, LoaDAcc_I, 0x01, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x00, cpu.getYRegister());
    EXPECT_EQ(0x01, cpu.getARegister());
}

TEST(CPUBranch, BPL_if_negative) {
    std::array<uint8_t, 16> mem = {LoaDX_I, 0x88, BranchonPLus, 0x02, LoaDY_I, 0x01, LoaDAcc_I, 0x01, 0x00};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x01, cpu.getYRegister());
    EXPECT_EQ(0x01, cpu.getARegister());
}

TEST(CPUBranch, BCC_if_true) {
    std::array<uint8_t, 16> mem = {BranchonCarryClear, 0x02, LoaDY_I, 0x01, LoaDAcc_I, 0x01, 0x00};
    auto cpu = CPU(0, mem);
    cpu.setCarryFlag(true);
    cpu.run();
    EXPECT_EQ(0x01, cpu.getYRegister());
    EXPECT_EQ(0x01, cpu.getARegister());
}

TEST(CPUBranch, BCC_if_false) {
    std::array<uint8_t, 16> mem = {BranchonCarryClear, 0x02, LoaDY_I, 0x01, LoaDAcc_I, 0x01, 0x00};
    auto cpu = CPU(0, mem);
    cpu.setCarryFlag(false);
    cpu.run();
    EXPECT_EQ(0x00, cpu.getYRegister());
    EXPECT_EQ(0x01, cpu.getARegister());
}

TEST(CPUBranch, BCS_if_true) {
    std::array<uint8_t, 16> mem = {BranchonCarrySet, 0x02, LoaDY_I, 0x01, LoaDAcc_I, 0x01, 0x00};
    auto cpu = CPU(0, mem);
    cpu.setCarryFlag(true);
    cpu.run();
    EXPECT_EQ(0x00, cpu.getYRegister());
    EXPECT_EQ(0x01, cpu.getARegister());
}

TEST(CPUBranch, BCS_if_false) {
    std::array<uint8_t, 16> mem = {BranchonCarrySet, 0x02, LoaDY_I, 0x01, LoaDAcc_I, 0x01, 0x00};
    auto cpu = CPU(0, mem);
    cpu.setCarryFlag(false);
    cpu.run();
    EXPECT_EQ(0x01, cpu.getYRegister());
    EXPECT_EQ(0x01, cpu.getARegister());
}

TEST(CPUBranch, BMI_if_true) {
    std::array<uint8_t, 16> mem = {BranchonMInus, 0x02, LoaDY_I, 0x01, LoaDAcc_I, 0x01, 0x00};
    auto cpu = CPU(0, mem);
    cpu.setNegativeFlag(true);
    cpu.run();
    EXPECT_EQ(0x00, cpu.getYRegister());
    EXPECT_EQ(0x01, cpu.getARegister());
}

TEST(CPUBranch, BMI_if_false) {
    std::array<uint8_t, 16> mem = {BranchonMInus, 0x02, LoaDY_I, 0x01, LoaDAcc_I, 0x01, 0x00};
    auto cpu = CPU(0, mem);
    cpu.setNegativeFlag(false);
    cpu.run();
    EXPECT_EQ(0x01, cpu.getYRegister());
    EXPECT_EQ(0x01, cpu.getARegister());
}

TEST(CPUBranch, BVC_if_false) {
    std::array<uint8_t, 16> mem = {BranchonoVerflowClear, 0x02, LoaDY_I, 0x01, LoaDAcc_I, 0x01, 0x00};
    auto cpu = CPU(0, mem);
    cpu.setOverflowFlag(false);
    cpu.run();
    EXPECT_EQ(0x00, cpu.getYRegister());
    EXPECT_EQ(0x01, cpu.getARegister());
}

TEST(CPUBranch, BVC_if_true) {
    std::array<uint8_t, 16> mem = {BranchonoVerflowClear, 0x02, LoaDY_I, 0x01, LoaDAcc_I, 0x01, 0x00};
    auto cpu = CPU(0, mem);
    cpu.setOverflowFlag(true);
    cpu.run();
    EXPECT_EQ(0x01, cpu.getYRegister());
    EXPECT_EQ(0x01, cpu.getARegister());
}

TEST(CPUBranch, BVS_if_false) {
    std::array<uint8_t, 16> mem = {BranchonoVerflowSet, 0x02, LoaDY_I, 0x01, LoaDAcc_I, 0x01, 0x00};
    auto cpu = CPU(0, mem);
    cpu.setOverflowFlag(false);
    cpu.run();
    EXPECT_EQ(0x01, cpu.getYRegister());
    EXPECT_EQ(0x01, cpu.getARegister());
}

TEST(CPUBranch, BVS_if_true) {
    std::array<uint8_t, 16> mem = {BranchonoVerflowSet, 0x02, LoaDY_I, 0x01, LoaDAcc_I, 0x01, 0x00};
    auto cpu = CPU(0, mem);
    cpu.setOverflowFlag(true);
    cpu.run();
    EXPECT_EQ(0x00, cpu.getYRegister());
    EXPECT_EQ(0x01, cpu.getARegister());
}

class CPUStack : public ::testing::Test {

};

TEST(CPUStack, TransferXtoStack) {
    std::array<uint8_t, 4> mem = {LoaDX_I, 0xff, TransferXtoStack, BReaK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0xff, cpu.getStackPointer());
}
// PHA : PusH Accumulator
TEST(CPUStack, PusHAcc) {
    std::array<uint8_t, 0x200> mem = {LoaDX_I, 0xff, TransferXtoStack, LoaDAcc_I, 0x01, PusHAcc, BReaK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0xfe, cpu.getStackPointer());
    EXPECT_EQ(0x01, cpu.getMemory()[0x1ff]);
}
// PLA : PuLl Accumulator
TEST(CPUStack, PuLlAcc) {
    std::array<uint8_t, 0x200> mem = {LoaDX_I, 0xff, TransferXtoStack, LoaDAcc_I, 0x01, PusHAcc, LoaDAcc_I, 0x02, PuLlAcc, BReaK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0xff, cpu.getStackPointer());
    EXPECT_EQ(0x01, cpu.getARegister());
    EXPECT_EQ(0x01, cpu.getMemory()[0x1ff]);
}

TEST(CPUStack, TransferStacktoX) {
    std::array<uint8_t, 0x200> mem = {LoaDX_I, 0xfe, TransferXtoStack, LoaDX_I, 0xff, TransferStacktoX, BReaK};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0xfe, cpu.getStackPointer());
    EXPECT_EQ(0xfe, cpu.getXRegister());
}

TEST(CPUStack, PHP_PLP) {
    std::array<uint8_t, 0x5> mem = {PusHProcessorstatus, LoaDAcc_I, 0x01, PuLlProcessorstatus, BReaK};
    auto cpu = CPU(0, mem);
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
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x00, cpu.getARegister());
    EXPECT_EQ(0xfd, cpu.getStackPointer());
    EXPECT_EQ(0x00, cpu.getMemory()[0x1ff]);
    EXPECT_EQ(0x05, cpu.getMemory()[0x1fe]);
}

TEST(CPUStack, ReTurnfromSubroutine) {
    std::array<uint8_t, 0x200> mem = {LoaDX_I, 0xff, TransferXtoStack, JumptoSubRoutine_Ab, 0x09, 0x00, LoaDAcc_I, 0xff, BReaK, ReTurnfromSubroutine};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0xff, cpu.getARegister());
    EXPECT_EQ(0xff, cpu.getStackPointer());
}

TEST(CPUStack, ReTurnfromInterrupt) {
    std::array<uint8_t, 0x10> mem = {LoaDAcc_I, 0x00, PusHAcc, LoaDAcc_I, 0x0b, PusHAcc, LoaDAcc_I, 0xff, PusHAcc, ReTurnfromInterrupt, BReaK, LoaDX_I, 0xff};
    auto cpu = CPU(0, mem);
    cpu.run();
    EXPECT_EQ(0x0e, cpu.getProgramCounter());
    EXPECT_TRUE(cpu.isCarryFlag());
    EXPECT_FALSE(cpu.isZeroFlag());
    EXPECT_TRUE(cpu.isDecimalFlag());
    EXPECT_TRUE(cpu.isOverflowFlag());
    EXPECT_TRUE(cpu.isNegativeFlag());

    EXPECT_EQ(0xff, cpu.getXRegister());
}