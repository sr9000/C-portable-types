#include <string.h>

#include "integer-serialization.h"
#include "test.h"

NEW_TEST(type_int8_t)
	enum {N = 10};
	int8_t src_val[N] =
		{   -1,    0,    1,  127
		, -128, -127,   32,  -32
		,  -82,  -98};
	unsigned char src_mem[N] =
		{ 0xff, 0x00, 0x01, 0x7f
		, 0x80, 0x81, 0x20, 0xe0
		, 0xae, 0x9e};
	unsigned char actual_mem[N];
	int8_t        actual_val[N];

	for (int i = 0; i < N; ++i)
	{
		void *pnext = serialize_int8_t(&(actual_mem[i]), src_val[i]);
		if (pnext != (actual_mem + i + 1))
			TEST_FAILURE;
	}
	if (memcmp(src_mem, actual_mem, N))
		TEST_FAILURE;

	for (int i = 0; i < N; ++i)
	{
		void *pnext = deserialize_int8_t(&(actual_val[i]), ((int8_t*)src_mem) + i);
		if (pnext != (((int8_t*)src_mem) + i + 1))
			TEST_FAILURE;
	}
	if (memcmp(src_val, actual_val, N))
		TEST_FAILURE;
TEST_FINISHED

NEW_TEST(type_uint8_t)
	enum {N = 10};
	uint8_t src_val[N] =
		{  255,    0,    1,  127
		,  128,  129,   32,  224
		,  174,  158};
	unsigned char src_mem[N] =
		{ 0xff, 0x00, 0x01, 0x7f
		, 0x80, 0x81, 0x20, 0xe0
		, 0xae, 0x9e};
	unsigned char actual_mem[N];
	int8_t        actual_val[N];

	for (int i = 0; i < N; ++i)
	{
		void *pnext = serialize_uint8_t(&(actual_mem[i]), src_val[i]);
		if (pnext != (actual_mem + i + 1))
			TEST_FAILURE;
	}
	if (memcmp(src_mem, actual_mem, N))
		TEST_FAILURE;

	for (int i = 0; i < N; ++i)
	{
		void *pnext = deserialize_uint8_t(&(actual_val[i]), ((int8_t*)src_mem) + i);
		if (pnext != (((int8_t*)src_mem) + i + 1))
			TEST_FAILURE;
	}
	if (memcmp(src_val, actual_val, N))
		TEST_FAILURE;
TEST_FINISHED

#ifdef INT16_SERIALIZATION_ALLOWED
NEW_TEST(type_int16_t)
	enum {N = 10};
	int16_t src_val[N] =
		{      -1
		,       0
		,       1
		,     127
		,    -128
		,    -127
		,      32
		,     -32
		,  -23122
		,     -98};
	unsigned char src_mem[2 * N] =
		{ 0xff, 0xff
		, 0x00, 0x00
		, 0x00, 0x01
		, 0x00, 0x7f
		, 0xff, 0x80
		, 0xff, 0x81
		, 0x00, 0x20
		, 0xff, 0xe0
		, 0xa5, 0xae
		, 0xff, 0x9e};
	unsigned char actual_mem[2 * N];
	int16_t       actual_val[N];

	for (int i = 0; i < N; ++i)
	{
		void *pnext = serialize_int16_t(&(actual_mem[2 * i]), src_val[i]);
		if (pnext != (actual_mem + 2 * (i + 1)))
			TEST_FAILURE;
	}
	if (memcmp(src_mem, actual_mem, N))
		TEST_FAILURE;

	for (int i = 0; i < N; ++i)
	{
		void *pnext = deserialize_int16_t(&(actual_val[i]), ((int16_t*)src_mem) + i);
		if (pnext != (((int16_t*)src_mem) + i + 1))
			TEST_FAILURE;
	}
	if (memcmp(src_val, actual_val, N))
		TEST_FAILURE;
TEST_FINISHED

