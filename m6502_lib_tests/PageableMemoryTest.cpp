#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../m6502_lib/PageableMemory.cpp"
#include <cstdint>
#include <array>


class PageableMemoryTest : public ::testing::Test {

};

TEST(PageableMemoryTest, RAMRead) {
    std::array<uint8_t, 0x8000> mem = {0x01, 0x02, 0x03};
    auto memory = PageableMemory(mem);

    EXPECT_EQ(0x01, memory.getValue(0));
    EXPECT_EQ(0x02, memory.getValue(1));
    EXPECT_EQ(0x03, memory.getValue(2));
    EXPECT_EQ(0x00, memory.getValue(3));
}

TEST(PageableMemoryTest, RAMWrite) {
    std::array<uint8_t, 0x8000> mem = {};
    auto memory = PageableMemory(mem);

    EXPECT_EQ(0x0, memory.getValue(0x0000));
    EXPECT_EQ(0x0, memory.getValue(0x7FFF));
    memory.setValue(0x0000, 0xFF);
    memory.setValue(0x7FFF, 0xFF);
    EXPECT_EQ(0xFF, memory.getValue(0x0000));
    EXPECT_EQ(0xFF, memory.getValue(0x7FFF));
}

TEST(PageableMemoryTest, OSRead) {
    std::array<uint8_t, 0x8000> mem = {0x01, 0x02, 0x03};
    auto memory = PageableMemory(mem);
    std::array<uint8_t, 0x4000> os = {};
    os[0x0000]=0xFF;
    os[0x3FFF]=0xFF;
    memory.setPageOS(os);

    EXPECT_EQ(0xFF, memory.getValue(0xC000));
    EXPECT_EQ(0xFF, memory.getValue(0xFFFF));
}
