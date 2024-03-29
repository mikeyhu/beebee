#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../m6502_lib/CPU.cpp"
#include <cstdint>
#include <array>
#include "Helpers.cpp"



class CPUGeneral : public ::testing::Test {
};

TEST(CPUGeneral, FoundBRK) {
    std::array<uint8_t, 0xffff> mem = {BReaK, 0x01, 0x02};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.setBreakLocation(0x01);
    cpu.run();
    EXPECT_TRUE(cpu.getCPUState().isBreakCommandFlag());
    EXPECT_EQ(0x201, cpu.getCPUState().getProgramCounter());
}

// ADC : ADd with Carry
TEST(CPUGeneral, ADC_I_nocarry) {
    std::array<uint8_t, 5> mem = {LoaDAcc_I, 0x10, ADdwithCarry_I, 0x0f, BReaK};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x1f, cpu.getCPUState().getARegister());
    EXPECT_FALSE(cpu.getCPUState().isCarryFlag());
}

// ADC : ADd with Carry
TEST(CPUGeneral, ADC_I_carry) {
    std::array<uint8_t, 5> mem = {LoaDAcc_I, 0xc0, ADdwithCarry_I, 0xc4, BReaK};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x84, cpu.getCPUState().getARegister());
    EXPECT_TRUE(cpu.getCPUState().isCarryFlag());
}

TEST(CPUGeneral, ADdwithCarry_Z) {
    std::array<uint8_t, 6> mem = {LoaDAcc_I, 0x10, ADdwithCarry_Z, 0x05, BReaK, 0x0f};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x1f, cpu.getCPUState().getARegister());
    EXPECT_FALSE(cpu.getCPUState().isCarryFlag());
}

TEST(CPUGeneral, ADdwithCarry_ZX) {
    std::array<uint8_t, 8> mem = {LoaDX_I, 0x02, LoaDAcc_I, 0x10, ADdwithCarry_ZX, 0x05, BReaK, 0x0f};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x1f, cpu.getCPUState().getARegister());
    EXPECT_FALSE(cpu.getCPUState().isCarryFlag());
}

TEST(CPUGeneral, ADdwithCarry_Ab) {
    std::array<uint8_t, 7> mem = {LoaDAcc_I, 0x10, ADdwithCarry_Ab, 0x06, 0x00, BReaK, 0x0f};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x1f, cpu.getCPUState().getARegister());
    EXPECT_FALSE(cpu.getCPUState().isCarryFlag());
}

TEST(CPUGeneral, ADdwithCarry_AbX) {
    std::array<uint8_t, 9> mem = {LoaDX_I, 0x02, LoaDAcc_I, 0x10, ADdwithCarry_AbX, 0x06, 0x00, BReaK, 0x0f};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x1f, cpu.getCPUState().getARegister());
    EXPECT_FALSE(cpu.getCPUState().isCarryFlag());
}

TEST(CPUGeneral, ADdwithCarry_AbY) {
    std::array<uint8_t, 9> mem = {LoaDY_I, 0x02, LoaDAcc_I, 0x10, ADdwithCarry_AbY, 0x06, 0x00, BReaK, 0x0f};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x1f, cpu.getCPUState().getARegister());
    EXPECT_FALSE(cpu.getCPUState().isCarryFlag());
}

// LDA : LoaD Accumulator

TEST(CPUGeneral, LoaDAcc_I) {
    std::array<uint8_t, 3> mem = {LoaDAcc_I, 0x08, BReaK};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x08, cpu.getCPUState().getARegister());
    EXPECT_FALSE(cpu.getCPUState().isNegativeFlag());
}

TEST(CPUGeneral, LDA_I_Negative) {
    std::array<uint8_t, 3> mem = {LoaDAcc_I, 0x80, BReaK};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getCPUState().getARegister());
    EXPECT_TRUE(cpu.getCPUState().isNegativeFlag());
}

TEST(CPUGeneral, LoaDAcc_Ab) {
    std::array<uint8_t, 5> mem = {LoaDAcc_Ab, 0x04, 0x00, BReaK, 0x80};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getCPUState().getARegister());
    EXPECT_EQ(0x04, cpu.getCPUState().getProgramCounter());
}

