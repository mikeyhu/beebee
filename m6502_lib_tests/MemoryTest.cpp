#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../m6502_lib/Memory.cpp"
#include <cstdint>
#include <array>


class MemoryTest : public ::testing::Test {

};

TEST(MemoryTest, Create) {
    std::array<uint8_t, 4> mem = {0x01, 0x02, 0x03};
    auto memory = Memory(mem);

    EXPECT_EQ(0x01, memory.getValue(0));
    EXPECT_EQ(0x02, memory.getValue(1));
    EXPECT_EQ(0x03, memory.getValue(2));
}

TEST(MemoryTest, Update) {
    std::array<uint8_t, 4> mem = {0x01, 0x02, 0x03};
    auto memory = Memory(mem);

    memory.setValue(1, 0xff);
    EXPECT_EQ(0x01, memory.getValue(0));
    EXPECT_EQ(0xff, memory.getValue(1));
    EXPECT_EQ(0x02, mem[1]);
    EXPECT_EQ(0x03, memory.getValue(2));
}