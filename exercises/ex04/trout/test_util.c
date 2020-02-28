//
// Created by Kyle Combes on 2/28/20 for Software Systems at Olin College of
// Engineering.
//

#include "minunit.h"
#include "util.h"
#include <string.h>

int tests_run = 0;

static char *test1() {
    char *res = icmpcode_v4(0);
    char *message = "test1 failed: icmpcode_v4(0) should return "
                    "\"network unreachable\"";
    mu_assert(message, strcmp(res, "network unreachable") == 0);
    return NULL;
}

static char *test2() {
    char *res = icmpcode_v4(-1);
    char *message = "test2 failed: icmpcode_v4(-1) should return "
                    "\"[unknown code]\"";
    mu_assert(message, strcmp(res, "[unknown code]") == 0);
    return NULL;
}

static char * all_tests() {
    mu_run_test(test1);
    mu_run_test(test2);
    return NULL;
}

int main(int argc, char **argv) {
    char *result = all_tests();
    if (result != NULL) {
        printf("%s\n", result);
    } else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}
