#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../m6502_lib/Memory.cpp"
#include "../m6502_lib/Via.cpp"
#include <cstdint>
#include <array>


class ViaTest : public ::testing::Test {

};

TEST(ViaTest, initialiseMos) {
    std::array<uint8_t, 0x8000> mem = {};
    auto memory = Memory(mem);
    for(uint16_t i = 0xFE40;i< 0xFE50;i++) {
        memory.setValue(i,0x11);
    }
    auto via = Via(memory);
    via.initialise();

    EXPECT_EQ(0xff, memory.getValue(0xFE40));
    EXPECT_EQ(0x00, memory.getValue(0xFE41));
    EXPECT_EQ(0x00, memory.getValue(0xFE42));
    EXPECT_EQ(0xff, memory.getValue(0xFE43));
    EXPECT_EQ(0x00, memory.getValue(0xFE44));
    EXPECT_EQ(0x00, memory.getValue(0xFE45));
    EXPECT_EQ(0x00, memory.getValue(0xFE46));
    EXPECT_EQ(0x00, memory.getValue(0xFE47));
    EXPECT_EQ(0x00, memory.getValue(0xFE48));
    EXPECT_EQ(0x00, memory.getValue(0xFE49));
    EXPECT_EQ(0x00, memory.getValue(0xFE4A));
    EXPECT_EQ(0x00, memory.getValue(0xFE4B));
    EXPECT_EQ(0x00, memory.getValue(0xFE4C));
    EXPECT_EQ(0x00, memory.getValue(0xFE4D));
    EXPECT_EQ(0x00, memory.getValue(0xFE4E));
    EXPECT_EQ(0x00, memory.getValue(0xFE4F));
}

TEST(ViaTest, initialiseUser) {
    std::array<uint8_t, 0x8000> mem = {};
    auto memory = Memory(mem);
    for(uint16_t i = 0xFE60;i< 0xFE70;i++) {
        memory.setValue(i,0x11);
    }
    auto via = Via(memory);
    via.initialise();

    EXPECT_EQ(0xff, memory.getValue(0xFE60));
    EXPECT_EQ(0x00, memory.getValue(0xFE61));
    EXPECT_EQ(0x00, memory.getValue(0xFE62));
    EXPECT_EQ(0xff, memory.getValue(0xFE63));
    EXPECT_EQ(0x00, memory.getValue(0xFE64));
    EXPECT_EQ(0x00, memory.getValue(0xFE65));
    EXPECT_EQ(0x00, memory.getValue(0xFE66));
    EXPECT_EQ(0x00, memory.getValue(0xFE67));
    EXPECT_EQ(0x00, memory.getValue(0xFE68));
    EXPECT_EQ(0x00, memory.getValue(0xFE69));
    EXPECT_EQ(0x00, memory.getValue(0xFE6A));
    EXPECT_EQ(0x00, memory.getValue(0xFE6B));
    EXPECT_EQ(0x00, memory.getValue(0xFE6C));
    EXPECT_EQ(0x00, memory.getValue(0xFE6D));
    EXPECT_EQ(0x00, memory.getValue(0xFE6E));
    EXPECT_EQ(0x00, memory.getValue(0xFE6F));
}

