#include <stdio.h>

#include "to-stream-serializer.h"

int main()
{
	stream_ptr_t stream;
	mem_mngr_t mngr = DEF_MEM_MNGR;
	printf("%p", mngr.pincrease);
	return 0;
}