TEST(CPUGeneral, LoaDAcc_AbX) {
    std::array<uint8_t, 7> mem = {LoaDX_I, 0x01, LoaDAcc_AbX, 0x5, 0x0, BReaK, 0x80};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getCPUState().getARegister());
    EXPECT_EQ(0x06, cpu.getCPUState().getProgramCounter());
}

TEST(CPUGeneral, LoaDAcc_AbY) {
    std::array<uint8_t, 7> mem = {LoaDY_I, 0x01, LoaDAcc_AbY, 0x5, 0x0, BReaK, 0x80};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getCPUState().getARegister());
    EXPECT_EQ(0x06, cpu.getCPUState().getProgramCounter());
}

TEST(CPUGeneral, LoaDAcc_Z) {
    std::array<uint8_t, 4> mem = {LoaDAcc_Z, 0x03, BReaK, 0x80};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getCPUState().getARegister());
    EXPECT_EQ(0x03, cpu.getCPUState().getProgramCounter());
}

TEST(CPUGeneral, LoaDAcc_ZX) {
    std::array<uint8_t, 6> mem = {LoaDX_I, 0x02, LoaDAcc_ZX, 0x3, BReaK, 0x80};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getCPUState().getARegister());
    EXPECT_EQ(0x05, cpu.getCPUState().getProgramCounter());
}

TEST(CPUGeneral, LoaDAcc_ZX_wraparound) {
    std::array<uint8_t, 6> mem = {LoaDX_I, 0x06, LoaDAcc_ZX, 0xff, BReaK, 0x80};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getCPUState().getARegister());
    EXPECT_EQ(0x05, cpu.getCPUState().getProgramCounter());
}

TEST(CPUGeneral, LoaDAcc_IndirIndex) {
    std::array<uint8_t, 8> mem = {LoaDY_I, 0x01, LoaDAcc_IndirIndex, 0x06, BReaK, 0x80, 0x04, 0x00};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getCPUState().getARegister());
    EXPECT_EQ(0x05, cpu.getCPUState().getProgramCounter());
}

TEST(CPUGeneral, LoaDAcc_IndexIndir) {
    std::array<uint8_t, 8> mem = {LoaDX_I, 0x01, LoaDAcc_IndexIndir, 0x05, BReaK, 0x80, 0x05, 0x00};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getCPUState().getARegister());
    EXPECT_EQ(0x05, cpu.getCPUState().getProgramCounter());
}


// LDX : LoaD Xregister

TEST(CPUGeneral, LoaDX_I) {
    std::array<uint8_t, 3> mem = {LoaDX_I, 0x80, BReaK};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getCPUState().getXRegister());
}

TEST(CPUGeneral, LoaDX_Ab) {
    std::array<uint8_t, 5> mem = {LoaDX_Ab, 0x04, 0x00, BReaK, 0x80};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getCPUState().getXRegister());
    EXPECT_EQ(0x04, cpu.getCPUState().getProgramCounter());
}

TEST(CPUGeneral, LoaDX_AbY) {
    std::array<uint8_t, 7> mem = {LoaDY_I, 0x01, LoaDX_AbY, 0x5, 0x0, BReaK, 0x80};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getCPUState().getXRegister());
    EXPECT_EQ(0x06, cpu.getCPUState().getProgramCounter());
}

TEST(CPUGeneral, LoaDX_Z) {
    std::array<uint8_t, 4> mem = {LoaDX_Z, 0x03, BReaK, 0x80};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getCPUState().getXRegister());
    EXPECT_EQ(0x03, cpu.getCPUState().getProgramCounter());
}

TEST(CPUGeneral, LoaDX_ZY) {
    std::array<uint8_t, 6> mem = {LoaDY_I, 0x02, LoaDX_ZY, 0x3, BReaK, 0x80};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getCPUState().getXRegister());
    EXPECT_EQ(0x05, cpu.getCPUState().getProgramCounter());
}

// LDY : LoaD Yregister

