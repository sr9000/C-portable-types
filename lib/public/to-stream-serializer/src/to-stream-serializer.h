
/**
 * @file to-stream-serializer.h
 * @author Rogonov Stepan Alekseevich
 * @brief File containing definitions of serialization functions.
 * @details Defines serialization and deserialization functions for each
 * possible type, from int8_t to int64_t. Each function works in similar way on
 * all possible platforms: integer always serialized in big-endian format.
 */

#ifndef TO_STREAM_SERIALIZER_HEADER
#define TO_STREAM_SERIALIZER_HEADER

#include <stdint.h>
#include <stdlib.h>

#include "flow-control.h"
#include "integer-serialization.h"
#include "floating-point-serialization.h"
#include "blob-serialization.h"

// check int8_t exists
#ifndef INT8_MAX
#error "To stream serializer library can not be build, because smalles 8-bit "\
       "type is unsupported on your platform."
#endif // INT8_MAX

typedef void   (*free_ptr_t)    (void *);
typedef void * (*malloc_ptr_t)  (size_t);
typedef void * (*calloc_ptr_t)  (size_t, size_t);
typedef void * (*realloc_ptr_t) (void *, size_t);

typedef struct
{
	free_ptr_t    pfree;
	malloc_ptr_t  pmalloc;
	calloc_ptr_t  pcalloc;
	realloc_ptr_t prealloc;
	void* nullptr_val;
} mem_allctr_t;

const extern mem_allctr_t DEF_MEM_ALLCTR;

typedef size_t (*increase_ptr_t) (size_t);

size_t inc_plus32  (size_t);
size_t inc_plus4k  (size_t);
size_t inc_plus16k (size_t);
size_t inc_x2_plus1(size_t);

typedef struct
{
	mem_allctr_t mem_allctr;
	increase_ptr_t pincrease;
} mem_mngr_t;

const extern mem_mngr_t DEF_MEM_MNGR;

typedef struct
{
	size_t capacity;
	size_t available;
	size_t max_capacity;
} stream_metha_t;

typedef struct struct_stream
{
	stream_metha_t  metha;
	mem_mngr_t      mem_mngr;
	uint8_t        *mem_ptr;
	uint8_t        *free_mem_ptr;
} *stream_ptr_t;

mem_allctr_t
create_mem_allctr(
	  free_ptr_t    pfree
	, malloc_ptr_t  pmalloc
	, calloc_ptr_t  pcalloc
	, realloc_ptr_t prealloc
);

mem_allctr_t
create_mem_allctr_ex(
	  free_ptr_t     pfree
	, malloc_ptr_t   pmalloc
	, calloc_ptr_t   pcalloc
	, realloc_ptr_t  prealloc
	, void          *nullptr_val
);

mem_mngr_t
create_mem_mngr(
	  mem_allctr_t   allctr
	, increase_ptr_t pincrease
);

mem_mngr_t
create_mem_mngr_ex(
	  free_ptr_t     pfree
	, malloc_ptr_t   pmalloc
	, calloc_ptr_t   pcalloc
	, realloc_ptr_t  prealloc
	, void          *nullptr_val
	, increase_ptr_t pincrease
);

FlwSt
new_stream(
	  stream_ptr_t *pstream
	, mem_mngr_t mngr
	, size_t max_capacity
	, size_t init_capacity
);

FlwSt
new_stream_ex(
	  stream_ptr_t  *pstream
	, free_ptr_t     pfree
	, malloc_ptr_t   pmalloc
	, calloc_ptr_t   pcalloc
	, realloc_ptr_t  prealloc
	, void          *nullptr_val
	, increase_ptr_t pincrease
	, size_t max_capacity
	, size_t init_capacity
);

FlwSt delete_stream(stream_ptr_t *pstream);

#ifdef INT8_SERIALIZATION_ALLOWED
FlwSt stream_int8_t(stream_ptr_t stream, int8_t value);
FlwSt stream_uint8_t(stream_ptr_t stream, uint8_t value);
#endif // INT8_SERIALIZATION_ALLOWED

#ifdef INT16_SERIALIZATION_ALLOWED
FlwSt stream_int16_t(stream_ptr_t stream, int16_t value);
FlwSt stream_uint16_t(stream_ptr_t stream, uint16_t value);
#endif // INT16_SERIALIZATION_ALLOWED

#ifdef INT32_SERIALIZATION_ALLOWED
FlwSt stream_int32_t(stream_ptr_t stream, int32_t value);
FlwSt stream_uint32_t(stream_ptr_t stream, uint32_t value);
#endif // INT32_SERIALIZATION_ALLOWED

#ifdef INT64_SERIALIZATION_ALLOWED
FlwSt stream_int64_t(stream_ptr_t stream, int64_t value);
FlwSt stream_uint64_t(stream_ptr_t stream, uint64_t value);
#endif // INT32_SERIALIZATION_ALLOWED

#ifdef FLOAT_SERIALIZATION_ALLOWED
FlwSt stream_float(stream_ptr_t stream, float value);
#endif // FLOAT_SERIALIZATION_ALLOWED

#ifdef DOUBLE_SERIALIZATION_ALLOWED
FlwSt stream_double(stream_ptr_t stream, double value);
#endif // DOUBLE_SERIALIZATION_ALLOWED

#ifdef BLOB_SERIALIZATION_ALLOWED
FlwSt stream_blob(stream_ptr_t stream, void *data, uint32_t size);
#endif // BLOB_SERIALIZATION_ALLOWED

#ifdef BELOB_SERIALIZATION_ALLOWED
FlwSt stream_belob(stream_ptr_t stream, void *data, uint64_t size);
#endif // BELOB_SERIALIZATION_ALLOWED

#endif // TO_STREAM_SERIALIZER_HEADER
