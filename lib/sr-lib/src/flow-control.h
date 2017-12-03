#ifndef SRLIB_FLOW_CONTROL_HEADER
#define SRLIB_FLOW_CONTROL_HEADER

// libc
#include <stdbool.h>

// check we have "bool" "true" and "false" macroses
#if __bool_true_false_are_defined != 1
#error Can not be compiled cause <stdbool.h> did not \
implement "bool", "true" and "false" macroses in some reason. \
Please, check your platform/architecture/compilator and official vendors \
information to find that reason.
#endif

// defines type, that used
// to store execution flow states
struct struct_flow_state;
typedef struct struct_flow_state
	                FlwSt
	, *            pFlwSt
	, * restrict  rpFlwSt;
typedef const struct struct_flow_state
	               cFlwSt
	, *           pcFlwSt
	, * restrict rpcFlwSt;
struct struct_flow_state
{
	int val;
};

// Defines values, that used
// in execution flow control
const static struct
{
	cFlwSt
		  succeeded // execution flow is OK
		, failed    // execution flow detects logic error
		            //   and falls into unimplemented case
		, crashed   // execution flow detects error, but
		            //   side effects can not be undone
		            //   memory leaks are very possible!
		;
}
FLW_ST = {
	  .succeeded  = { .val =  1 }
	, .failed     = { .val =  0 }
	, .crashed    = { .val = -1 }
};

#ifndef BUILD_SRLIB
	extern
#endif
bool
is_flow_succeeded( // O(1)
	cFlwSt register flw_st // state which need to be checked
);

#ifndef BUILD_SRLIB
	extern
#endif
bool
is_flow_not_succeeded( // O(1)
	cFlwSt register flw_st // state which need to be checked
);

#ifndef BUILD_SRLIB
	extern
#endif
bool
is_flow_failed( // O(1)
	cFlwSt register flw_st // state which need to be checked
);

#ifndef BUILD_SRLIB
	extern
#endif
bool
is_flow_crashed( // O(1)
	cFlwSt register flw_st // state which need to be checked
);

#endif // SRLIB_FLOW_CONTROL_HEADER