TEST(CPUGeneral, LoaDY_I) {
    std::array<uint8_t, 3> mem = {LoaDY_I, 0x80, BReaK};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getCPUState().getYRegister());
}

TEST(CPUGeneral, LoaDY_Ab) {
    std::array<uint8_t, 5> mem = {LoaDY_Ab, 0x04, 0x00, BReaK, 0x80};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getCPUState().getYRegister());
    EXPECT_EQ(0x04, cpu.getCPUState().getProgramCounter());
}

TEST(CPUGeneral, LoaDY_AbX) {
    std::array<uint8_t, 7> mem = {LoaDX_I, 0x01, LoaDY_AbX, 0x5, 0x0, BReaK, 0x80};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getCPUState().getYRegister());
    EXPECT_EQ(0x06, cpu.getCPUState().getProgramCounter());
}

TEST(CPUGeneral, LoaDY_Z) {
    std::array<uint8_t, 4> mem = {LoaDY_Z, 0x03, BReaK, 0x80};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getCPUState().getYRegister());
    EXPECT_EQ(0x03, cpu.getCPUState().getProgramCounter());
}

TEST(CPUGeneral, LoaDY_ZX) {
    std::array<uint8_t, 6> mem = {LoaDX_I, 0x02, LoaDY_ZX, 0x3, BReaK, 0x80};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getCPUState().getYRegister());
    EXPECT_EQ(0x05, cpu.getCPUState().getProgramCounter());
}

// STA : STore Accumulator

TEST(CPUGeneral, SToreAcc_Ab) {
    std::array<uint8_t, 7> mem = {LoaDAcc_I, 0x80, SToreAcc_Ab, 0x06, 0x00, BReaK, 0x00};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getCPUState().getARegister());
    EXPECT_EQ(0x80, cpu.getMemoryAt(6));
}

TEST(CPUGeneral, SToreAcc_AbX) {
    std::array<uint8_t, 9> mem = {LoaDAcc_I, 0x80, LoaDX_I, 0x01, SToreAcc_AbX, 0x07, 0x00, BReaK, 0x00};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getCPUState().getARegister());
    EXPECT_EQ(0x80, cpu.getMemoryAt(8));
}

TEST(CPUGeneral, SToreAcc_AbY) {
    std::array<uint8_t, 9> mem = {LoaDAcc_I, 0x80, LoaDY_I, 0x01, SToreAcc_AbY, 0x07, 0x00, BReaK, 0x00};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getCPUState().getARegister());
    EXPECT_EQ(0x80, cpu.getMemoryAt(8));
}

TEST(CPUGeneral, SToreAcc_Z) {
    std::array<uint8_t, 6> mem = {LoaDAcc_I, 0x80, SToreAcc_Z, 0x05, BReaK, 0x00};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getCPUState().getARegister());
    EXPECT_EQ(0x80, cpu.getMemoryAt(5));
}

TEST(CPUGeneral, SToreAcc_ZX) {
    std::array<uint8_t, 8> mem = {LoaDAcc_I, 0x80, LoaDX_I, 0x02, SToreAcc_ZX, 0x05, BReaK, 0x00};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getCPUState().getARegister());
    EXPECT_EQ(0x80, cpu.getMemoryAt(7));
}

TEST(CPUGeneral, SToreAcc_IndirIndex) {
    std::array<uint8_t, 10> mem = {LoaDAcc_I, 0x80, LoaDY_I, 0x01, SToreAcc_IndirIndex, 0x08, BReaK, 0x00, 0x06, 0x00};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getCPUState().getARegister());
    EXPECT_EQ(0x80, cpu.getMemoryAt(7));
}

TEST(CPUGeneral, SToreAcc_IndexIndir) {
    std::array<uint8_t, 10> mem = {LoaDAcc_I, 0x80, LoaDX_I, 0x01, SToreAcc_IndexIndir, 0x07, BReaK, 0x00, 0x07, 0x00};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getCPUState().getARegister());
    EXPECT_EQ(0x80, cpu.getMemoryAt(7));
}

// STX : STore Xregister

