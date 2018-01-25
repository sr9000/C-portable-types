
/**
 * @file blob-serialization.h
 * @author Rogonov Stepan Alekseevich
 * @brief File containing definitions of serialization functions.
 * @details Defines serialization and deserialization functions for Binary
 * Large OBject.
 * @warning There are no checks for unallocated memory or out-of-range errors.
 */

#ifndef BLOB_SERIALIZATION_HEADER
#define BLOB_SERIALIZATION_HEADER

#include "integer-serialization.h"

#ifndef INT8_SERIALIZATION_ALLOWED
#error "BLOB serialization library can not be build, because smalles 8-bit "\
       "type is unsupported on your platform."
#endif // INT8_SERIALIZATION_ALLOWED

#ifndef INT32_SERIALIZATION_ALLOWED
#error "BLOB serialization library can not be build, because 32-bit integer"\
       "type is unsupported on your platform."
#endif // INT32_SERIALIZATION_ALLOWED

/**
 * @def BLOB_SERIALIZATION_ALLOWED
 * @brief Serialization operations allowed for BLOB.
 */
#define BLOB_SERIALIZATION_ALLOWED

/**
 * @brief Serialize BLOB value
 * @code{.c}
 * void *stream = get_stream_for_serialization();
 * char blob[] = "Character sequence as an example of BLOB";
 * stream = serialize_blob(stream, blob, sizeof(blob));
 * @endcode
 * @param [out] address_to_serialize Address, where @p data will be written.
 * @param [in] data BLOB value.
 * @param [in] size Number of bytes (8-bit integers). Specified number of bytes
 * of BLOB will be serialized.
 * @return Address of stream, shifted on size of serialized BLOB value.
 * @warning Function is unsafe if @p address_to_serialize or @p data is NULL or
 * not allocated.
 */
void*
serialize_blob(
	  void *address_to_serialize
	, void *data
	, uint32_t size
);

/**
 * @brief Return size of serialized BLOB value
 * @code{.c}
 * void *stream = get_stream_for_deserialization();
 * #define N = 100;
 * uint8_t blob[N];
 * if (N < get_size_of_blob(stream))
 * {
 * 	// some error throwing
 * }
 * @endcode
 * @param [in] address_to_deserialize Address, from size will be read.
 * @return Size of BLOB, stored in @p address_to_deserialize.
 * @warning Function is unsafe if @p address_to_deserialize is NULL or not
 * allocated.
 */
uint32_t
get_size_of_blob(
	  void *address_to_deserialize
);

/**
 * @brief Deserialize BLOB value
 * @code{.c}
 * void *stream = get_stream_for_deserialization();
 * #define N = 100;
 * uint8_t blob[N];
 * if (N < get_size_of_blob(stream))
 * {
 * 	// some error throwing
 * }
 * stream = deserialize_blob(blob, stream);
 * @endcode
 * @param [out] data Storage of deserialized BLOB value.
 * @param [in] address_to_deserialize Address, from @p data will be read.
 * @return Address of stream, shifted on size of serialized BLOB value.
 * @warning Function is unsafe if @p address_to_deserialize or @p data is NULL
 * or not allocated.
 */
void*
deserialize_blob(
	  void *data
	, void *address_to_deserialize
);

#ifdef INT64_SERIALIZATION_ALLOWED
/**
 * @def BELOB_SERIALIZATION_ALLOWED
 * @brief Serialization operations allowed for Binary Extra Large OBjects.
 */
#define BELOB_SERIALIZATION_ALLOWED

/**
 * @brief Serialize BELOB value
 * @code{.c}
 * void *stream = get_stream_for_serialization();
 * void *belob32GB = get_32GB_belob();
 * uint64_t size = get_size_of_32GB_belob();
 * stream = serialize_belob(stream, belob32GB, size);
 * @endcode
 * @param [out] address_to_serialize Address, where @p data will be written.
 * @param [in] data BELOB value.
 * @param [in] size Number of bytes (8-bit integers). Specified number of bytes
 * of BELOB will be serialized.
 * @return Address of stream, shifted on size of serialized BELOB value.
 * @warning Function is unsafe if @p address_to_serialize or @p data is NULL or
 * not allocated.
 */
void*
serialize_belob(
	  void *address_to_serialize
	, void *data
	, uint64_t size
);

/**
 * @brief Return size of serialized BELOB value
 * @code{.c}
 * void *stream = get_stream_for_deserialization();
 * #define N = 100;
 * uint8_t blob[N];
 * if (N < get_size_of_belob(stream))
 * {
 * 	// some error throwing
 * }
 * @endcode
 * @param [in] address_to_deserialize Address, from size will be read.
 * @return Size of BELOB, stored in @p address_to_deserialize.
 * @warning Function is unsafe if @p address_to_deserialize is NULL or not
 * allocated.
 */
uint64_t
get_size_of_belob(
	  void *address_to_deserialize
);

/**
 * @brief Deserialize BELOB value
 * @code{.c}
 * // definition of _32GB constant
 * void *stream = get_stream_for_deserialization();
 * uint8_t belob[_32GB];
 * if (N < get_size_of_belob(stream))
 * {
 * 	// some error throwing
 * }
 * stream = deserialize_belob(belob, stream);
 * @endcode
 * @param [out] data Storage of deserialized BELOB value.
 * @param [in] address_to_deserialize Address, from @p data will be read.
 * @return Address of stream, shifted on size of serialized BELOB value.
 * @warning Function is unsafe if @p address_to_deserialize or @p data is NULL
 * or not allocated.
 */
void*
deserialize_belob(
	  void *data
	, void *address_to_deserialize
);

#endif // INT64_SERIALIZATION_ALLOWED

#endif // BLOB_SERIALIZATION_HEADER
