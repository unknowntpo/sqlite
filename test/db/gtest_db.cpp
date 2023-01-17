/*
 * Ref: https://shengyu7697.github.io/googletest/
 * google test
 */
#include <gtest/gtest.h>


int myadd(int a, int b) {
    return a + b;
}

TEST(testCase, test1) {
    EXPECT_EQ(myadd(2, 3), 5);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
