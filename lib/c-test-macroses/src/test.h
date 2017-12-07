
/**
 * @file test.h
 * @author Rogonov Stepan Alekseevich
 * @brief File containing several macroses, that simplifies tests writing.
 */

#ifndef SRLIB_TEST_MACROSES
#define SRLIB_TEST_MACROSES

#include <stdio.h>
#include <stdlib.h>

#include "flow-control.h"

/**
 * @def NEW_TEST(name)
 * @brief Create new test function.
 * @param  name Name of test function.
 */
#define NEW_TEST(name) \
	FlwSt name () {

/**
 * @def TEST_FAILURE
 * @brief Fail test.
 */
#define TEST_FAILURE \
	{printf("ERROR: Failure at %s:%d\n", __FILE__, __LINE__); return FLW_ST.failed;}

/**
 * @def TEST_FINISHED
 * @brief Finishing test.
 * @details If test execution finished without any failure, then
 * test is successfully passed.
 */
#define TEST_FINISHED \
	return FLW_ST.succeeded; }

/**
 * @def INIT_TESTS_CHECKS
 * @brief Entry point for test program.
 */
#define INIT_TESTS_CHECKS \
	int main() { FlwSt test_ret_val;

/**
 * @def DONE_TESTS_CHECKS
 * @brief Finishing test program.
 */
#define DONE_TESTS_CHECKS \
	printf("INFO: Tests passed successfully.\n"); \
	return EXIT_SUCCESS; }

/**
 * @var TEST_CHECK_UP
 * @brief Enable test execution in test check function \ref CHECK_TEST.
 */
static const int TEST_CHECK_UP = 1;

/**
 * @var TEST_CHECK_dn
 * @brief Skip test in test check function \ref CHECK_TEST.
 */
static const int TEST_CHECK_dn = 0;

/**
 * @def CHECK_TEST(check, name)
 * @brief Run test check.
 * @param  check Indicates, when test is enabled (\ref TEST_CHECK_UP)
 * or skipped (\ref TEST_CHECK_dn).
 * @param  name  Name of test function.
 */
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
