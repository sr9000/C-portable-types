#include <advanced-sr-lib-flow-control.h>
#include "advanced-sr-lib-flow-control.h"
#include "test.h"

NEW_TEST(test_signal_code_empty)
	if (   SIGNAL_CODE.empty.active_codes_number != 0
	    || SIGNAL_CODE.empty.code1 != 0
	    || SIGNAL_CODE.empty.code2 != 0
	    || SIGNAL_CODE.empty.code3 != 0
	    || SIGNAL_CODE.empty.code4 != 0
	) {
		TEST_FAILURE;
	}
TEST_FINISHED

NEW_TEST(test_make_signal_codes)
	unsigned int c1 = 11611, c2 = 14260, c3 = 15282, c4 = 25739;
	signal_code_t signal;
	signal = make_signal_code1(c4);
	if (   signal.active_codes_number != 1
	    || signal.code1 != c4
	    || signal.code2 != 0
	    || signal.code3 != 0
	    || signal.code4 != 0
	) {
		TEST_FAILURE;
	}
	signal = make_signal_code2(c3, c4);
	if (   signal.active_codes_number != 2
	    || signal.code1 != c3
	    || signal.code2 != c4
	    || signal.code3 != 0
	    || signal.code4 != 0
	) {
		TEST_FAILURE;
	}
	signal = make_signal_code3(c2, c3, c4);
	if (   signal.active_codes_number != 3
	    || signal.code1 != c2
	    || signal.code2 != c3
	    || signal.code3 != c4
	    || signal.code4 != 0
	) {
		TEST_FAILURE;
	}
	signal = make_signal_code4(c1, c2, c3, c4);
	if (   signal.active_codes_number != 4
	    || signal.code1 != c1
	    || signal.code2 != c2
	    || signal.code3 != c3
	    || signal.code4 != c4
	) {
		TEST_FAILURE;
	}
TEST_FINISHED

INIT_TESTS_CHECKS
	CHECK_TEST(TEST_CHECK_UP, test_signal_code_empty);
	CHECK_TEST(TEST_CHECK_UP, test_make_signal_codes);
DONE_TESTS_CHECKS
