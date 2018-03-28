#include "test.h"
#include "advanced-sr-lib-flow-control.h"
#include "internal/advanced-sr-lib-flow-control.h"

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

NEW_TEST(test_signals_internal_compairing)
	unsigned int randUint1[] = {19122, 28348, 29103, 45541};
	unsigned int randUint2[] = {14094, 16612, 23534, 51616};
	signal_code_t s1, s2;
	s1 = SIGNAL_CODE.empty;
	s2 = SIGNAL_CODE.empty;

	s1.code1 = randUint1[0];
	s1.code2 = randUint1[1];
	s1.code3 = randUint1[2];
	s1.code4 = randUint1[3];

	s2.code1 = randUint2[0];
	s2.code2 = randUint2[1];
	s2.code3 = randUint2[2];
	s2.code4 = randUint2[3];

	if (   !is_signals_equal(s1, s2)
	    ||  is_not_signals_equal(s1, s2)
	) {
		TEST_FAILURE;
	}

	s1.code1 = s2.code1 = randUint1[0];
	if (!is_signals_code1_equal(s1, s2))
	{
		TEST_FAILURE;
	}
	s1.active_codes_number = s2.active_codes_number = 1;
	if (   !is_signals_equal(s1, s2)
	    ||  is_not_signals_equal(s1, s2)
	) {
		TEST_FAILURE;
	}

	s1.code2 = s2.code2 = randUint1[1];
	if (!is_signals_code2_equal(s1, s2))
	{
		TEST_FAILURE;
	}
	s1.active_codes_number = s2.active_codes_number = 2;
	if (   !is_signals_equal(s1, s2)
	    ||  is_not_signals_equal(s1, s2)
	) {
		TEST_FAILURE;
	}

	s1.code3 = s2.code3 = randUint1[2];
	if (!is_signals_code1_equal(s1, s2))
	{
		TEST_FAILURE;
	}
	s1.active_codes_number = s2.active_codes_number = 3;
	if (   !is_signals_equal(s1, s2)
	    ||  is_not_signals_equal(s1, s2)
	) {
		TEST_FAILURE;
	}

	s1.code4 = s2.code4 = randUint1[3];
	if (!is_signals_code1_equal(s1, s2))
	{
		TEST_FAILURE;
	}
	s1.active_codes_number = s2.active_codes_number = 4;
	if (   !is_signals_equal(s1, s2)
	    ||  is_not_signals_equal(s1, s2)
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

	if (is_not_signals_equal(SIGNAL_CODE.empty, SIGNAL_CODE.empty))
	{
		TEST_FAILURE;
	}
	if (!is_signals_equal(SIGNAL_CODE.empty, SIGNAL_CODE.empty))
	{
		TEST_FAILURE;
	}

	for (int i = 0; i < 4; ++i)
	{
		if (is_signals_equal(signals1[i], signals2[i]))
		{
			TEST_FAILURE;
		}
		if (is_signals_equal(signals1[i], SIGNAL_CODE.empty))
		{
			TEST_FAILURE;
		}
		if (is_signals_equal(SIGNAL_CODE.empty, signals2[i]))
		{
			TEST_FAILURE;
		}
		if (is_not_signals_equal(signals1[i], signals1[i]))
		{
			TEST_FAILURE;
		}
		if (is_not_signals_equal(signals2[i], signals2[i]))
		{
			TEST_FAILURE;
		}
		// inverse conditions
		if (!is_not_signals_equal(signals1[i], signals2[i]))
		{
			TEST_FAILURE;
		}
		if (!is_not_signals_equal(signals1[i], SIGNAL_CODE.empty))
		{
			TEST_FAILURE;
		}
		if (!is_not_signals_equal(SIGNAL_CODE.empty, signals2[i]))
		{
			TEST_FAILURE;
		}
		if (!is_signals_equal(signals1[i], signals1[i]))
		{
			TEST_FAILURE;
		}
		if (!is_signals_equal(signals2[i], signals2[i]))
		{
			TEST_FAILURE;
		}
	}
TEST_FINISHED

NEW_TEST(test_make_and_def_processor_aflw)
	unsigned int randUint1[] = {19122, 28348, 29103, 45541};
	Aflw aflw, def;
	signal_code_t signal;
	signal =
		make_signal_code4(
			  randUint1[0]
			, randUint1[1]
			, randUint1[2]
			, randUint1[3]
		);

	// FlwST & signal
	aflw = make_aflw_signal(FLW_ST.succeeded, signal);
	if (   !is_flow_succeeded(aflw.flow_state)
	    || !is_signals_equal(aflw.signal, signal)
	    || !has_aflw_signal(aflw)
	    ||  has_not_aflw_signal(aflw)
	    || !is_aflw_succeeded(aflw)
	    ||  is_not_aflw_succeeded(aflw)
	) {
		TEST_FAILURE;
	}
	def = default_aflw_processor(aflw);
	if (   aflw.flow_state.val != def.flow_state.val
	    || is_not_signals_equal(aflw.signal, def.signal)
	) {
		TEST_FAILURE;
	}
	aflw = make_aflw_signal(FLW_ST.failed, signal);
	if (   !is_flow_failed(aflw.flow_state)
	    || !is_signals_equal(aflw.signal, signal)
	    || !has_aflw_signal(aflw)
	    ||  has_not_aflw_signal(aflw)
	    || !is_aflw_failed(aflw)
	    || !is_not_aflw_succeeded(aflw)
	) {
		TEST_FAILURE;
	}
	def = default_aflw_processor(aflw);
	if (   aflw.flow_state.val != def.flow_state.val
	       || is_not_signals_equal(aflw.signal, def.signal)
		) {
		TEST_FAILURE;
	}
	aflw = make_aflw_signal(FLW_ST.crashed, signal);
	if (   !is_flow_crashed(aflw.flow_state)
	    || !is_signals_equal(aflw.signal, signal)
	    || !has_aflw_signal(aflw)
	    ||  has_not_aflw_signal(aflw)
	    || !is_aflw_crashed(aflw)
	    || !is_not_aflw_succeeded(aflw)
	) {
		TEST_FAILURE;
	}
	def = default_aflw_processor(aflw);
	if (   aflw.flow_state.val != def.flow_state.val
	       || is_not_signals_equal(aflw.signal, def.signal)
		) {
		TEST_FAILURE;
	}

	// signal ONLY
	aflw = make_succeeded_aflw_signal(signal);
	if (   !is_flow_succeeded(aflw.flow_state)
	    || !is_signals_equal(aflw.signal, signal)
	    || !has_aflw_signal(aflw)
	    ||  has_not_aflw_signal(aflw)
	    || !is_aflw_succeeded(aflw)
	    ||  is_not_aflw_succeeded(aflw)
	) {
		TEST_FAILURE;
	}
	def = default_aflw_processor(aflw);
	if (   aflw.flow_state.val != def.flow_state.val
	       || is_not_signals_equal(aflw.signal, def.signal)
		) {
		TEST_FAILURE;
	}
	aflw = make_failed_aflw_signal(signal);
	if (   !is_flow_failed(aflw.flow_state)
	    || !is_signals_equal(aflw.signal, signal)
	    || !has_aflw_signal(aflw)
	    ||  has_not_aflw_signal(aflw)
	    || !is_aflw_failed(aflw)
	    || !is_not_aflw_succeeded(aflw)
	) {
		TEST_FAILURE;
	}
	def = default_aflw_processor(aflw);
	if (   aflw.flow_state.val != def.flow_state.val
	       || is_not_signals_equal(aflw.signal, def.signal)
		) {
		TEST_FAILURE;
	}
	aflw = make_crashed_aflw_signal(signal);
	if (   !is_flow_crashed(aflw.flow_state)
	    || !is_signals_equal(aflw.signal, signal)
	    || !has_aflw_signal(aflw)
	    ||  has_not_aflw_signal(aflw)
	    || !is_aflw_crashed(aflw)
	    || !is_not_aflw_succeeded(aflw)
	) {
		TEST_FAILURE;
	}
	def = default_aflw_processor(aflw);
	if (   aflw.flow_state.val != def.flow_state.val
	       || is_not_signals_equal(aflw.signal, def.signal)
		) {
		TEST_FAILURE;
	}

	// FlwSt ONLY
	aflw = make_aflw(FLW_ST.succeeded);
	if (   !is_flow_succeeded(aflw.flow_state)
	    || !is_signals_equal(aflw.signal, SIGNAL_CODE.empty)
	    ||  has_aflw_signal(aflw)
	    || !has_not_aflw_signal(aflw)
	    || !is_aflw_succeeded(aflw)
	    ||  is_not_aflw_succeeded(aflw)
	) {
		TEST_FAILURE;
	}
	def = default_aflw_processor(aflw);
	if (   aflw.flow_state.val != def.flow_state.val
	       || is_not_signals_equal(aflw.signal, def.signal)
		) {
		TEST_FAILURE;
	}
	aflw = make_aflw(FLW_ST.failed);
	if (   !is_flow_failed(aflw.flow_state)
	    || !is_signals_equal(aflw.signal, SIGNAL_CODE.empty)
	    ||  has_aflw_signal(aflw)
	    || !has_not_aflw_signal(aflw)
	    || !is_aflw_failed(aflw)
	    || !is_not_aflw_succeeded(aflw)
	) {
		TEST_FAILURE;
	}
	def = default_aflw_processor(aflw);
	if (   aflw.flow_state.val != def.flow_state.val
	       || is_not_signals_equal(aflw.signal, def.signal)
		) {
		TEST_FAILURE;
	}
	aflw = make_aflw(FLW_ST.crashed);
	if (   !is_flow_crashed(aflw.flow_state)
	    || !is_signals_equal(aflw.signal, SIGNAL_CODE.empty)
	    ||  has_aflw_signal(aflw)
	    || !has_not_aflw_signal(aflw)
	    || !is_aflw_crashed(aflw)
	    || !is_not_aflw_succeeded(aflw)
	) {
		TEST_FAILURE;
	}
	def = default_aflw_processor(aflw);
	if (   aflw.flow_state.val != def.flow_state.val
	       || is_not_signals_equal(aflw.signal, def.signal)
		) {
		TEST_FAILURE;
	}

	// Auto FlwST
	aflw = make_succeeded_aflw();
	if (   !is_flow_succeeded(aflw.flow_state)
	    || !is_signals_equal(aflw.signal, SIGNAL_CODE.empty)
	    ||  has_aflw_signal(aflw)
	    || !has_not_aflw_signal(aflw)
	    || !is_aflw_succeeded(aflw)
	    ||  is_not_aflw_succeeded(aflw)
	) {
		TEST_FAILURE;
	}
	def = default_aflw_processor(aflw);
	if (   aflw.flow_state.val != def.flow_state.val
	       || is_not_signals_equal(aflw.signal, def.signal)
		) {
		TEST_FAILURE;
	}
	aflw = make_failed_aflw();
	if (   !is_flow_failed(aflw.flow_state)
	    || !is_signals_equal(aflw.signal, SIGNAL_CODE.empty)
	    ||  has_aflw_signal(aflw)
	    || !has_not_aflw_signal(aflw)
	    || !is_aflw_failed(aflw)
	    || !is_not_aflw_succeeded(aflw)
	) {
		TEST_FAILURE;
	}
	def = default_aflw_processor(aflw);
	if (   aflw.flow_state.val != def.flow_state.val
	       || is_not_signals_equal(aflw.signal, def.signal)
		) {
		TEST_FAILURE;
	}
	aflw = make_crashed_aflw();
	if (   !is_flow_crashed(aflw.flow_state)
	    || !is_signals_equal(aflw.signal, SIGNAL_CODE.empty)
	    ||  has_aflw_signal(aflw)
	    || !has_not_aflw_signal(aflw)
	    || !is_aflw_crashed(aflw)
	    || !is_not_aflw_succeeded(aflw)
	) {
		TEST_FAILURE;
	}
	def = default_aflw_processor(aflw);
	if (   aflw.flow_state.val != def.flow_state.val
	       || is_not_signals_equal(aflw.signal, def.signal)
		) {
		TEST_FAILURE;
	}
TEST_FINISHED

Aflw finish_crashed()
{
	AFLOW_FINISH_CRASHED;
}
Aflw finish_crashed_with(unsigned int n)
{
	signal_code_t sig = make_signal_code1(n);
	AFLOW_FINISH_CRASHED_WITH(sig);
}
Aflw finish_failed()
{
	AFLOW_FINISH_FAILED;
}
Aflw finish_failed_with(unsigned int n)
{
	signal_code_t sig = make_signal_code1(n);
	AFLOW_FINISH_FAILED_WITH(sig);
}
Aflw finish_succeeded()
{
	AFLOW_FINISH_SUCCEEDED;
}
Aflw finish_succeeded_with(unsigned int n)
{
	signal_code_t sig = make_signal_code1(n);
	AFLOW_FINISH_SUCCEEDED_WITH(sig);
}
NEW_TEST(test_finish_macroses)
	Aflw aflw;

	// Aflow without signal
	aflw = finish_crashed();
	if (   !is_aflw_crashed(aflw)
	    ||  has_aflw_signal(aflw)
	) {
		TEST_FAILURE;
	}
	aflw = finish_failed();
	if (   !is_aflw_failed(aflw)
	    ||  has_aflw_signal(aflw)
	) {
		TEST_FAILURE;
	}
	aflw = finish_succeeded();
	if (   is_not_aflw_succeeded(aflw)
	    || has_aflw_signal(aflw)
	) {
		TEST_FAILURE;
	}

	// Flow with signal
	aflw = finish_crashed_with(1);
	if (   !is_aflw_crashed(aflw)
	    || !has_aflw_signal(aflw)
	    ||  is_not_signals_equal(aflw.signal, make_signal_code1(1))
	) {
		TEST_FAILURE;
	}
	aflw = finish_failed_with(12);
	if (   !is_aflw_failed(aflw)
	    || !has_aflw_signal(aflw)
	    ||  is_not_signals_equal(aflw.signal, make_signal_code1(12))
	) {
		TEST_FAILURE;
	}
	aflw = finish_succeeded_with(123);
	if (    is_not_aflw_succeeded(aflw)
	    || !has_aflw_signal(aflw)
	    ||  is_not_signals_equal(aflw.signal, make_signal_code1(123))
	) {
		TEST_FAILURE;
	}
TEST_FINISHED

Aflw pass_func()
{
	INIT_ADVANCED_FLOW_CONTROL;
	FLOW finish_succeeded() PASS;
	AFLOW_FINISH_SUCCEEDED;
}
Aflw not_pass_func()
{
	INIT_ADVANCED_FLOW_CONTROL;
	FLOW finish_failed() PASS;
	AFLOW_FINISH_SUCCEEDED;
}
Aflw if_failed_stmnt_func()
{
	INIT_ADVANCED_FLOW_CONTROL;
	FLOW finish_failed();
	IF_AFLOW_FAILED
		AFLOW_FINISH_SUCCEEDED;
	END_IF_AND_PASS;
}
Aflw if_crashed_stmnt_func()
{
	INIT_ADVANCED_FLOW_CONTROL;
	FLOW finish_crashed();
	IF_AFLOW_CRASHED
		AFLOW_FINISH_SUCCEEDED;
	END_IF_AND_PASS;
}
Aflw if_failed_else_crashed_stmnt_func()
{
	INIT_ADVANCED_FLOW_CONTROL;
	FLOW finish_crashed();
	IF_AFLOW_FAILED
		AFLOW_FINISH_FAILED;
	ELSE_IF_AFLOW_CRASHED
		AFLOW_FINISH_SUCCEEDED;
	END_IF_AND_PASS;
}
Aflw super_pass_func()
{
	INIT_ADVANCED_FLOW_CONTROL;
	FLOW finish_succeeded()
	IF_AFLOW_FAILED
		AFLOW_FINISH_FAILED;
	ELSE_IF_AFLOW_CRASHED
		AFLOW_FINISH_FAILED;
	END_IF_AND_PASS;
}
NEW_TEST(test_pass_and_if_stmnt)
	Aflw aflw;
	aflw = pass_func();
	if (is_not_aflw_succeeded(aflw))
	{
		TEST_FAILURE;
	}
	aflw = not_pass_func();
	if (!is_aflw_failed(aflw))
	{
		TEST_FAILURE;
	}
	aflw = if_failed_stmnt_func();
	if (is_not_aflw_succeeded(aflw))
	{
		TEST_FAILURE;
	}
	aflw = if_crashed_stmnt_func();
	if (is_not_aflw_succeeded(aflw))
	{
		TEST_FAILURE;
	}
	aflw = if_failed_else_crashed_stmnt_func();
	if (is_not_aflw_succeeded(aflw))
	{
		TEST_FAILURE;
	}
	aflw = super_pass_func();
	if (is_not_aflw_succeeded(aflw))
	{
		TEST_FAILURE;
	}
TEST_FINISHED

Aflw switch_signal()
{
	INIT_ADVANCED_FLOW_CONTROL;
	FLOW finish_failed_with(13);
	signal_code_t s0,s1,sm1,s13;
	s0 = make_signal_code1(0);
	s1 = make_signal_code1(1);
	sm1 = make_signal_code1((unsigned int) -1);
	s13 = make_signal_code1(13);
	SWITCH_SIGNAL
		CASE_SIGNAL(s0)
			AFLOW_FINISH_FAILED;
		CASE_SIGNAL(s1)
			AFLOW_FINISH_FAILED;
		CASE_SIGNAL(sm1)
			AFLOW_FINISH_FAILED;
		CASE_SIGNAL(s13)
			AFLOW_FINISH_SUCCEEDED;
	END_SWITCH_SIGNAL;
}
NEW_TEST(test_switch_signal)
	Aflw aflw;
	aflw = switch_signal();
	if (is_not_aflw_succeeded(aflw))
	{
		TEST_FAILURE;
	}
TEST_FINISHED

Aflw always_succeeded(Aflw aflw)
{
	AFLOW_FINISH_SUCCEEDED;
}
Aflw not_today()
{
	INIT_ADVANCED_FLOW_CONTROL;
	FLOW finish_failed() PASS_WITH(always_succeeded);
	AFLOW_FINISH_FAILED;
}
bool gt100_and_odd(signal_code_t sig)
{
	return
		   sig.active_codes_number == 1
		&& sig.code1 > 100
		&& sig.code1 % 2 == 1;
}
Aflw special_case()
{
	INIT_ADVANCED_FLOW_CONTROL;
	FLOW finish_crashed_with(113);
	SWITCH_SIGNAL
		CASE_SIGNAL_WITH(gt100_and_odd)
			AFLOW_FINISH_SUCCEEDED;
	END_SWITCH_SIGNAL
	PASS;
}
Aflw not_special_case()
{
	INIT_ADVANCED_FLOW_CONTROL;
	FLOW finish_succeeded_with(114);
	SWITCH_SIGNAL
	CASE_SIGNAL_WITH(gt100_and_odd)
		AFLOW_FINISH_FAILED;
	END_SWITCH_SIGNAL
	PASS;
}
NEW_TEST(test_special_macroses)
	Aflw aflw;
	aflw = not_today();
	if (is_not_aflw_succeeded(aflw))
	{
		TEST_FAILURE;
	}
	aflw = special_case();
	if (is_not_aflw_succeeded(aflw))
	{
		TEST_FAILURE;
	}
	aflw = not_special_case();
	if (is_not_aflw_succeeded(aflw))
	{
		TEST_FAILURE;
	}
TEST_FINISHED

INIT_TESTS_CHECKS
	CHECK_TEST(TEST_CHECK_UP, test_signal_code_empty);
	CHECK_TEST(TEST_CHECK_UP, test_make_signal_codes);
	CHECK_TEST(TEST_CHECK_UP, test_signals_internal_compairing);
	CHECK_TEST(TEST_CHECK_UP, test_signals_compairing);
	CHECK_TEST(TEST_CHECK_UP, test_make_and_def_processor_aflw);
	CHECK_TEST(TEST_CHECK_UP, test_finish_macroses);
	CHECK_TEST(TEST_CHECK_UP, test_pass_and_if_stmnt);
	CHECK_TEST(TEST_CHECK_UP, test_switch_signal);
	CHECK_TEST(TEST_CHECK_UP, test_special_macroses);
DONE_TESTS_CHECKS
