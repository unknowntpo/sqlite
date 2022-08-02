#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "gtest/gtest.h"
#include "gmock/gmock.h"



extern "C"{
    #include "db.h"
}

int myadd(int a, int b) {
    return a + b;
}

TEST(testCase, test1) {
    EXPECT_EQ(myadd(2, 3), 5);
}

TEST(testString, test1) {
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

TEST(testInputBuffer, read_input) {
    // FILE *f = fopen("/Users/ds904297/repo/unknowntpo/sqlite/temp.txt", "r");
    printf(">>>>>>>>PROJECT_SOURCE_DIR\n");

    char cwd[300]; 
  if (  getcwd(cwd,sizeof(cwd))) {
  printf("current working dir: %s", cwd);
  }
    // printf("PROJECT_SOURCE_DIR", project_source_dir);

    // char *project_source_dir = getenv("PROJECT_SOURCE_DIR");
    // printf("PROJECT_SOURCE_DIR", project_source_dir);
    // char *test_file_dir = (char*)malloc(100);
    // sprintf(test_file_dir, "%s/%s", project_source_dir, "test/testdata/input_buffer.txt");
    // printf("test file dir: %s", test_file_dir);
    // FILE *f = fopen(test_file_dir, "r");
    // long size = fsize(f);
    // printf("size of file: %ld \n",size);
    printf("hello from printf\n");
    // int c ;
    // // while((c = getc(f)) != EOF) {
    // //     putchar(c);
    // // }
}