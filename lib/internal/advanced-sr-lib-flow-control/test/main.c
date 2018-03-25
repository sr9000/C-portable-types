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
	unsigned int randUint[] = {
		  23202
		, 21609, 24947
		, 27873, 34920, 35087
		, 19122, 28348, 29103, 45541
	};
	signal_code_t signal;
	signal = make_signal_code1(randUint[0]);
	if (   signal.active_codes_number != 1
	    || signal.code1 != randUint[0]
	    || signal.code2 != 0
	    || signal.code3 != 0
	    || signal.code4 != 0
	) {
		TEST_FAILURE;
	}
	signal = make_signal_code2(randUint[1], randUint[2]);
	if (   signal.active_codes_number != 2
	    || signal.code1 != randUint[1]
	    || signal.code2 != randUint[2]
	    || signal.code3 != 0
	    || signal.code4 != 0
	) {
		TEST_FAILURE;
	}
	signal = make_signal_code3(randUint[3], randUint[4], randUint[5]);
	if (   signal.active_codes_number != 3
	    || signal.code1 != randUint[3]
	    || signal.code2 != randUint[4]
	    || signal.code3 != randUint[5]
	    || signal.code4 != 0
	) {
		TEST_FAILURE;
	}
	signal = make_signal_code4(randUint[6], randUint[7], randUint[8], randUint[9]);
	if (   signal.active_codes_number != 4
	    || signal.code1 != randUint[6]
	    || signal.code2 != randUint[7]
	    || signal.code3 != randUint[8]
	    || signal.code4 != randUint[9]
	) {
		TEST_FAILURE;
	}
TEST_FINISHED

NEW_TEST(test_signals_compairing)
	unsigned int randUint1[] = {
		  23202
		, 21609, 24947
		, 27873, 34920, 35087
		, 19122, 28348, 29103, 45541
	};

	unsigned int randUint2[] = {
		  2582
		, 28403, 39476
		, 14893, 26927, 28258
		, 14094, 16612, 23534, 51616
	};

	signal_code_t signals1[4];
	signal_code_t signals2[4];

	signals1[0] = make_signal_code1(randUint1[0]);
	signals1[1] = make_signal_code2(randUint1[1], randUint1[2]);
	signals1[2] = make_signal_code3(randUint1[3], randUint1[4], randUint1[5]);
	signals1[3] =
		make_signal_code4(
			  randUint1[6]
			, randUint1[7]
			, randUint1[8]
			, randUint1[9]
		);

	signals2[0] = make_signal_code1(randUint2[0]);
	signals2[1] = make_signal_code2(randUint2[1], randUint2[2]);
	signals2[2] = make_signal_code3(randUint2[3], randUint2[4], randUint2[5]);
	signals2[3] =
		make_signal_code4(
			  randUint2[6]
			, randUint2[7]
			, randUint2[8]
			, randUint2[9]
		);

	

TEST_FINISHED

INIT_TESTS_CHECKS
	CHECK_TEST(TEST_CHECK_UP, test_signal_code_empty);
	CHECK_TEST(TEST_CHECK_UP, test_make_signal_codes);
	CHECK_TEST(TEST_CHECK_UP, test_signals_compairing);
DONE_TESTS_CHECKS
