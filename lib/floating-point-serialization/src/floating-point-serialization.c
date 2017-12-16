#include <math.h>

#include "floating-point-serialization.h"
#include "internal-definitions/floating-point-serialization.h"

void*
serialize_float(
	  void *address_to_serialize
	, float value
) {
	void *p;
	int exp;
	float rest;
	int16_t exponenta;
	int32_t significant_bits;

	switch(fpclassify(value))
	{
		case FP_NAN:
		{
			p = serialize_uint8_t(address_to_serialize, FPMARK_NAN);
		}; break;
		case FP_INFINITE:
		{
			p =
				serialize_uint8_t(
					  address_to_serialize
					, (value > 0.0f) ? FPMARK_PINF : FPMARK_NINF);
		}; break;
		default:
		{
			p = serialize_uint8_t(address_to_serialize, FPMARK_REGULAR);
			rest = frexpf(value, &exp);
			exponenta = ((int16_t)exp);
			significant_bits = (int32_t)(rest * ((float)INT32_MAX));
		}; break;
	}

	p = serialize_int16_t(p, exponenta);
	p = serialize_int32_t(p, significant_bits);

	return p;
}

void*
deserialize_float(
	  float *value
	, void *address_to_deserialize
) {
	void *p;
	int exp;
	float rest;
	uint8_t fpmark;
	int16_t exponenta;
	int32_t significant_bits;

	p = deserialize_uint8_t(&fpmark, address_to_deserialize);
	p = deserialize_int16_t(&exponenta, p);
	p = deserialize_int32_t(&significant_bits, p);

	switch(fpmark)
	{
		case CASE_FPMARK_PINF:
		{
			*value = HUGE_VALF;
		}; break;
		case CASE_FPMARK_NINF:
		{
			*value = -HUGE_VALF;
		}; break;
		case CASE_FPMARK_REGULAR:
		{
			rest = ((float)significant_bits) / ((float)INT32_MAX);
			exp = (int)significant_bits;
			*value = ldexpf(rest, exp);
		}; break;
		case CASE_FPMARK_NAN:
		default:
		{
			*value = nanf("");
		}; break;
	}

	return p;
}


#ifdef DOUBLE_SERIALIZATION_ALLOWED

void*
serialize_double(
	  void *address_to_serialize
	, double value
) {
	void *p;
	int exp;
	double rest;
	int16_t exponenta;
	int64_t significant_bits;

	switch(fpclassify(value))
	{
		case FP_NAN:
		{
			p = serialize_uint8_t(address_to_serialize, FPMARK_NAN);
		}; break;
		case FP_INFINITE:
		{
			p =
				serialize_uint8_t(
					  address_to_serialize
					, (value > 0.0f) ? FPMARK_PINF : FPMARK_NINF);
		}; break;
		default:
		{
			p = serialize_uint8_t(address_to_serialize, FPMARK_REGULAR);
			rest = frexp(value, &exp);
			exponenta = ((int16_t)exp);
			significant_bits = (int64_t)(rest * ((float)INT64_MAX));
		}; break;
	}

	p = serialize_int16_t(p, exponenta);
	p = serialize_int64_t(p, significant_bits);

	return p;
}

void*
deserialize_double(
	  double *value
	, void *address_to_deserialize
) {
	void *p;
	int exp;
	double rest;
	uint8_t fpmark;
	int16_t exponenta;
	int64_t significant_bits;

	p = deserialize_uint8_t(&fpmark, address_to_deserialize);
	p = deserialize_int16_t(&exponenta, p);
	p = deserialize_int64_t(&significant_bits, p);

	switch(fpmark)
	{
		case CASE_FPMARK_PINF:
		{
			*value = HUGE_VAL;
		}; break;
		case CASE_FPMARK_NINF:
		{
			*value = -HUGE_VAL;
		}; break;
		case CASE_FPMARK_REGULAR:
		{
			rest = ((double)significant_bits) / ((double)INT32_MAX);
			exp = (int)significant_bits;
			*value = ldexp(rest, exp);
		}; break;
		case CASE_FPMARK_NAN:
		default:
		{
			*value = nan("");
		}; break;
	}

	return p;
}
#endif // DOUBLE_SERIALIZATION_ALLOWED
