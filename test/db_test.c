#include <string.h>
#include "db.h"
#include "src/minunit.h"

char *test_hello()
{
    return TEST_PASS;
}

char *all_tests() 
{
    mu_suite_start();
    mu_run_test(test_hello);

    return TEST_PASS;
}