#include <gtest/gtest.h>
#include <emptyTestHeader.h>

TEST(InitialTest, EmptyTestEQ) {
    EXPECT_EQ(NumberGenerator::getNumber7(),7);
}

TEST(InitialTest, EmptyTestNE) {
    EXPECT_NE(NumberGenerator::getNumber7(),6);
}