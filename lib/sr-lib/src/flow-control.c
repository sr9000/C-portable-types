// libc
#include "flow-control.h"

bool
is_flow_succeeded(flw_st)
	cFlwSt register flw_st; // state which need to be checked
{ return (flw_st.val == FLW_ST.succeeded.val); }

bool
is_flow_not_succeeded(flw_st)
	cFlwSt register flw_st; // state which need to be checked
{ return (flw_st.val != FLW_ST.succeeded.val); }

bool
is_flow_failed(flw_st)
	cFlwSt register flw_st; // state which need to be checked
{ return (flw_st.val == FLW_ST.failed.val); }

bool
is_flow_crashed(flw_st)
	cFlwSt register flw_st; // state which need to be checked
{ return (flw_st.val == FLW_ST.crashed.val); }
