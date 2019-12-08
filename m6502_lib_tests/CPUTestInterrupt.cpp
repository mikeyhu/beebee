#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../m6502_lib/CPU.cpp"
#include <cstdint>
#include <array>
#include "Helpers.cpp"

class CPUInterrupt : public ::testing::Test {

};

TEST(CPUInterrupt, HandleInterruptIRQ) {
    std::array<uint8_t, 0xFFFF> mem = {LoaDX_I, 0xff, TransferXtoA, BReaK,LoaDY_I, 0xee, ReTurnfromInterrupt};
    auto memory = Memory(mem);
    memory.setValue(0xFFFE, 0x04);
    memory.setValue(0xFFFF, 0x00);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.runOnce();
    cpu.getCPUState().setIRQ(IRQ_LOW);
    cpu.runOnce();
    cpu.runOnce();
    EXPECT_EQ(0xff, cpu.getCPUState().getXRegister());
    EXPECT_EQ(0x00, cpu.getCPUState().getARegister());
    EXPECT_EQ(0xee, cpu.getCPUState().getYRegister());
    cpu.runOnce();
    cpu.runOnce();
    EXPECT_EQ(0xff, cpu.getCPUState().getARegister());
}

TEST(CPUInterrupt, DisableHandleInterruptIRQ) {
    std::array<uint8_t, 0xFFFF> mem = {LoaDX_I, 0xff, TransferXtoA, BReaK,LoaDY_I, 0xee, ReTurnfromInterrupt};
    auto memory = Memory(mem);
    auto cpu = CPU(0, memory, cycleCallback);
    cpu.getCPUState().setInterruptDisableFlag(true);
    cpu.getCPUState().setIRQ(IRQ_LOW);
    cpu.run();
    EXPECT_EQ(0xff, cpu.getCPUState().getXRegister());
    EXPECT_EQ(0xff, cpu.getCPUState().getARegister());
    EXPECT_EQ(0x00, cpu.getCPUState().getYRegister());
}
