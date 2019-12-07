#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../m6502_lib/Memory.cpp"
#include "../m6502_lib/Via.cpp"
#include <cstdint>
#include <array>


class ViaTest : public ::testing::Test {

};

TEST(ViaTest, initialise) {
    std::array<uint8_t, 0x8000> mem = {};
    auto memory = Memory(mem);
    memory.setValue(0xFE4E,0x11);
    auto via = Via(memory);
    via.initialise();
    // mos
    EXPECT_EQ(0xff, memory.getValue(0xFE40));
    EXPECT_EQ(0x00, memory.getValue(0xFE41));
    EXPECT_EQ(0x00, memory.getValue(0xFE42));
    EXPECT_EQ(0xff, memory.getValue(0xFE43));
    EXPECT_EQ(0x00, memory.getValue(0xFE4E));
    // user
    EXPECT_EQ(0xff, memory.getValue(0xFE60));
    EXPECT_EQ(0x00, memory.getValue(0xFE61));
    EXPECT_EQ(0x00, memory.getValue(0xFE62));
    EXPECT_EQ(0xff, memory.getValue(0xFE63));
}

