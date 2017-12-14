
/**
 * @file integer-serialization.h
 * @author Rogonov Stepan Alekseevich
 * @brief File containing definitions of serialization functions.
 * @details Defines serialization and deserialization functions for each
 * possible type, from int8_t to int64_t. Each function works in similar way on
 * all possible platforms: integer always serialized in big-endian format.
 */

#ifndef INTEGER_SERIALIZATION_HEADER
#define INTEGER_SERIALIZATION_HEADER

#include <stdint.h>

// check int8_t exists
#ifndef INT8_MAX
#error "Integer serialization library can not be build, because smalles 8-bit "\
       "type unsupported on your platform."
#endif //INT8_MAX

// check uint8_t exists
#ifndef UINT8_MAX
#error "Integer serialization library can not be build, because smalles 8-bit "\
       "type unsupported on your platform."
#endif //UINT8_MAX

/**
 * @def INT8_SERIALIZATION_ALLOWED
 * @brief Serialization operations allowed for int8_t and uint8_t.
 */
#define INT8_SERIALIZATION_ALLOWED

/**
 * @brief Serialize int8_t value
 * @code{.c}
 * void *stream = get_stream_for_serialization();
 * int8_t value = 1;
 * stream = serialize_int8_t(stream, value);
 * @endcode
 * @param [out] address_to_serialize Address, where @p value will be written.
 * @param [in] value int8_t value.
 * @return Address of stream, shifted on size of int8_t value.
 * @warning Function is unsafe if @p address_to_serialize is NULL or not
 * allocated.
 */
void*
serialize_int8_t(
	  void *address_to_serialize
	, int8_t value
);

/**
 * @brief Deserialize int8_t value
 * @code{.c}
 * void *stream = get_stream_for_deserialization();
 * int8_t value;
 * stream = deserialize_int8_t(&value, stream);
 * @endcode
 * @param [out] value Storage of deserialized int8_t value.
 * @param [in] address_to_deserialize Address, from @p value will be read.
 * @return Address of stream, shifted on size of int8_t value.
 * @warning Function is unsafe if @p address_to_deserialize or @p value is NULL
 * or not allocated.
 */
void*
deserialize_int8_t(
	  int8_t *value
	, void *address_to_deserialize
);

/**
 * @brief Serialize uint8_t value
 * @code{.c}
 * void *stream = get_stream_for_serialization();
 * uint8_t value = 1;
 * stream = serialize_uint8_t(stream, value);
 * @endcode
 * @param [out] address_to_serialize Address, where @p value will be written.
 * @param [in] value uint8_t value.
 * @return Address of stream, shifted on size of uint8_t value.
 * @warning Function is unsafe if @p address_to_serialize is NULL or not
 * allocated.
 */
void*
serialize_uint8_t(
	  void *address_to_serialize
	, uint8_t value
);

/**
 * @brief Deserialize uint8_t value
 * @code{.c}
 * void *stream = get_stream_for_deserialization();
 * uint8_t value;
 * stream = deserialize_uint8_t(&value, stream);
 * @endcode
 * @param [out] value Storage of deserialized uint8_t value.
 * @param [in] address_to_deserialize Address, from @p value will be read.
 * @return Address of stream, shifted on size of uint8_t value.
 * @warning Function is unsafe if @p address_to_deserialize or @p value is NULL
 * or not allocated.
 */
void*
deserialize_uint8_t(
	  uint8_t *value
	, void *address_to_deserialize
);

#ifdef INT16_MAX

/**
 * @def INT16_SERIALIZATION_ALLOWED
 * @brief Serialization operations allowed for int16_t and uint16_t.
 */
#define INT16_SERIALIZATION_ALLOWED

/**
 * @brief Serialize int16_t value
 * @code{.c}
 * void *stream = get_stream_for_serialization();
 * int16_t value = 1;
 * stream = serialize_int16_t(stream, value);
 * @endcode
 * @param [out] address_to_serialize Address, where @p value will be written.
 * @param [in] value int16_t value.
 * @return Address of stream, shifted on size of int16_t value.
 * @warning Function is unsafe if @p address_to_serialize is NULL or not
 * allocated.
 */
void*
serialize_int16_t(
	  void *address_to_serialize
	, int16_t value
);

/**
 * @brief Deserialize int16_t value
 * @code{.c}
 * void *stream = get_stream_for_deserialization();
 * int16_t value;
 * stream = deserialize_int16_t(&value, stream);
 * @endcode
 * @param [out] value Storage of deserialized int16_t value.
 * @param [in] address_to_deserialize Address, from @p value will be read.
 * @return Address of stream, shifted on size of int16_t value.
 * @warning Function is unsafe if @p address_to_deserialize or @p value is NULL
 * or not allocated.
 */
void*
deserialize_int16_t(
	  int16_t *value
	, void *address_to_deserialize
);

/**
 * @brief Serialize uint16_t value
 * @code{.c}
 * void *stream = get_stream_for_serialization();
 * uint16_t value = 1;
 * stream = serialize_uint16_t(stream, value);
 * @endcode
 * @param [out] address_to_serialize Address, where @p value will be written.
 * @param [in] value uint16_t value.
 * @return Address of stream, shifted on size of uint16_t value.
 * @warning Function is unsafe if @p address_to_serialize is NULL or not
 * allocated.
 */
void*
serialize_uint16_t(
	  void *address_to_serialize
	, uint16_t value
);

/**
 * @brief Deserialize uint16_t value
 * @code{.c}
 * void *stream = get_stream_for_deserialization();
 * uint16_t value;
 * stream = deserialize_uint16_t(&value, stream);
 * @endcode
 * @param [out] value Storage of deserialized uint16_t value.
 * @param [in] address_to_deserialize Address, from @p value will be read.
 * @return Address of stream, shifted on size of uint16_t value.
 * @warning Function is unsafe if @p address_to_deserialize or @p value is NULL
 * or not allocated.
 */
