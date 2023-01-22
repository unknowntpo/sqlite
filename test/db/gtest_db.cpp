/*
 * Ref: https://shengyu7697.github.io/googletest/
 * google test
 */
#include <gtest/gtest.h>

extern "C" {
#include "db/db.h"
}

int myadd(int a, int b)
{
    return a + b;
}

TEST(testCase, test1)
{
    EXPECT_EQ(myadd(2, 3), 5);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(testInputBuffer, read_input)
{
    FILE *f = fopen("./testdata/input_buffer.txt", "r");
    InputBuffer *b = new_input_buffer();
    read_input(b, f);
    std::string str = "insert 1 user1 person1@example.com";
    const char *want = str.c_str();
    EXPECT_EQ(b->input_length, strlen(want));
    EXPECT_STREQ(b->buffer, want);
}

TEST(testSerializeData, serialize_deserialize)
{
    Row row = {.id = 1, .username = "Alice", .email = "alice@example.com"};
    char *dest = (char *) malloc(sizeof(Row));
    EXPECT_TRUE(dest);
    serialize_row(&row, dest);

    Row *got_row = (Row *) malloc(sizeof(Row));
    EXPECT_TRUE(got_row);

    deserialize_row(dest, got_row);

    std::string str = "(1, Alice, alice@example.com)";
    const char *want = str.c_str();
    char got[100];
    sprintf(got, "(%d, %s, %s)", got_row->id, got_row->username,
            got_row->email);
    EXPECT_STREQ(got, want);
}
