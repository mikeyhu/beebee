#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../m6502_lib/CPU.cpp"

class CPUTest : public ::testing::Test {

};

TEST(CPUTest, IsTrue) {
    bool result = CPU::isTrue();
    EXPECT_TRUE(result);
}