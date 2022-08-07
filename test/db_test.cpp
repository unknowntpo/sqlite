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

TEST(testSerializeData, serialize)
{
    // FILE *f = fopen("./testdata/input_buffer.txt", "r");
    // InputBuffer *b = new_input_buffer();
    // read_input(b, f);
    // char *want = "insert 1 user1 person1@example.com";
    Row row = {.id = 1, .username = "Alice", .email = "alice@example.com"};
    char *dest = (char *) calloc(1, sizeof(Row));
    print_row_byte((Row *) &dest);

    // char *dest = (char *) malloc(sizeof(Row));
    // set terminator
    // memset(&dest[sizeof(Row)], '\0', 1);
    EXPECT_TRUE(dest);
    print_row(&row);
    serialize_row(&row, dest);

    print_row_byte((Row *) &dest);


    // char *want = "lala";
    // EXPECT_STREQ(dest, strlen(want));
}