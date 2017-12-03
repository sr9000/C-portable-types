
// libc
#include <stdio.h>
#include <stdlib.h>

// srlib
#include "flow_control.h"

FlwSt     fail() { return FLW_ST.failed;     }
FlwSt    crash() { return FLW_ST.crashed;    }
FlwSt  success() { return FLW_ST.succeeded;  }

int main()
{
	FlwSt st;

	//Test fail() function.
	st = fail();
	if (!(    st.val == 0
	      && !is_flow_succeeded(st)
	      &&  is_flow_not_succeeded(st)
	      &&  is_flow_failed(st)
	      && !is_flow_crashed(st)))
	{
		printf("ERROR: Test failed on \"fail()\" function.\n");
		return EXIT_FAILURE;
	}

	//Test success
	st = success();
	if (!(    st.val == 1
	      &&  is_flow_succeeded(st)
	      && !is_flow_not_succeeded(st)
	      && !is_flow_failed(st)
	      && !is_flow_crashed(st)))
	{
		printf("ERROR: Test failed on \"success()\" function.\n");
		return EXIT_FAILURE;
	}

	//Test crash
	st = crash();
	if (!(    st.val == -1
	      && !is_flow_succeeded(st)
	      &&  is_flow_not_succeeded(st)
	      && !is_flow_failed(st)
	      &&  is_flow_crashed(st)))
	{
		printf("ERROR: Test failed on \"crash()\" function.\n");
		return EXIT_FAILURE;
	}

	//Test passed
	printf("INFO: Tests passed successfully.\n");
	return EXIT_SUCCESS;
}
