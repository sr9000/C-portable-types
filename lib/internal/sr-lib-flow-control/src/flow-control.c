#include "flow-control.h"

bool
is_flow_succeeded(
	cFlwSt register flw_st
) {
	return (flw_st.val == FLW_ST.succeeded.val);
}

bool
is_flow_not_succeeded(
	cFlwSt register flw_st
) {
	return (flw_st.val != FLW_ST.succeeded.val);
}

bool
is_flow_failed(
	cFlwSt register flw_st
) {
	return (flw_st.val == FLW_ST.failed.val);
}

bool
is_flow_crashed(
	cFlwSt register flw_st
) {
	return (flw_st.val == FLW_ST.crashed.val);
}
