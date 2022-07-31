#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "gtest/gtest.h"

extern "C"{
    #include "db.h"
}


int myadd(int a, int b) {
    return a + b;
}

TEST(testCase, test1) {
    EXPECT_EQ(myadd(2, 3), 5);
}

TEST(testInputBuffer, read_input) {
    // char *project_source_dir = getenv("PROJECT_SOURCE_DIR");
    // char *test_file_dir = sprintf("%s/%s", project_source_dir, "test/testdata/input_buffer.txt")
    FILE *f = fopen("temp.txt", "w");
    fclose(f);
    freopen("temp.txt", "w", stdout);
    printf("hello");
    f = fopen("temp.txt", "r");
    
    char out[10] = {0};
    fgets(out, 10, f);
    EXPECT_TRUE(strcmp(out, "hello1"));
}