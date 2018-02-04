
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

// check int8_t exists
#ifndef INT8_MAX
#error "To stream serializer library can not be build, because smalles 8-bit "\
       "type is unsupported on your platform."
#endif // INT8_MAX

typedef void   (*free_ptr_t)     (void *);
typedef void * (*malloc_ptr_t)   (size_t);
typedef void * (*calloc_ptr_t)   (size_t, size_t);
typedef void * (*realloc_ptr_t)  (void *, size_t);

typedef struct
{
	free_ptr_t    pfree;
	malloc_ptr_t  pmalloc;
	calloc_ptr_t  pcalloc;
	realloc_ptr_t prealloc;
} mem_allctr_t;

#define MACRO_DEF_MEM_ALLCTR_INITIALIZER \
{ \
	  .pfree    = &free \
	, .pmalloc  = &malloc \
	, .pcalloc  = &calloc \
	, .prealloc = &realloc }

const static mem_allctr_t
DEF_MEM_ALLCTR = MACRO_DEF_MEM_ALLCTR_INITIALIZER;

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

const static mem_mngr_t
DEF_MEM_MNGR =
{
	  .mem_allctr = MACRO_DEF_MEM_ALLCTR_INITIALIZER
	, .pincrease  = &inc_x2_plus1
};

typedef struct
{
	size_t capacity;
	size_t available;
	size_t max_capacity;
} stream_metha_t;

typedef struct
{
	stream_metha_t metha;
	mem_mngr_t     mem_mngr;
	uint8_t       *mem_ptr;
} stream_t;

#endif // TO_STREAM_SERIALIZER_HEADER
