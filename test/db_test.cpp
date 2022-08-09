#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "gmock/gmock.h"
#include "gtest/gtest.h"



extern "C" {
#include "db.h"
}

int myadd(int a, int b)
{
    return a + b;
}

TEST(testCase, test1)
{
    EXPECT_EQ(myadd(2, 3), 5);
}

TEST(testString, test1)
{
    char *str = "hello";
    EXPECT_STREQ(str, "hello");
    // EXPECT_STREQ(str, "hello moto");
}

TEST(testInputBuffer, read_input)
{
    FILE *f = fopen("./testdata/input_buffer.txt", "r");
    InputBuffer *b = new_input_buffer();
    read_input(b, f);
    char *want = "insert 1 user1 person1@example.com";
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

    char *want = "(1, Alice, alice@example.com)";
    char got[100];
    sprintf(got, "(%d, %s, %s)", got_row->id, got_row->username,
            got_row->email);
    EXPECT_STREQ(got, want);
}