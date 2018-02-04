#include "to-stream-serializer.h"

size_t inc_plus32(size_t size)
{
	return size + 32;
}

size_t inc_plus4k(size_t size)
{
	return size + 4096;
}

size_t inc_plus16k(size_t size)
{
	return size + 16384;
}

size_t inc_x2_plus1(size_t size)
{
	return 2 * size + 1;
}
