
/**
 * @file to-stream-serializer.h
 * @author Rogonov Stepan Alekseevich
 * @brief File containing definitions of serialization functions into
 * autoscalable binary stream.
 * @details Defines serialization and deserialization functions that used in
 * combination with autoscalable binary stream. Comfort highlevel programming
 * with maximum control of serialization process.
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

/*!
 * @typedef free_ptr_t
 * @brief Pointer onto \c free function.
 * @details Pointer onto \c free function used in \em memory \em manager to
 * make memory control more flexible.
 */
typedef void (*free_ptr_t) (void *);

/*!
 * @typedef malloc_ptr_t
 * @brief Pointer onto \c malloc function.
 * @details Pointer onto \c malloc function used in \em memory \em manager to
 * make memory control more flexible.
 */
typedef void * (*malloc_ptr_t) (size_t);

/*!
 * @typedef calloc_ptr_t
 * @brief Pointer onto \c calloc function.
 * @details Pointer onto \c calloc function used in \em memory \em manager to
 * make memory control more flexible.
 */
typedef void * (*calloc_ptr_t) (size_t, size_t);

/*!
 * @typedef realloc_ptr_t
 * @brief Pointer onto \c realloc function.
 * @details Pointer onto \c realloc function used in \em memory \em manager to
 * make memory control more flexible.
 */
typedef void * (*realloc_ptr_t) (void *, size_t);

/*!
 * @typedef mem_allctr_t
 * @brief \em Memory \em allocator type.
 * @details \em Memory \em allocator type include all memory control function:
 * \c free, \c malloc, \c calloc and \c realloc. Also that type includes \em
 * null \em pointer special value, that should be interpret by memory control
 * functions as unallocated memory.
 */
typedef struct
{
	free_ptr_t    pfree;    //!< Pointer onto \c free function.
	malloc_ptr_t  pmalloc;  //!< Pointer onto \c malloc function.
	calloc_ptr_t  pcalloc;  //!< Pointer onto \c calloc function.
	realloc_ptr_t prealloc; //!< Pointer onto \c realloc function.
	void* nullptr_val;      //!< \em Null \em pointer special value.
} mem_allctr_t;

/*!
 * @var DEF_MEM_ALLCTR
 * @brief \em Memory \em allocator with standard \c C memory control functions.
 * @details \em Memory \em allocator \c DEF_MEM_ALLCTR should be used instead
 * calling \ref create_mem_allctr or \ref create_mem_allctr_ex function with
 * standard \c C memory control functions.
 */
const extern mem_allctr_t DEF_MEM_ALLCTR;

/*!
 * @typedef increase_ptr_t
 * @brief Pointer onto function, that gets new stream capacity, based on
 * previous capacity value.
 * @details You can and (if you need) you should use your custom increase
 * functions, that fits your \em special conditions or complex behaviour. That
 * type of function used by functions, that manage \ref stream_ptr_t.
 */
typedef size_t (*increase_ptr_t) (size_t);

/*!
 * @brief Increase stream capacity by 32.
 * @param [in] size Previous stream capacity value.
 * @return Previous stream capacity value inscreased by 32.
 */
size_t inc_plus32(size_t size);

/*!
 * @brief Increase stream capacity by 4096.
 * @param [in] size Previous stream capacity value.
 * @return Previous stream capacity value inscreased by 4096.
 */
size_t inc_plus4k(size_t size);

/*!
 * @brief Increase stream capacity by 16384.
 * @param [in] size Previous stream capacity value.
 * @return Previous stream capacity value inscreased by 16384.
 */
size_t inc_plus16k(size_t size);

/*!
 * @brief Double stream capacity.
 * @param [in] size Previous stream capacity value.
 * @details To avoid stuck on zero size that functions add 1 after multiplying
 * by 2.
 * @return Previous stream capacity value multiplied by 2.
 */
size_t inc_x2_plus1(size_t size);

/*!
 * @brief Add one tenth of current stream capacity.
 * @param [in] size Previous stream capacity value.
 * @details To avoid stuck on low sizes that functions add 100 after
 * multiplying by 1.1 .
 * @return Previous stream capacity value increased by one tenth of stream
 * capacity.
 */
size_t inc_on_one10th(size_t size);

/*!
 * @typedef mem_mngr_t
 * @brief \em Memory \em manager. It can allocates and frees memory, assings
 * new stream size.
 * @details Functionally equivalent to \ref mem_allctr_t except possibility of
 * assigning new sizes based on previous stream size.
 */
typedef struct
{
	mem_allctr_t mem_allctr;  //!< \em Memory \em allocator
	increase_ptr_t pincrease; //!< Size increasing function
} mem_mngr_t;

/*!
 * @var DEF_MEM_MNGR
 * @brief \em Memory \em manager with standard \c C memory control functions
 * and \ref inc_x2_plus1 as increase finction.
 * @details \em Memory \em manager \c DEF_MEM_MNGR should be used instead
 * calling \ref create_mem_mngr_ex function with standard \c C memory control
 * and increase functions.
 */
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

/*!
 * @brief Function to create custom \em memory \em allocators.
 * @param [in] pfree    Pointer onto \c free function.
 * @param [in] pmalloc  Pointer onto \c malloc function.
 * @param [in] pcalloc  Pointer onto \c calloc function.
 * @param [in] prealloc Pointer onto \c realloc function.
 * @return Filled \ref mem_allctr_t value with pointed functions as memory
 * control functions and \c NULL as \em null \em pointer special value.
 */
mem_allctr_t
create_mem_allctr(
	  free_ptr_t    pfree
	, malloc_ptr_t  pmalloc
	, calloc_ptr_t  pcalloc
	, realloc_ptr_t prealloc
);

/*!
 * @brief Function to create custom \em memory \em allocators with nonstandard
 * \em null \em pointer special value.
 * @param [in] pfree       Pointer onto \c free function.
 * @param [in] pmalloc     Pointer onto \c malloc function.
 * @param [in] pcalloc     Pointer onto \c calloc function.
 * @param [in] prealloc    Pointer onto \c realloc function.
 * @param [in] nullptr_val \em Null \em pointer special value
 * @return Filled \ref mem_allctr_t value with pointed functions as memory
 * control functions and \p nullptr_val as \em null \em pointer special value.
 */
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

size_t get_stream_size(stream_ptr_t *pstream);
void*  get_stream_content_pointer(stream_ptr_t *pstream);

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
