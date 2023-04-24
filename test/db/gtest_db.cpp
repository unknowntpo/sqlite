/*
 * Ref: https://shengyu7697.github.io/googletest/
 * google test
 */
#include "gtest/gtest.h"

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
    std::string str = "insert 1 user1 person1@example.com";
    // Create a memory buffer with the contents of the string
    const char *data = str.data();
    size_t size = str.size();

    // Open a stream using the memory buffer
    FILE *f = fmemopen(const_cast<char *>(data), size, "r");

    //    FILE *f = fopen("../testdata/input_buffer.txt", "r");
    char cwd[1024];
    EXPECT_TRUE(getcwd(cwd, sizeof(cwd)) != NULL);
    GTEST_LOG_(INFO) << "cwd = " << cwd << std::endl;

    EXPECT_FALSE(f == NULL);
    InputBuffer *b = new_input_buffer();
    read_input(b, f);
    const char *want = str.c_str();

    GTEST_LOG_(INFO) << "want: " << want << std::endl;

    GTEST_LOG_(INFO) << "buf: " << b->buffer << std::endl;

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
