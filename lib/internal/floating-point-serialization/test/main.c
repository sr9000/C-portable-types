#include <string.h>
#include <math.h>
#include <float.h>

#include "floating-point-serialization.h"
#include "internal-definitions/floating-point-serialization.h"
#include "test.h"

NEW_TEST(type_float_regular)
	enum {N = 10};
	float src_val[N] =
		{  0.0f      //  zero
		,  1.0f      //  one
		, -1.0f      //  minus one
		,  1.0f/3.0f //  0.(3)
		,  M_PI      //  3.1415...
		,  M_E       //  2.7182...
		,  M_SQRT2   //  1.4142...
		, -M_PI      // -3.1415...
		, -M_E       // -2.7182...
		, -M_SQRT2}; // -1.4142...
	float delta[N];
	float actual_val[N];
	unsigned char actual_mem[SIZE_OF_SERIALIZED_FLOAT * N];

	// init delta
	for (int i = 0; i < N; ++i)
	{
		delta[i] = fmaxf(5.0f * FLT_MIN, fabsf(5.0f * FLT_EPSILON * src_val[i]));
	}

	// serialize
	for (int i = 0; i < N; ++i)
	{
		void *pnext =
			serialize_float(
				  &(actual_mem[SIZE_OF_SERIALIZED_FLOAT * i])
				, src_val[i]);
		if (pnext != (actual_mem + SIZE_OF_SERIALIZED_FLOAT * (i + 1)))
			TEST_FAILURE;
	}

	// deserialize
	for (int i = 0; i < N; ++i)
	{
		void *pnext =
			deserialize_float(
				  &(actual_val[i])
				, actual_mem + i * SIZE_OF_SERIALIZED_FLOAT);
		if (islessequal(delta[i], fabsf(actual_val[i] - src_val[i])))
			TEST_FAILURE;
		if (pnext != (actual_mem + SIZE_OF_SERIALIZED_FLOAT * (i + 1)))
			TEST_FAILURE;
	}
TEST_FINISHED

NEW_TEST(type_float_special)
	void *p;
	uint8_t indicate_byte;
	float src_pinf    =  HUGE_VALF;
	float src_ninf    = -HUGE_VALF;
	float src_nan     =  nanf("");
	float src_regular =  1.234f;
	float actual_val;
	unsigned char actual_mem[SIZE_OF_SERIALIZED_FLOAT];

	{ // check positive infinity
		p = serialize_float(actual_mem, src_pinf);
		// memory shift
		if (p != (actual_mem + SIZE_OF_SERIALIZED_FLOAT))
			TEST_FAILURE;
		// indicate byte
		p = deserialize_uint8_t(&indicate_byte, actual_mem);
		if (indicate_byte != FPMARK_PINF)
			TEST_FAILURE;

		p = deserialize_float(&actual_val, actual_mem);
		// memory shift
		if (p != (actual_mem + SIZE_OF_SERIALIZED_FLOAT))
			TEST_FAILURE;
		// check value
		if (!isinf(actual_val))
			TEST_FAILURE;
		if (!isgreater(actual_val, 0.0f))
			TEST_FAILURE;
	}
	{ // check positive infinity
		p = serialize_float(actual_mem, src_ninf);
		// memory shift
		if (p != (actual_mem + SIZE_OF_SERIALIZED_FLOAT))
			TEST_FAILURE;
		// indicate byte
		p = deserialize_uint8_t(&indicate_byte, actual_mem);
		if (indicate_byte != FPMARK_NINF)
			TEST_FAILURE;

		p = deserialize_float(&actual_val, actual_mem);
		// memory shift
		if (p != (actual_mem + SIZE_OF_SERIALIZED_FLOAT))
			TEST_FAILURE;
		// check value
		if (!isinf(actual_val))
			TEST_FAILURE;
		if (!isless(actual_val, 0.0f))
			TEST_FAILURE;
	}
	{ // check NaN
		p = serialize_float(actual_mem, src_nan);
		// memory shift
		if (p != (actual_mem + SIZE_OF_SERIALIZED_FLOAT))
			TEST_FAILURE;
		// indicate byte
		p = deserialize_uint8_t(&indicate_byte, actual_mem);
		if (indicate_byte != FPMARK_NAN)
			TEST_FAILURE;

		p = deserialize_float(&actual_val, actual_mem);
		// memory shift
		if (p != (actual_mem + SIZE_OF_SERIALIZED_FLOAT))
			TEST_FAILURE;
		// check value
		if (!isnan(actual_val))
			TEST_FAILURE;
	}
	{ // check regular
		p = serialize_float(actual_mem, src_regular);
		// memory shift
		if (p != (actual_mem + SIZE_OF_SERIALIZED_FLOAT))
			TEST_FAILURE;
		// indicate byte
		p = deserialize_uint8_t(&indicate_byte, actual_mem);
		if (indicate_byte != FPMARK_REGULAR)
			TEST_FAILURE;

		p = deserialize_float(&actual_val, actual_mem);
		// memory shift
		if (p != (actual_mem + SIZE_OF_SERIALIZED_FLOAT))
			TEST_FAILURE;
		// check value
		if (isnan(actual_val))
			TEST_FAILURE;
		if (isinf(actual_val))
			TEST_FAILURE;
	}
TEST_FINISHED

#ifdef DOUBLE_SERIALIZATION_ALLOWED

