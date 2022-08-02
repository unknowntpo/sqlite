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

// TEST(prepareInsert, test1) {
//     InputBuffer *b = new_input_buffer();
//     Statement statement;
//     PrepareResult res = prepare_insert(b, &statement)
//     EXPECT_EQ(res,PREPARE_SUCCESS);
// }

TEST(testInputBuffer, read_input)
{
    printf(">>>>>>>>PROJECT_SOURCE_DIR\n");

    char cwd[300];
    if (getcwd(cwd, sizeof(cwd))) {
        printf("current working dir: %s\n", cwd);
    }

    FILE *f = fopen("./testdata/input_buffer.txt", "r");
    // printf("hello from printf\n");
    int c;
    while ((c = getc(f)) != EOF) {
        putchar(c);
    }
    printf("\n");
}