TEST(CPUGeneral, SToreX_Ab) {
    std::array<uint8_t, 7> mem = {LoaDX_I, 0x80, SToreX_Ab, 0x06, 0x00, BReaK, 0x00};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getMemoryAt(6));
}

TEST(CPUGeneral, SToreX_Z) {
    std::array<uint8_t, 6> mem = {LoaDX_I, 0x80, SToreX_Z, 0x05, BReaK, 0x00};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getMemoryAt(5));
}

TEST(CPUGeneral, SToreX_ZY) {
    std::array<uint8_t, 8> mem = {LoaDX_I, 0x80, LoaDY_I, 0x02, SToreX_ZY, 0x05, BReaK, 0x00};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getMemoryAt(7));
}

// STY : STore Yregister

TEST(CPUGeneral, SToreY_Ab) {
    std::array<uint8_t, 7> mem = {LoaDY_I, 0x80, SToreY_Ab, 0x06, 0x00, BReaK, 0x00};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getMemoryAt(6));
}

TEST(CPUGeneral, SToreY_Z) {
    std::array<uint8_t, 6> mem = {LoaDY_I, 0x80, SToreY_Z, 0x05, BReaK, 0x00};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getMemoryAt(5));
}

TEST(CPUGeneral, SToreY_ZX) {
    std::array<uint8_t, 8> mem = {LoaDY_I, 0x80, LoaDX_I, 0x02, SToreY_ZX, 0x05, BReaK, 0x00};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x80, cpu.getMemoryAt(7));
}

TEST(CPUGeneral, CLearCarry) {
    std::array<uint8_t, 2> mem = {CLearCarry, BReaK};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.getCPUState().setCarryFlag(true);
    cpu.run();
    EXPECT_FALSE(cpu.getCPUState().isCarryFlag());
}

TEST(CPUGeneral, SEtCarry) {
    std::array<uint8_t, 2> mem = {SEtCarry, BReaK};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.getCPUState().setCarryFlag(false);
    cpu.run();
    EXPECT_TRUE(cpu.getCPUState().isCarryFlag());
}

TEST(CPUGeneral, CLearDecimal) {
    std::array<uint8_t, 2> mem = {CLearDecimal, BReaK};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.getCPUState().setDecimalFlag(true);
    cpu.run();
    EXPECT_FALSE(cpu.getCPUState().isDecimalFlag());
}

TEST(CPUGeneral, SEtDecimal) {
    std::array<uint8_t, 2> mem = {SEtDecimal, BReaK};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.getCPUState().setDecimalFlag(false);
    cpu.run();
    EXPECT_TRUE(cpu.getCPUState().isDecimalFlag());
}

TEST(CPUGeneral, CLearinterrupt) {
    std::array<uint8_t, 2> mem = {CLearInterrupt, BReaK};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.getCPUState().setInterruptDisableFlag(true);
    cpu.run();
    EXPECT_FALSE(cpu.getCPUState().isInterruptDisableFlag());
}

TEST(CPUGeneral, SEtInterrupt) {
    std::array<uint8_t, 2> mem = {SEtInterrupt, BReaK};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.getCPUState().setInterruptDisableFlag(false);
    cpu.run();
    EXPECT_TRUE(cpu.getCPUState().isInterruptDisableFlag());
}

TEST(CPUGeneral, CLearoVerflow) {
    std::array<uint8_t, 2> mem = {CLearoVerflow, BReaK};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.getCPUState().setOverflowFlag(true);
    cpu.run();
    EXPECT_FALSE(cpu.getCPUState().isOverflowFlag());
}

TEST(CPUGeneral, JuMP_Ab) {
    std::array<uint8_t, 6> mem = {JuMP_Ab, 0x05, 0x00, LoaDX_I, 0xff, BReaK};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x00, cpu.getCPUState().getXRegister());
    EXPECT_EQ(0x06, cpu.getCPUState().getProgramCounter());
}

TEST(CPUGeneral, JuMP_Indir) {
    std::array<uint8_t, 8> mem = {JuMP_Indir, 0x06, 0x00, LoaDX_I, 0xff, BReaK, 0x03, 0x00};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0xff, cpu.getCPUState().getXRegister());
    EXPECT_EQ(0x06, cpu.getCPUState().getProgramCounter());
}