NEW_TEST(type_uint16_t)
	enum {N = 10};
	uint16_t src_val[N] =
		{ 65535
		,     0
		,     1
		,   127
		, 65408
		, 65409
		,    32
		, 65504
		, 42414
		, 65438};
	unsigned char src_mem[2 * N] =
		{ 0xff, 0xff
		, 0x00, 0x00
		, 0x00, 0x01
		, 0x00, 0x7f
		, 0xff, 0x80
		, 0xff, 0x81
		, 0x00, 0x20
		, 0xff, 0xe0
		, 0xa5, 0xae
		, 0xff, 0x9e};
	unsigned char actual_mem[2 * N];
	uint16_t      actual_val[N];

	for (int i = 0; i < N; ++i)
	{
		void *pnext = serialize_uint16_t(&(actual_mem[2 * i]), src_val[i]);
		if (pnext != (actual_mem + 2 * (i + 1)))
			TEST_FAILURE;
	}
	if (memcmp(src_mem, actual_mem, N))
		TEST_FAILURE;

	for (int i = 0; i < N; ++i)
	{
		void *pnext = deserialize_uint16_t(&(actual_val[i]), ((uint16_t*)src_mem) + i);
		if (pnext != (((uint16_t*)src_mem) + i + 1))
			TEST_FAILURE;
	}
	if (memcmp(src_val, actual_val, N))
		TEST_FAILURE;
TEST_FINISHED
#endif // INT16_SERIALIZATION_ALLOWED

#ifdef INT32_SERIALIZATION_ALLOWED
NEW_TEST(type_int32_t)
	enum {N = 10};
	int32_t src_val[N] =
		{          -1L
		,           0L
		,           1L
		,         127L
		,        -128L
		,        -127L
		,          32L
		,         -32L
		,  -559045202L
		,         -98L};
	unsigned char src_mem[4 * N] =
		{ 0xff, 0xff, 0xff, 0xff
		, 0x00, 0x00, 0x00, 0x00
		, 0x00, 0x00, 0x00, 0x01
		, 0x00, 0x00, 0x00, 0x7f
		, 0xff, 0xff, 0xff, 0x80
		, 0xff, 0xff, 0xff, 0x81
		, 0x00, 0x00, 0x00, 0x20
		, 0xff, 0xff, 0xff, 0xe0
		, 0xde, 0xad, 0xa5, 0xae
		, 0xff, 0xff, 0xff, 0x9e};
	unsigned char actual_mem[4 * N];
	int32_t       actual_val[N];

	for (int i = 0; i < N; ++i)
	{
		void *pnext = serialize_int32_t(&(actual_mem[4 * i]), src_val[i]);
		if (pnext != (actual_mem + 4 * (i + 1)))
			TEST_FAILURE;
	}
	if (memcmp(src_mem, actual_mem, N))
		TEST_FAILURE;

	for (int i = 0; i < N; ++i)
	{
		void *pnext = deserialize_int32_t(&(actual_val[i]), ((int32_t*)src_mem) + i);
		if (pnext != (((int32_t*)src_mem) + i + 1))
			TEST_FAILURE;
	}
	if (memcmp(src_val, actual_val, N))
		TEST_FAILURE;
TEST_FINISHED

NEW_TEST(type_uint32_t)
	enum {N = 10};
	uint32_t src_val[N] =
		{ 4294967295UL
		,          0UL
		,          1UL
		,        127UL
		, 4294967168UL
		, 4294967169UL
		,         32UL
		, 4294967264UL
		, 3735922094UL
		, 4294967198UL};
	unsigned char src_mem[4 * N] =
		{ 0xff, 0xff, 0xff, 0xff
		, 0x00, 0x00, 0x00, 0x00
		, 0x00, 0x00, 0x00, 0x01
		, 0x00, 0x00, 0x00, 0x7f
		, 0xff, 0xff, 0xff, 0x80
		, 0xff, 0xff, 0xff, 0x81
		, 0x00, 0x00, 0x00, 0x20
		, 0xff, 0xff, 0xff, 0xe0
		, 0xde, 0xad, 0xa5, 0xae
		, 0xff, 0xff, 0xff, 0x9e};
	unsigned char actual_mem[4 * N];
	uint32_t      actual_val[N];

	for (int i = 0; i < N; ++i)
	{
		void *pnext = serialize_uint32_t(&(actual_mem[4 * i]), src_val[i]);
		if (pnext != (actual_mem + 4 * (i + 1)))
			TEST_FAILURE;
	}
	if (memcmp(src_mem, actual_mem, N))
		TEST_FAILURE;

	for (int i = 0; i < N; ++i)
	{
		void *pnext = deserialize_uint32_t(&(actual_val[i]), ((uint32_t*)src_mem) + i);
		if (pnext != (((uint32_t*)src_mem) + i + 1))
			TEST_FAILURE;
	}
	if (memcmp(src_val, actual_val, N))
		TEST_FAILURE;
