
/*!
 * @file    advanced-sr-lib-flow-control.h
 * @author  Rogonov Stepan Alekseevich
 * @brief   Library with useful macroses to contrrolling flow execution.
 * @details More control over flow execution with \em signal \em codes (
 * \ref signal_code_t). Library based on sr-lib-flow-control library.
 */

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

/*!
 * @typedef signal_code_t
 * @brief   Type to store signals.
 * @details Signals should be used to more rich interaction between methods.
 * Signals can indicate different causes of failure or status of successfully
 * executed methods. Use methods \ref make_signal_code1 \ref make_signal_code2
 * \ref make_signal_code3 or \ref make_signal_code4 to create correct signal
 * values.
 */
typedef struct
{
	unsigned char active_codes_number;
	unsigned int code1, code2, code3, code4;
} signal_code_t;

const static struct
{
	//! Empty signal. It indicates that no any signal presented. Like \c NULL
	//! value for pointers.
	signal_code_t empty;
}
/*!
 * @var     SIGNAL_CODE
 * @brief   Stores default signal codes.
 * @hideinitializer
 * @details Usually that codes represent special values, which are used by
 * advanced flow control macroses for internal purposes.
 */
SIGNAL_CODE = {
	.empty = {
		  .active_codes_number = 0
		, .code1 = 0
		, .code2 = 0
		, .code3 = 0
		, .code4 = 0
	}
};

/*!
 * @brief Create signal value \ref signal_code_t from one code value.
 * @param [in] code1  Code value
 * @return Corectly initialized signal value \ref signal_code_t
 */
signal_code_t
make_signal_code1(
	unsigned int code1
);

/*!
 * @brief Create signal value \ref signal_code_t from one code value.
 * @param [in] code1  First part of code value
 * @param [in] code2  Second part of code value
 * @details Creates signal values, using twice more code values than \ref
 * make_signal_code1.
 * @return Corectly initialized signal value \ref signal_code_t
 */
signal_code_t
make_signal_code2(
	  unsigned int code1
	, unsigned int code2
);

/*!
 * @brief Create signal value \ref signal_code_t from one code value.
 * @param [in] code1  First part of code value
 * @param [in] code2  Second part of code value
 * @param [in] code3  Third part of code value
 * @details Creates signal values, using even more code values than \ref
 * make_signal_code2.
 * @return Corectly initialized signal value \ref signal_code_t
 */
signal_code_t
make_signal_code3(
	  unsigned int code1
	, unsigned int code2
	, unsigned int code3
);

/*!
 * @brief Create signal value \ref signal_code_t from one code value.
 * @param [in] code1  First part of code value
 * @param [in] code2  Second part of code value
 * @param [in] code3  Third part of code value
 * @param [in] code4  Fourth part of code value
 * @details Creates signal values, using all four code values. Signal value,
 * that are created by \ref make_signal_code4 can represent
 * <b>18,446 744 073,709 551 616</b> different values.
 * @warning Each \code value of type \c unsigned \c int according to C11
 * standard can represent values from range 0..65535
 * @return Corectly initialized signal value \ref signal_code_t
 */
signal_code_t
make_signal_code4(
	  unsigned int code1
	, unsigned int code2
	, unsigned int code3
	, unsigned int code4
);

/*!
 * @brief Compare two signal value \ref signal_code_t.
 * @param [in] signal1  First signal value
 * @param [in] signal2  Second signal value
 * @details Check that \p signal1 and \p signal2 are the same.
 * @return \c true if signal aere the same, \c false else
 */
bool
is_siganls_equal(
	  signal_code_t signal1
	, signal_code_t signal2
);

/*!
 * @brief Inverse to \ref is_siganls_equal.
 * @param [in] signal1  First signal value
 * @param [in] signal2  Second signal value
 * @details Check that \p signal1 and \p signal2 are <b>not</b> the same.
 * @return \c false if signal are the same, \c true else
 */
bool
is_not_siganls_equal(
	  signal_code_t signal1
	, signal_code_t signal2
);

/*!
 * @typedef Aflw
 * @brief   Advanced flow state.
 * @details Contains as flow state as signal code for rich method interaction.
 */
typedef struct struct_aflw
{
	FlwSt          flow_state; //<! State: \c succeeded, \c failed or \c crashed
	signal_code_t  signal;     //<! Signal, Meaning is determined by developer
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

Aflw
default_aflw_processor(
	Aflw aflw
);

#define AFLOW_VAR fe75a94dccc1a2fc78a0bb224e6618f4

#define INIT_ADVANCED_FLOW_CONTROL \
	Aflw AFLOW_VAR;

#define FLOW \
	AFLOW_VAR =

#define PASS \
	; \
	if (is_not_aflw_succeeded(AFLOW_VAR)) \
	{ \
		return default_aflw_processor(AFLOW_VAR); \
	} ;

#define PASS_WITH(aflw_processor_func_name) \
	; \
	if (is_not_aflw_succeeded(AFLOW_VAR)) \
	{ \
		return (aflw_processor_func_name)(AFLOW_VAR); \
	} ;

#define SWITCH_SIGNAL \
	; \
	if (is_siganls_equal((AFLOW_VAR).signal, SIGNAL_CODE.empty)) {

#define CASE_SIGNAL(case_signal) \
	} else if(is_siganls_equal((AFLOW_VAR).signal, (case_signal))) \
	{

#define CASE_SIGNAL_WITH(case_function_takes_signal_code_t_return_bool) \
	} else if( \
		(case_function_takes_signal_code_t_return_bool)( \
			(AFLOW_VAR).signal \
		) \
	) {

#define END_SWITCH_SIGNAL \
	} ;

#define AFLOW_FINISH_WITH(aflw) \
	return (aflw);

#define AFLOW_FINISH_SUCCEEDED \
	return make_succeeded_aflw();

#define AFLOW_FINISH_SUCCEEDED_WITH(signal) \
	return make_succeeded_aflw_signal(signal);

#define AFLOW_FINISH_FAILED \
	return make_failed_aflw();

#define AFLOW_FINISH_FAILED_WITH(signal) \
	return make_failed_aflw_signal(signal);

#define AFLOW_FINISH_CRASHED \
	return make_crashed_aflw();

#define AFLOW_FINISH_CRASHED_WITH(signal) \
	return make_crashed_aflw_signal(signal);

#endif // ADVANCED_SR_LIB_FLOW_CONTROL