NEW_TEST(type_double_regular)
	enum {N = 10};
	double src_val[N] =
		{  0.0       //  zero
		,  1.0       //  one
		, -1.0       //  minus one
		,  1.0/3.0   //  0.(3)
		,  M_PI      //  3.1415...
		,  M_E       //  2.7182...
		,  M_SQRT2   //  1.4142...
		, -M_PI      // -3.1415...
		, -M_E       // -2.7182...
		, -M_SQRT2}; // -1.4142...
	double delta[N];
	double actual_val[N];
	unsigned char actual_mem[SIZE_OF_SERIALIZED_DOUBLE * N];

	// init delta
	for (int i = 0; i < N; ++i)
	{
		delta[i] = fmax(5.0 * DBL_MIN, fabs(5.0 * DBL_EPSILON * src_val[i]));
	}

	// serialize
	for (int i = 0; i < N; ++i)
	{
		void *pnext =
			serialize_double(
				  &(actual_mem[SIZE_OF_SERIALIZED_DOUBLE * i])
				, src_val[i]);
		if (pnext != (actual_mem + SIZE_OF_SERIALIZED_DOUBLE * (i + 1)))
			TEST_FAILURE;
	}

	// deserialize
	for (int i = 0; i < N; ++i)
	{
		void *pnext =
			deserialize_double(
				  &(actual_val[i])
				, actual_mem + i * SIZE_OF_SERIALIZED_DOUBLE);
		if (islessequal(delta[i], fabs(actual_val[i] - src_val[i])))
			TEST_FAILURE;
		if (pnext != (actual_mem + SIZE_OF_SERIALIZED_DOUBLE * (i + 1)))
			TEST_FAILURE;
	}
TEST_FINISHED

NEW_TEST(type_double_special)
	void *p;
	uint8_t indicate_byte;
	double src_pinf    =  HUGE_VAL;
	double src_ninf    = -HUGE_VAL;
	double src_nan     =  nan("");
	double src_regular =  1.234;
	double actual_val;
	unsigned char actual_mem[SIZE_OF_SERIALIZED_DOUBLE];

	{ // check positive infinity
		p = serialize_double(actual_mem, src_pinf);
		// memory shift
		if (p != (actual_mem + SIZE_OF_SERIALIZED_DOUBLE))
			TEST_FAILURE;
		// indicate byte
		p = deserialize_uint8_t(&indicate_byte, actual_mem);
		if (indicate_byte != FPMARK_PINF)
			TEST_FAILURE;

		p = deserialize_double(&actual_val, actual_mem);
		// memory shift
		if (p != (actual_mem + SIZE_OF_SERIALIZED_DOUBLE))
			TEST_FAILURE;
		// check value
		if (!isinf(actual_val))
			TEST_FAILURE;
		if (!isgreater(actual_val, 0.0))
			TEST_FAILURE;
	}
	{ // check positive infinity
		p = serialize_double(actual_mem, src_ninf);
		// memory shift
		if (p != (actual_mem + SIZE_OF_SERIALIZED_DOUBLE))
			TEST_FAILURE;
		// indicate byte
		p = deserialize_uint8_t(&indicate_byte, actual_mem);
		if (indicate_byte != FPMARK_NINF)
			TEST_FAILURE;

		p = deserialize_double(&actual_val, actual_mem);
		// memory shift
		if (p != (actual_mem + SIZE_OF_SERIALIZED_DOUBLE))
			TEST_FAILURE;
		// check value
		if (!isinf(actual_val))
			TEST_FAILURE;
		if (!isless(actual_val, 0.0))
			TEST_FAILURE;
	}
	{ // check NaN
		p = serialize_double(actual_mem, src_nan);
		// memory shift
		if (p != (actual_mem + SIZE_OF_SERIALIZED_DOUBLE))
			TEST_FAILURE;
		// indicate byte
		p = deserialize_uint8_t(&indicate_byte, actual_mem);
		if (indicate_byte != FPMARK_NAN)
			TEST_FAILURE;

		p = deserialize_double(&actual_val, actual_mem);
		// memory shift
		if (p != (actual_mem + SIZE_OF_SERIALIZED_DOUBLE))
			TEST_FAILURE;
		// check value
		if (!isnan(actual_val))
			TEST_FAILURE;
	}
	{ // check regular
		p = serialize_double(actual_mem, src_regular);
		// memory shift
		if (p != (actual_mem + SIZE_OF_SERIALIZED_DOUBLE))
			TEST_FAILURE;
		// indicate byte
		p = deserialize_uint8_t(&indicate_byte, actual_mem);
		if (indicate_byte != FPMARK_REGULAR)
			TEST_FAILURE;

		p = deserialize_double(&actual_val, actual_mem);
		// memory shift
		if (p != (actual_mem + SIZE_OF_SERIALIZED_DOUBLE))
			TEST_FAILURE;
		// check value
		if (isnan(actual_val))
			TEST_FAILURE;
		if (isinf(actual_val))
			TEST_FAILURE;
	}
TEST_FINISHED
#endif // DOUBLE_SERIALIZATION_ALLOWED

INIT_TESTS_CHECKS
	CHECK_TEST(TEST_CHECK_UP, type_float_regular);
	CHECK_TEST(TEST_CHECK_UP, type_float_special);
#ifdef DOUBLE_SERIALIZATION_ALLOWED
	CHECK_TEST(TEST_CHECK_UP, type_double_regular);
	CHECK_TEST(TEST_CHECK_UP, type_double_special);
#endif // DOUBLE_SERIALIZATION_ALLOWED
DONE_TESTS_CHECKS