TEST_FINISHED
#endif // INT32_SERIALIZATION_ALLOWED

#ifdef INT64_SERIALIZATION_ALLOWED
NEW_TEST(type_int64_t)
	enum {N = 10};
	int64_t src_val[N] =
		{                   -1LL
		,                    0LL
		,                    1LL
		,                  127LL
		,                 -128LL
		,                 -127LL
		,                   32LL
		,                  -32LL
		, -2401053089480333906LL
		,                  -98LL};
	unsigned char src_mem[8 * N] =
		{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
		, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
		, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01
		, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f
		, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80
		, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x81
		, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20
		, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0
		, 0xde, 0xad, 0xbe, 0xef, 0xba, 0xad, 0xa5, 0xae
		, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x9e};
	unsigned char actual_mem[8 * N];
	int64_t       actual_val[N];

	for (int i = 0; i < N; ++i)
	{
		void *pnext = serialize_int64_t(&(actual_mem[8 * i]), src_val[i]);
		if (pnext != (actual_mem + 8 * (i + 1)))
			TEST_FAILURE;
	}
	if (memcmp(src_mem, actual_mem, N))
		TEST_FAILURE;

	for (int i = 0; i < N; ++i)
	{
		void *pnext = deserialize_int64_t(&(actual_val[i]), ((int64_t*)src_mem) + i);
		if (pnext != (((int64_t*)src_mem) + i + 1))
			TEST_FAILURE;
	}
	if (memcmp(src_val, actual_val, N))
		TEST_FAILURE;
TEST_FINISHED

NEW_TEST(type_uint64_t)
	enum {N = 10};
	uint64_t src_val[N] =
		{ 18446744073709551615ULL
		,                    0ULL
		,                    1ULL
		,                  127ULL
		, 18446744073709551488ULL
		, 18446744073709551489ULL
		,                   32ULL
		, 18446744073709551584ULL
		, 16045690984229348782ULL
		, 18446744073709551518ULL};
	unsigned char src_mem[8 * N] =
		{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
		, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
		, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01
		, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f
		, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80
		, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x81
		, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20
		, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0
		, 0xde, 0xad, 0xbe, 0xef, 0xba, 0xad, 0xa5, 0xae
		, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x9e};
	unsigned char actual_mem[8 * N];
	uint64_t      actual_val[N];

	for (int i = 0; i < N; ++i)
	{
		void *pnext = serialize_uint64_t(&(actual_mem[8 * i]), src_val[i]);
		if (pnext != (actual_mem + 8 * (i + 1)))
			TEST_FAILURE;
	}
	if (memcmp(src_mem, actual_mem, N))
		TEST_FAILURE;

	for (int i = 0; i < N; ++i)
	{
		void *pnext = deserialize_uint64_t(&(actual_val[i]), ((uint64_t*)src_mem) + i);
		if (pnext != (((uint64_t*)src_mem) + i + 1))
			TEST_FAILURE;
	}
	if (memcmp(src_val, actual_val, N))
		TEST_FAILURE;
TEST_FINISHED
#endif // INT64_SERIALIZATION_ALLOWED

INIT_TESTS_CHECKS
	CHECK_TEST(TEST_CHECK_UP, type_int8_t);
	CHECK_TEST(TEST_CHECK_UP, type_uint8_t);
#ifdef INT16_SERIALIZATION_ALLOWED
	CHECK_TEST(TEST_CHECK_UP, type_int16_t);
	CHECK_TEST(TEST_CHECK_UP, type_uint16_t);
#endif // INT16_SERIALIZATION_ALLOWED
#ifdef INT32_SERIALIZATION_ALLOWED
	CHECK_TEST(TEST_CHECK_UP, type_int32_t);
	CHECK_TEST(TEST_CHECK_UP, type_uint32_t);
#endif // INT32_SERIALIZATION_ALLOWED
#ifdef INT64_SERIALIZATION_ALLOWED
	CHECK_TEST(TEST_CHECK_UP, type_int64_t);
	CHECK_TEST(TEST_CHECK_UP, type_uint64_t);
#endif // INT64_SERIALIZATION_ALLOWED
DONE_TESTS_CHECKS
