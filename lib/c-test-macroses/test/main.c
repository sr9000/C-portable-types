#include "atest.h"

NEW_ATEST(simple_test)
	if (1 != 1)
	{
		ATEST_FAILURE;
	}
ATEST_FINISHED

Aflw succeeded_function()
{
	INIT_ADVANCED_FLOW_CONTROL;
	AFLOW_FINISH_SUCCEEDED;
}

NEW_ATEST(multi_succeeded_test)
	FLOW succeeded_function() ATEST_PASS;
	FLOW succeeded_function() ATEST_PASS;
	FLOW succeeded_function() ATEST_PASS;
ATEST_FINISHED

NEW_ATEST(failure_test)
	ATEST_FAILURE;
ATEST_FINISHED

Aflw failure_function()
{
	INIT_ADVANCED_FLOW_CONTROL;
	AFLOW_FINISH_FAILED;
}

NEW_ATEST(second_failure_test)
	FLOW succeeded_function() ATEST_PASS;
	FLOW succeeded_function() ATEST_PASS;
	FLOW failure_function() ATEST_PASS;
ATEST_FINISHED

INIT_ATESTS_CHECKS
	CHECK_ATEST(ATEST_CHECK_UP, simple_test);
	CHECK_ATEST(ATEST_CHECK_UP, multi_succeeded_test);
	CHECK_ATEST(ATEST_CHECK_dn, failure_test);
	CHECK_ATEST(ATEST_CHECK_UP, second_failure_test);
DONE_ATESTS_CHECKS