// INcrement

TEST(CPUGeneral, INcrementX) {
    std::array<uint8_t, 4> mem = {LoaDX_I, 0x01, INcrementX, BReaK};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x02, cpu.getCPUState().getXRegister());
}

TEST(CPUGeneral, INcrementY) {
    std::array<uint8_t, 4> mem = {LoaDY_I, 0x01, INcrementY, BReaK};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x02, cpu.getCPUState().getYRegister());
}

TEST(CPUGeneral, INCrement_Z) {
    std::array<uint8_t, 4> mem = {INCrement_Z, 0x03, BReaK, 0x01};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x02, cpu.getMemoryAt(3));
}

TEST(CPUGeneral, INCrement_ZX) {
    std::array<uint8_t, 6> mem = {LoaDX_I, 0x02, INCrement_ZX, 0x03, BReaK, 0x01};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x02, cpu.getMemoryAt(5));
}

TEST(CPUGeneral, INCrement_Ab) {
    std::array<uint8_t, 5> mem = {INCrement_Ab, 0x04, 0x00, BReaK, 0x01};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x02, cpu.getMemoryAt(4));
}

TEST(CPUGeneral, INCrement_AbX) {
    std::array<uint8_t, 7> mem = {LoaDX_I, 0x02, INCrement_AbX, 0x04, 0x00, BReaK, 0x01};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x02, cpu.getMemoryAt(6));
}

// DEcrement

TEST(CPUGeneral, DEcrementX) {
    std::array<uint8_t, 4> mem = {LoaDX_I, 0x02, DEcrementX, BReaK};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x01, cpu.getCPUState().getXRegister());
    EXPECT_FALSE(cpu.getCPUState().isZeroFlag());
}

TEST(CPUGeneral, DEX_zeroflag) {
    std::array<uint8_t, 4> mem = {LoaDX_I, 0x01, DEcrementX, BReaK};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x00, cpu.getCPUState().getXRegister());
    EXPECT_TRUE(cpu.getCPUState().isZeroFlag());
}

TEST(CPUGeneral, DEcrementY) {
    std::array<uint8_t, 4> mem = {LoaDY_I, 0x02, DEcrementY, BReaK};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x01, cpu.getCPUState().getYRegister());
}

TEST(CPUGeneral, DEY_zeroflag) {
    std::array<uint8_t, 4> mem = {LoaDY_I, 0x01, DEcrementY, BReaK};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x00, cpu.getCPUState().getYRegister());
    EXPECT_TRUE(cpu.getCPUState().isZeroFlag());
}

TEST(CPUGeneral, DECrement_Z) {
    std::array<uint8_t, 4> mem = {DECrement_Z, 0x03, BReaK, 0x05};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x04, cpu.getMemoryAt(3));
}

TEST(CPUGeneral, DECrement_ZX) {
    std::array<uint8_t, 6> mem = {LoaDX_I, 0x02, DECrement_ZX, 0x03, BReaK, 0x05};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x04, cpu.getMemoryAt(5));
}

TEST(CPUGeneral, DECrement_Ab) {
    std::array<uint8_t, 5> mem = {DECrement_Ab, 0x04, 0x00, BReaK, 0x02};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x01, cpu.getMemoryAt(4));
}

TEST(CPUGeneral, DECrement_AbX) {
    std::array<uint8_t, 7> mem = {LoaDX_I, 0x02, DECrement_AbX, 0x04, 0x00, BReaK, 0x02};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x01, cpu.getMemoryAt(6));
}
// T Transfer

TEST(CPUGeneral, TransferAtoX) {
    std::array<uint8_t, 4> mem = {LoaDAcc_I, 0x02, TransferAtoX, BReaK};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x02, cpu.getCPUState().getXRegister());
}

TEST(CPUGeneral, TransferAtoY) {
    std::array<uint8_t, 4> mem = {LoaDAcc_I, 0x02, TransferAtoY, BReaK};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x02, cpu.getCPUState().getYRegister());
}