void*
deserialize_uint16_t(
	  uint16_t *value
	, void *address_to_deserialize
);
#endif // INT16_MAX

#ifdef INT32_MAX

/**
 * @def INT32_SERIALIZATION_ALLOWED
 * @brief Serialization operations allowed for int32_t and uint32_t.
 */
#define INT32_SERIALIZATION_ALLOWED

/**
 * @brief Serialize int32_t value
 * @code{.c}
 * void *stream = get_stream_for_serialization();
 * int32_t value = 1;
 * stream = serialize_int32_t(stream, value);
 * @endcode
 * @param [out] address_to_serialize Address, where @p value will be written.
 * @param [in] value int32_t value.
 * @return Address of stream, shifted on size of int32_t value.
 * @warning Function is unsafe if @p address_to_serialize is NULL or not
 * allocated.
 */
void*
serialize_int32_t(
	  void *address_to_serialize
	, int32_t value
);

/**
 * @brief Deserialize int32_t value
 * @code{.c}
 * void *stream = get_stream_for_deserialization();
 * int32_t value;
 * stream = deserialize_int32_t(&value, stream);
 * @endcode
 * @param [out] value Storage of deserialized int32_t value.
 * @param [in] address_to_deserialize Address, from @p value will be read.
 * @return Address of stream, shifted on size of int32_t value.
 * @warning Function is unsafe if @p address_to_deserialize or @p value is NULL
 * or not allocated.
 */
void*
deserialize_int32_t(
	  int32_t *value
	, void *address_to_deserialize
);

/**
 * @brief Serialize uint32_t value
 * @code{.c}
 * void *stream = get_stream_for_serialization();
 * uint32_t value = 1;
 * stream = serialize_uint32_t(stream, value);
 * @endcode
 * @param [out] address_to_serialize Address, where @p value will be written.
 * @param [in] value uint32_t value.
 * @return Address of stream, shifted on size of uint32_t value.
 * @warning Function is unsafe if @p address_to_serialize is NULL or not
 * allocated.
 */
void*
serialize_uint32_t(
	  void *address_to_serialize
	, uint32_t value
);

/**
 * @brief Deserialize uint32_t value
 * @code{.c}
 * void *stream = get_stream_for_deserialization();
 * uint32_t value;
 * stream = deserialize_uint32_t(&value, stream);
 * @endcode
 * @param [out] value Storage of deserialized uint32_t value.
 * @param [in] address_to_deserialize Address, from @p value will be read.
 * @return Address of stream, shifted on size of uint32_t value.
 * @warning Function is unsafe if @p address_to_deserialize or @p value is NULL
 * or not allocated.
 */
void*
deserialize_uint32_t(
	  uint32_t *value
	, void *address_to_deserialize
);
#endif // INT32_MAX

#ifdef INT64_MAX

/**
 * @def INT64_SERIALIZATION_ALLOWED
 * @brief Serialization operations allowed for int64_t and uint64_t.
 */
#define INT64_SERIALIZATION_ALLOWED

/**
 * @brief Serialize int64_t value
 * @code{.c}
 * void *stream = get_stream_for_serialization();
 * int64_t value = 1;
 * stream = serialize_int64_t(stream, value);
 * @endcode
 * @param [out] address_to_serialize Address, where @p value will be written.
 * @param [in] value int64_t value.
 * @return Address of stream, shifted on size of int64_t value.
 * @warning Function is unsafe if @p address_to_serialize is NULL or not
 * allocated.
 */
void*
serialize_int64_t(
	  void *address_to_serialize
	, int64_t value
);

/**
 * @brief Deserialize int64_t value
 * @code{.c}
 * void *stream = get_stream_for_deserialization();
 * int64_t value;
 * stream = deserialize_int64_t(&value, stream);
 * @endcode
 * @param [out] value Storage of deserialized int64_t value.
 * @param [in] address_to_deserialize Address, from @p value will be read.
 * @return Address of stream, shifted on size of int64_t value.
 * @warning Function is unsafe if @p address_to_deserialize or @p value is NULL
 * or not allocated.
 */
void*
deserialize_int64_t(
	  int64_t *value
	, void *address_to_deserialize
);

/**
 * @brief Serialize uint64_t value
 * @code{.c}
 * void *stream = get_stream_for_serialization();
 * uint64_t value = 1;
 * stream = serialize_uint64_t(stream, value);
 * @endcode
 * @param [out] address_to_serialize Address, where @p value will be written.
 * @param [in] value uint64_t value.
 * @return Address of stream, shifted on size of uint64_t value.
 * @warning Function is unsafe if @p address_to_serialize is NULL or not
 * allocated.
 */
void*
serialize_uint64_t(
	  void *address_to_serialize
	, uint64_t value
);

/**
 * @brief Deserialize uint64_t value
 * @code{.c}
 * void *stream = get_stream_for_deserialization();
 * uint64_t value;
 * stream = deserialize_uint64_t(&value, stream);
 * @endcode
 * @param [out] value Storage of deserialized uint64_t value.
 * @param [in] address_to_deserialize Address, from @p value will be read.
 * @return Address of stream, shifted on size of uint64_t value.
 * @warning Function is unsafe if @p address_to_deserialize or @p value is NULL
 * or not allocated.
 */
void*
deserialize_uint64_t(
	  uint64_t *value
	, void *address_to_deserialize
);
#endif // INT64_MAX

#endif // INTEGER_SERIALIZATION_HEADER
