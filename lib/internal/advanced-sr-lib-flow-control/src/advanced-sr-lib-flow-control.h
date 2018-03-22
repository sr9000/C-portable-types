
#ifndef ADVANCED_SR_LIB_FLOW_CONTROL
#define ADVANCED_SR_LIB_FLOW_CONTROL

#include <stdbool.h>

#include "flow-control.h"

// check existing "bool" "true" and "false" macroses
#if __bool_true_false_are_defined != 1
#error "Can not be compiled cause <stdbool.h> did not "\
       "implement \"bool\", \"true\" and \"false\" macroses in some reason. "\
       "Please, check your platform/architecture/compilator and official "\
       "vendors information to find the cause."
#endif

typedef struct
{
	unsigned char active_codes_number;
	unsigned int code1, code2, code3, code4;
} signal_code_t;

const static struct
{
	signal_code_t empty;
}
SIGNAL_CODE = {
	.empty = {
		  .active_codes_number = 0
		, .code1 = 0
		, .code2 = 0
		, .code3 = 0
		, .code4 = 0
	}
};

signal_code_t
make_signal_code1(
	unsigned int code1
);

signal_code_t
make_signal_code2(
	  unsigned int code1
	, unsigned int code2
);

signal_code_t
make_signal_code3(
	  unsigned int code1
	, unsigned int code2
	, unsigned int code3
);

signal_code_t
make_signal_code4(
	  unsigned int code1
	, unsigned int code2
	, unsigned int code3
	, unsigned int code4
);

bool
is_siganls_equal(
	  signal_code_t signal1
	, signal_code_t signal2
);

bool
is_not_siganls_equal(
	  signal_code_t signal1
	, signal_code_t signal2
);

typedef struct struct_aflw Aflw;

struct struct_aflw
{
	FlwSt          flow_state;
	signal_code_t  signal;
} Aflw;

Aflw
make_aflw_signal(
	  FlwSt         flow_state
	, signal_code_t signal
);

Aflw
make_succeeded_aflw_signal(
	signal_code_t signal
);

Aflw
make_failed_aflw_signal(
	signal_code_t signal
);

Aflw
make_crashed_aflw_signal(
	signal_code_t signal
);

Aflw
make_aflw(
	FlwSt flow_state
);

Aflw
make_succeeded_aflw();

Aflw
make_failed_aflw();

Aflw
make_crashed_aflw();

bool
has_aflw_signal(
	Aflw aflw
);

bool
has_not_aflw_signal(
	Aflw aflw
);

bool
is_aflw_succeeded(
	Aflw aflw
);

bool
is_not_aflw_succeeded(
	Aflw aflw
);

bool
is_aflw_failed(
	Aflw aflw
);

bool
is_aflw_crashed(
	Aflw aflw
);

#endif // ADVANCED_SR_LIB_FLOW_CONTROL