TEST(CPUGeneral, TransferXtoA) {
    std::array<uint8_t, 4> mem = {LoaDX_I, 0x02, TransferXtoA, BReaK};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x02, cpu.getCPUState().getARegister());
}

TEST(CPUGeneral, TransferYtoA) {
    std::array<uint8_t, 4> mem = {LoaDY_I, 0x02, TransferYtoA, BReaK};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x02, cpu.getCPUState().getARegister());
}

TEST(CPUGeneral, SuBtractwithCarry_Z_simple) {
    std::array<uint8_t, 6> mem = {LoaDAcc_I, 0x05, SuBtractwithCarry_Z, 0x05, BReaK, 0x03};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.run();
    EXPECT_EQ(0x01, cpu.getCPUState().getARegister()); //carry flag is off
    EXPECT_FALSE(cpu.getCPUState().isCarryFlag());
    EXPECT_FALSE(cpu.getCPUState().isNegativeFlag());
    EXPECT_FALSE(cpu.getCPUState().isZeroFlag());
    EXPECT_FALSE(cpu.getCPUState().isOverflowFlag());
}

TEST(CPUGeneral, SuBtractwithCarry_Z_zero) {
    std::array<uint8_t, 6> mem = {LoaDAcc_I, 0x04, SuBtractwithCarry_Z, 0x05, BReaK, 0x04};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.getCPUState().setCarryFlag(true);
    cpu.run();
    EXPECT_EQ(0x0, cpu.getCPUState().getARegister());
    EXPECT_TRUE(cpu.getCPUState().isCarryFlag());
    EXPECT_FALSE(cpu.getCPUState().isNegativeFlag());
    EXPECT_TRUE(cpu.getCPUState().isZeroFlag());
    EXPECT_FALSE(cpu.getCPUState().isOverflowFlag());
}

TEST(CPUGeneral, SuBtractwithCarry_Z_negative) {
    std::array<uint8_t, 6> mem = {LoaDAcc_I, 0x0, SuBtractwithCarry_Z, 0x05, BReaK, 0xff};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.getCPUState().setCarryFlag(true);
    cpu.run();
    EXPECT_EQ(0x1, cpu.getCPUState().getARegister());
    EXPECT_TRUE(cpu.getCPUState().isCarryFlag());
    EXPECT_TRUE(cpu.getCPUState().isNegativeFlag());
    EXPECT_FALSE(cpu.getCPUState().isZeroFlag());
    EXPECT_FALSE(cpu.getCPUState().isOverflowFlag());
}

TEST(CPUGeneral, SuBtractwithCarry_Z) {
    std::array<uint8_t, 6> mem = {LoaDAcc_I, 0x0, SuBtractwithCarry_Z, 0x05, BReaK, 0xff};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.getCPUState().setCarryFlag(true);
    cpu.run();
    EXPECT_EQ(0x1, cpu.getCPUState().getARegister());
    EXPECT_TRUE(cpu.getCPUState().isCarryFlag());
    EXPECT_TRUE(cpu.getCPUState().isNegativeFlag());
    EXPECT_FALSE(cpu.getCPUState().isZeroFlag());
    EXPECT_FALSE(cpu.getCPUState().isOverflowFlag());
}

TEST(CPUGeneral, runOnce) {
    std::array<uint8_t, 6> mem = {LoaDAcc_I, 0xff, LoaDX_I, 0xff};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.runOnce();
    EXPECT_EQ(0xff, cpu.getCPUState().getARegister());
    EXPECT_EQ(0x00, cpu.getCPUState().getXRegister());
}

TEST(CPUGeneral, runUntilInteruptable) {
    std::array<uint8_t, 7> mem = {LoaDAcc_I, 0xff, LoaDX_I, 0xff, CLearInterrupt, LoaDY_I, 0xff};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.getCPUState().setInterruptDisableFlag(true);
    cpu.runUntilInteruptable();
    EXPECT_EQ(0xff, cpu.getCPUState().getARegister());
    EXPECT_EQ(0xff, cpu.getCPUState().getXRegister());
    EXPECT_EQ(0x00, cpu.getCPUState().getYRegister());
}
