#include <stdio.h>
#include <stdlib.h>

#include "to-stream-serializer.h"

int main()
{
	stream_ptr_t stream;
	if (is_flow_not_succeeded(new_stream(&stream, DEF_MEM_MNGR, 100, 10)))
	{
		printf("%s:%d \"%s\"\n", __FILE__, __LINE__, "new_stream");
		exit(EXIT_FAILURE);
	}
	if (is_flow_not_succeeded(stream_int32_t(stream, 17)))
	{
		printf("%s:%d \"%s\"\n", __FILE__, __LINE__, "stream_int32_t");
		exit(EXIT_FAILURE);
	}
	if (is_flow_not_succeeded(stream_int32_t(stream, 33)))
	{
		printf("%s:%d \"%s\"\n", __FILE__, __LINE__, "stream_int32_t");
		exit(EXIT_FAILURE);
	}
	if (is_flow_not_succeeded(stream_double(stream, 17.7)))
	{
		printf("%s:%d \"%s\"\n", __FILE__, __LINE__, "stream_double");
		exit(EXIT_FAILURE);
	}
	char overstring[] =
		"string that overflow maximal capacity of current stream"
		"twice string that overflow maximal capacity of current stream";
	FlwSt st = stream_blob(stream, overstring, sizeof(overstring));
	if (is_flow_failed(st))
	{
		printf("%s:%d \"%s\"\n", __FILE__, __LINE__, "stream_blob");
		exit(EXIT_FAILURE);
	}
	if (1)
	{
		printf("%s:%d \"%s\"\n", __FILE__, __LINE__, "extravaganza!!!");
		exit(EXIT_FAILURE);
	}
	return EXIT_SUCCESS;
}
