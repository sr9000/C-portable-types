#ifndef SRLIB_TEST_MACROSES
#define SRLIB_TEST_MACROSES

#include <stdio.h>
#include <stdlib.h>

#include "flow-control.h"


#define NEW_TEST(name) \
	FlwSt name () {

#define TEST_FAILURE \
	{printf("ERROR: Failure at %s:%d\n", __FILE__, __LINE__); return FLW_ST.failed;}

#define TEST_FINISHED \
	return FLW_ST.succeeded; }

#define INIT_TESTS_CHECKS \
	int main() { FlwSt test_ret_val;

#define DONE_TESTS_CHECKS \
	printf("INFO: Tests passed successfully.\n"); \
	return EXIT_SUCCESS; }

static const int TEST_CHECK_UP = 1;
static const int TEST_CHECK_dn = 0;

#define CHECK_TEST(check, name) \
	if (check) { \
		test_ret_val = name(); \
		if (is_flow_not_succeeded(test_ret_val)) { \
			printf("ERROR: FAILED test \"" #name "\".\n"); \
			return EXIT_FAILURE; \
		} else { \
			printf("INFO: FINISHED SUCCESSFULLY test \"" #name "\".\n"); \
		} \
	} else { \
		printf("INFO: Test \"" #name "\" SKIPPED.\n"); \
	}

#endif //SRLIB_TEST_MACROSES
