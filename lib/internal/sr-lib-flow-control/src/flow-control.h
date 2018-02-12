
/**
 * @file flow-control.h
 * @author Rogonov Stepan Alekseevich
 * @brief File containing definitions of execution flow control functions.
 * @details Defines structures and types, that should be return from functions.
 * Also there are several constants, that indicated status of flow. Finally
 * there are functions, that provides way to check status of execution flow.
 */

#ifndef SRLIB_FLOW_CONTROL_HEADER
#define SRLIB_FLOW_CONTROL_HEADER

#include <stdbool.h>
#include <stdint.h>

// check existing "bool" "true" and "false" macroses
#if __bool_true_false_are_defined != 1
#error "Can not be compiled cause <stdbool.h> did not "\
       "implement \"bool\", \"true\" and \"false\" macroses in some reason. "\
       "Please, check your platform/architecture/compilator and official "\
       "vendors information to find the cause."
#endif


struct struct_flow_state;

typedef
struct struct_flow_state
	                FlwSt //! Alias for \ref struct_flow_state.
	, *            pFlwSt //! Pointer onto \ref struct_flow_state.
	, * restrict  rpFlwSt //! Restrict pointer onto \ref struct_flow_state.
	;


typedef const
struct struct_flow_state
	               cFlwSt //! Constant variant of \ref FlwSt.
	, *           pcFlwSt //! Constant variant of \ref pFlwSt.
	, * restrict rpcFlwSt //! Constant variant of \ref rpFlwSt.
	;

/**
 * @brief Defines type, that used to store execution flow state.
 */
struct struct_flow_state
{
#ifdef INT_FAST8_MAX
	int_fast8_t // take fastest integer type
#else
	int // or simple int type, if fastest type is not defined on that platform
#endif
	val; //!< Flow state.
};


const static struct
{
	cFlwSt
		  succeeded //! Constant field of \ref FLW_ST, that
		            //!< indicates successful execution flow finishing.
		            //!< @code{.c} FlwSt state = FLW_ST.succeeded; @endcode
		            //!<
		, failed    //! Constant field of \ref FLW_ST, that
		            //!< indicates execution flow falling into an unimplemented
		            //!< case because a logic error was detected.
		            //!< @code{.c} FlwSt state = FLW_ST.failed; @endcode
		            //!<
		, crashed   //! Constant field of \ref FLW_ST, that indicates
		            //!< an error with irreversible side effects
		            //!< and memory leaks possibility.
		            //!< @code{.c} FlwSt state = FLW_ST.crashed; @endcode
		            //!<
		;
}
/**
 * @var FLW_ST
 * @brief Defines constant values, that used in execution flow control
 * @hideinitializer
 * @code{.c}
 * int n;
 * scanf("%d", &n);
 * if (n <= 0)
 * 	return FLW_ST.failed;
 * void *mem = malloc(n);
 * if (mem == NULL)
 * 	return FLW_ST.crashed;
 * free(mem);
 * return FLW_ST.succeeded;
 * @endcode
 */
FLW_ST = {
	  .succeeded  = { .val =  1 }
	, .failed     = { .val =  0 }
	, .crashed    = { .val = -1 }
};

/**
 * @brief returns, only if flow finished successfully.
 * @param flw_st [in] flow execution result.
 * @return <b>true</b>, if flow finished successfully.
 * <b>false</b> in all other cases.
 */
bool
is_flow_succeeded(
	cFlwSt register flw_st
);

/**
 * @brief returns, if any errors occurred
 * @param flw_st [in] flow execution result.
 * @return inverse result of \ref is_flow_succeeded.
 * <b>false</b>, if flow finished successfully.
 * <b>true</b> in all other cases.
 */
bool
is_flow_not_succeeded(
	cFlwSt register flw_st
);

/**
 * @brief returns, only if logic error detected.
 * @param flw_st [in] flow execution result.
 * @return <b>true</b>, if logic error detected.
 * <b>false</b> in all other cases.
 */
bool
is_flow_failed(
	cFlwSt register flw_st
);

/**
 * @brief returns, only if error with irreversible side effects detected.
 * @param flw_st [in] flow execution result.
 * @return <b>true</b>, if error with irreversible side effects detected.
 * <b>false</b> in all other cases.
 */
bool
is_flow_crashed(
	cFlwSt register flw_st
);

#endif // SRLIB_FLOW_CONTROL_HEADER
