
/**
 * @file atest.h
 * @author Rogonov Stepan Alekseevich
 * @brief File containing several macroses, that simplifies tests writing.
 * @details Significantly less of "syntax noise".
 * @code{.c}
 * NEW_ATEST(my_test)
 * 	if (1 != 1) ATEST_FAILURE;
 * ATEST_FINISHED
 *
 * NEW_ATEST(no_test)
 * ATEST_FINISHED
 *
 * INIT_ATESTS_CHECKS
 * 	CHECK_ATEST(ATEST_CHECK_UP, my_test);
 * 	CHECK_ATEST(ATEST_CHECK_dn, no_test);
 * DONE_ATESTS_CHECKS
 * @endcode
 */

#ifndef SRLIB_ATEST_MACROSES
#define SRLIB_ATEST_MACROSES

#include <stdio.h>
#include <stdlib.h>

#include "advanced-sr-lib-flow-control.h"

/**
 * @def NEW_ATEST(name)
 * @brief Create new test function.
 * @param  name Name of test function.
 */
#define NEW_ATEST(name) \
	Aflw name () { INIT_ADVANCED_FLOW_CONTROL;

signal_code_t signal_from_line_number(unsigned long int line)
{
	return make_signal_code2(line / 65536UL, line % 65536UL);
}

unsigned long int line_number_from_aflw(Aflw aflw)
{
	return
		  ((unsigned long int)(aflw.signal.code1)) * 65536UL
		+ ((unsigned long int)(aflw.signal.code2));
}

/**
 * @def ATEST_FAILURE
 * @brief Fail test.
 */
#define ATEST_FAILURE \
	;{signal_code_t e30607c8 = signal_from_line_number(__LINE__); AFLOW_FINISH_FAILED_WITH(e30607c8);};

/**
 * @def ATEST_FINISHED
 * @brief Finishing test.
 * @details If test execution finished without any failure, then
 * test is successfully passed.
 */
#define ATEST_FINISHED \
	; AFLOW_FINISH_SUCCEEDED; }

/**
 * @def INIT_ATESTS_CHECKS
 * @brief Entry point for test program.
 */
#define INIT_ATESTS_CHECKS \
	int main() { Aflw test_ret_val;

/**
 * @def DONE_ATESTS_CHECKS
 * @brief Finishing test program.
 */
#define DONE_ATESTS_CHECKS \
	; printf("INFO: Tests passed successfully.\n"); \
	return EXIT_SUCCESS; }

/**
 * @var ATEST_CHECK_UP
 * @brief Enable test execution in test check function \ref CHECK_TEST.
 */
static const int ATEST_CHECK_UP = 1;

/**
 * @var ATEST_CHECK_dn
 * @brief Skip test in test check function \ref CHECK_TEST.
 */
static const int ATEST_CHECK_dn = 0;

/**
 * @def CHECK_ATEST(check, name)
 * @brief Run test check.
 * @param  check Indicates, when test is enabled (\ref TEST_CHECK_UP)
 * or skipped (\ref TEST_CHECK_dn).
 * @param  name  Name of test function.
 */
#define CHECK_ATEST(check, name) \
	; if (check) { \
		test_ret_val = name(); \
		if (is_not_aflw_succeeded(test_ret_val)) { \
			printf("ERROR: FAILED test \"" #name "\" at %s:%lu.\n", __FILE__, line_number_from_aflw(test_ret_val)); \
			return EXIT_FAILURE; \
		} else { \
			printf("INFO: FINISHED SUCCESSFULLY test \"" #name "\".\n"); \
		} \
	} else { \
		printf("INFO: Test \"" #name "\" SKIPPED.\n"); \
	};

/**
 * @def ATEST_PASS
 * @brief Wrap aflw execution in tests.
 * @details Pass codeline with error in signal.
 * @code{.c}
 * NEW_ATEST(atest_example)
 * 	FLOW any_aflw_func() ATEST_PASS;
 * ATEST_FINISHED
 * @endcode
 */
#define ATEST_PASS \
	; {signal_code_t e30607c8 = signal_from_line_number(__LINE__); if (is_not_aflw_succeeded(AFLOW_VAR)) { AFLOW_FINISH_FAILED_WITH(e30607c8); } ;};

#endif //SRLIB_TEST_MACROSES
