
/**
 * @file floating-point-serialization.h
 * @author Rogonov Stepan Alekseevich
 * @brief File containing definitions of serialization functions.
 * @details Defines serialization and deserialization functions for each
 * possible type, from float to double. Each function works in similar way
 * on all possible platforms. Values always serialized as indication byte and
 * pair of integers: power of two and normilized fraction. Indication byte
 * indicates special floating point value like +Inf, -Inf and NaN. Normilized
 * fraction is multiplied by maximum integer value and stored in integer type,
 * that is big enough to store all significant bits.
 * @warning There are no function to serialization-deserialization of long
 * double, because size and precision of that type is very implementation
 * depending and cannot be portable between differen platforms with lower or
 * higher precision than source platform of serialized long double value.
 */

#ifndef FLOATING_POINT_SERIALIZATION_HEADER
#define FLOATING_POINT_SERIALIZATION_HEADER

#include <stdint.h>

#include "integer-serialization.h"

#ifndef INT8_SERIALIZATION_ALLOWED
#error "Floating point serialization library can not be build, because "\
       "8-bit integer type serialization is unsupported on your platform."
#endif // INT8_MAX

#ifndef INT16_SERIALIZATION_ALLOWED
#error "Floating point serialization library can not be build, because "\
       "16-bit integer type serialization is unsupported on your platform."
#endif // INT16_MAX

#ifndef INT32_SERIALIZATION_ALLOWED
#error "Floating point serialization library can not be build, because "\
       "32-bit integer type serialization is unsupported on your platform."
#endif // INT16_MAX

#ifndef INT32_MAX
#error "Floating point serialization library can not be build, because "\
       "maximum value for int32_t is undefined."
#endif // INT8_MAX

/**
 * @def FLOAT_SERIALIZATION_ALLOWED
 * @brief Serialization operations allowed for float.
 */
#define FLOAT_SERIALIZATION_ALLOWED

/**
 * @def SIZE_OF_SERIALIZED_FLOAT
 * @brief Size in bytes of serialized float value.
 */
#define SIZE_OF_SERIALIZED_FLOAT 7

/**
 * @name Indication byte constants.
 * @{
 */

/**
 * @brief Indicates _Not A Number_ value.
 */
static const uint8_t FPMARK_NAN = 1;

/**
 * @brief Indicates _Positive Infinity_ value.
 */
static const uint8_t FPMARK_PINF = 2;

/**
 * @brief Indicates _Negative Infinity_ value.
 */
static const uint8_t FPMARK_NINF = 3;

/**
 * @brief Indicates regular floating point value.
 */
static const uint8_t FPMARK_REGULAR = 4;

/**
 * @}
 */

/**
 * @brief Serialize float value
 * @code{.c}
 * void *stream = get_stream_for_serialization();
 * float value = 3.1415;
 * stream = serialize_float(stream, value);
 * @endcode
 * @param [out] address_to_serialize Address, where @p value will be written.
 * @param [in] value float value.
 * @return Address of stream, shifted on size of serialized floating point
 * value.
 * @warning Function is unsafe if @p address_to_serialize is NULL or not
 * allocated.
 */
void*
serialize_float(
	  void *address_to_serialize
	, float value
);

/**
 * @brief Deserialize float value
 * @code{.c}
 * void *stream = get_stream_for_deserialization();
 * float value;
 * stream = deserialize_float(&value, stream);
 * @endcode
 * @param [out] value Storage of deserialized float value.
 * @param [in] address_to_deserialize Address, from @p value will be read.
 * @return Address of stream, shifted on size of serialized floating point
 * value.
 * @warning Function is unsafe if @p address_to_deserialize or @p value is NULL
 * or not allocated.
 */
void*
deserialize_float(
	  float *value
	, void *address_to_deserialize
);


#ifdef INT64_SERIALIZATION_ALLOWED

// check max int64_t value defined.
// it needs to serialize significant bits in crossplatform like way.
#ifdef INT64_MAX

/**
 * @def DOUBLE_SERIALIZATION_ALLOWED
 * @brief Serialization operations allowed for double.
 */
#define DOUBLE_SERIALIZATION_ALLOWED

/**
 * @def SIZE_OF_SERIALIZED_DOUBLE
 * @brief Size in bytes of serialized double value.
 */
#define SIZE_OF_SERIALIZED_DOUBLE 11

/**
 * @brief Serialize double value
 * @code{.c}
 * void *stream = get_stream_for_serialization();
 * double value = 3.1415;
 * stream = serialize_double(stream, value);
 * @endcode
 * @param [out] address_to_serialize Address, where @p value will be written.
 * @param [in] value double value.
 * @return Address of stream, shifted on size of serialized floating point
 * value.
 * @warning Function is unsafe if @p address_to_serialize is NULL or not
 * allocated.
 */
void*
serialize_double(
	  void *address_to_serialize
	, double value
);

/**
 * @brief Deserialize double value
 * @code{.c}
 * void *stream = get_stream_for_deserialization();
 * double value;
 * stream = deserialize_double(&value, stream);
 * @endcode
 * @param [out] value Storage of deserialized double value.
 * @param [in] address_to_deserialize Address, from @p value will be read.
 * @return Address of stream, shifted on size of serialized floating point
 * value.
 * @warning Function is unsafe if @p address_to_deserialize or @p value is NULL
 * or not allocated.
 */
void*
deserialize_double(
	  double *value
	, void *address_to_deserialize
);
#endif // INT64_MAX
#endif // INT64_SERIALIZATION_ALLOWED

#endif // FLOATING_POINT_SERIALIZATION_HEADER
