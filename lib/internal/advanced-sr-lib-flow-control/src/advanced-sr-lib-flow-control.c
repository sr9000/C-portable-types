
#include "advanced-sr-lib-flow-control.h"
#include "internal/advanced-sr-lib-flow-control.h"


signal_code_t
make_signal_code1(
	unsigned int code1
) {
	signal_code_t signal;
	signal.active_codes_number = 1;
	signal.code1 = code1;
	signal.code2 = 0;
	signal.code3 = 0;
	signal.code4 = 0;
	return signal;
}

signal_code_t
make_signal_code2(
	  unsigned int code1
	, unsigned int code2
) {
	signal_code_t signal;
	signal.active_codes_number = 2;
	signal.code1 = code1;
	signal.code2 = code2;
	signal.code3 = 0;
	signal.code4 = 0;
	return signal;
}

signal_code_t
make_signal_code3(
	  unsigned int code1
	, unsigned int code2
	, unsigned int code3
) {
	signal_code_t signal;
	signal.active_codes_number = 3;
	signal.code1 = code1;
	signal.code2 = code2;
	signal.code3 = code3;
	signal.code4 = 0;
	return signal;
}

signal_code_t
make_signal_code4(
	  unsigned int code1
	, unsigned int code2
	, unsigned int code3
	, unsigned int code4
) {
	signal_code_t signal;
	signal.active_codes_number = 4;
	signal.code1 = code1;
	signal.code2 = code2;
	signal.code3 = code3;
	signal.code4 = code4;
	return signal;
}

bool
is_siganls_equal(
	  signal_code_t signal1
	, signal_code_t signal2
) {
	if (signal1.active_codes_number != signal2.active_codes_number)
	{
		return false;
	}
	switch(signal1.active_codes_number)
	{
		case  0: return true;
		case  1: return is_siganls_code1_equal(signal1, signal2);
		case  2: return is_siganls_code2_equal(signal1, signal2);
		case  3: return is_siganls_code3_equal(signal1, signal2);
		case  4: return is_siganls_code4_equal(signal1, signal2);
		default: return false;
	}
}

bool
is_siganls_code1_equal(
	  signal_code_t signal1
	, signal_code_t signal2
) {
	return signal1.code1 == signal2.code1;
}

bool
is_siganls_code2_equal(
	  signal_code_t signal1
	, signal_code_t signal2
) {
	return    signal1.code1 == signal2.code1
	       && signal1.code2 == signal2.code2;
}

bool
is_siganls_code3_equal(
	  signal_code_t signal1
	, signal_code_t signal2
) {
	return    signal1.code1 == signal2.code1
	       && signal1.code2 == signal2.code2
	       && signal1.code3 == signal2.code3;
}

bool
is_siganls_code4_equal(
	  signal_code_t signal1
	, signal_code_t signal2
) {
	return    signal1.code1 == signal2.code1
	       && signal1.code2 == signal2.code2
	       && signal1.code3 == signal2.code3
	       && signal1.code4 == signal2.code4;
}

bool
is_not_siganls_equal(
	  signal_code_t signal1
	, signal_code_t signal2
) {
	return !is_siganls_equal(signal1, signal2);
}

Aflw
make_aflw_signal(
	  FlwSt         flow_state
	, signal_code_t signal
) {
	Aflw flw;
	flw.flow_state = flow_state;
	flw.signal     = signal;
	return flw;
}

Aflw
make_succeeded_aflw_signal(
	signal_code_t signal
) {
	Aflw flw;
	flw.flow_state = FLW_ST.succeeded;
	flw.signal     = signal;
	return flw;
}

Aflw
make_failed_aflw_signal(
	signal_code_t signal
) {
	Aflw flw;
	flw.flow_state = FLW_ST.failed;
	flw.signal     = signal;
	return flw;
}

Aflw
make_crashed_aflw_signal(
	signal_code_t signal
) {
	Aflw flw;
	flw.flow_state = FLW_ST.crashed;
	flw.signal     = signal;
	return flw;
}

Aflw
make_aflw(
	FlwSt flow_state
) {
	Aflw flw;
	flw.flow_state = flow_state;
	flw.signal     = SIGNAL_CODE.empty;
	return flw;
}

Aflw
make_succeeded_aflw()
{
	Aflw flw;
	flw.flow_state = FLW_ST.succeeded;
	flw.signal     = SIGNAL_CODE.empty;
	return flw;
}

Aflw
make_failed_aflw()
{
	Aflw flw;
	flw.flow_state = FLW_ST.failed;
	flw.signal     = SIGNAL_CODE.empty;
	return flw;
}

Aflw
make_crashed_aflw()
{
	Aflw flw;
	flw.flow_state = FLW_ST.crashed;
	flw.signal     = SIGNAL_CODE.empty;
	return flw;
}

bool
has_aflw_signal(
	Aflw aflw
) {
	return aflw.signal.active_codes_number > 0;
}

bool
has_not_aflw_signal(
	Aflw aflw
) {
	return aflw.signal.active_codes_number == 0;
}

bool
is_aflw_succeeded(
	Aflw aflw
) {
	return is_flow_succeeded(aflw.flow_state);
}

bool
is_not_aflw_succeeded(
	Aflw aflw
) {
	return is_flow_not_succeeded(aflw.flow_state);
}

bool
is_aflw_failed(
	Aflw aflw
) {
	return is_flow_failed(aflw.flow_state);
}

bool
is_aflw_crashed(
	Aflw aflw
) {
	return is_flow_crashed(aflw.flow_state);
}
