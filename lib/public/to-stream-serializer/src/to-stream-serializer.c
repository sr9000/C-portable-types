#include "to-stream-serializer.h"

#define MACRO_DEF_MEM_ALLCTR_INITIALIZER \
{ \
	  .pfree    = &free \
	, .pmalloc  = &malloc \
	, .pcalloc  = &calloc \
	, .prealloc = &realloc \
  , .nullptr_val = NULL }

const mem_allctr_t
DEF_MEM_ALLCTR = MACRO_DEF_MEM_ALLCTR_INITIALIZER;

const mem_mngr_t
DEF_MEM_MNGR =
{
	  .mem_allctr = MACRO_DEF_MEM_ALLCTR_INITIALIZER
	, .pincrease  = &inc_x2_plus1
};

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

size_t inc_on_one10th(size_t size);
{
	return size + (size / 10) + 100;
}

mem_allctr_t
create_mem_allctr(
	  free_ptr_t    pfree
	, malloc_ptr_t  pmalloc
	, calloc_ptr_t  pcalloc
	, realloc_ptr_t prealloc
) {
	mem_allctr_t r;
	r.pfree       = pfree;
	r.pmalloc     = pmalloc;
	r.pcalloc     = pcalloc;
	r.prealloc    = prealloc;
	r.nullptr_val = NULL;
	return r;
}

mem_allctr_t
create_mem_allctr_ex(
	  free_ptr_t     pfree
	, malloc_ptr_t   pmalloc
	, calloc_ptr_t   pcalloc
	, realloc_ptr_t  prealloc
	, void          *nullptr_val
) {
	mem_allctr_t r;
	r.pfree       = pfree;
	r.pmalloc     = pmalloc;
	r.pcalloc     = pcalloc;
	r.prealloc    = prealloc;
	r.nullptr_val = nullptr_val;
	return r;
}

mem_mngr_t
create_mem_mngr(
	  mem_allctr_t   allctr
	, increase_ptr_t pincrease
) {
	mem_mngr_t r;
	r.mem_allctr = allctr;
	r.pincrease  = pincrease;
	return r;
}

mem_mngr_t
create_mem_mngr_ex(
	  free_ptr_t     pfree
	, malloc_ptr_t   pmalloc
	, calloc_ptr_t   pcalloc
	, realloc_ptr_t  prealloc
	, void          *nullptr_val
	, increase_ptr_t pincrease
) {
	mem_mngr_t r;
	r.mem_allctr =
		create_mem_allctr_ex(
			  pfree
			, pmalloc
			, pcalloc
			, prealloc
			, nullptr_val
		);
	r.pincrease = pincrease;
	return r;
}

#define STREAM_NOT_NULL_ELSE_CRASHED(stream) \
if ((stream) == NULL) \
{ \
	return FLW_ST.crashed; \
}

uint8_t*
get_current_stream_addres(stream_ptr_t stream)
{
	return
		  ((uint8_t*)((*stream).mem_ptr))
		+ (*stream).metha.capacity
		- (*stream).metha.available;
}

FlwSt
check_stream_consistency(stream_ptr_t stream)
{
	STREAM_NOT_NULL_ELSE_CRASHED(stream);
	if (   (   (*stream).metha.max_capacity > 0
	        && (*stream).metha.max_capacity < (*stream).metha.capacity)
	    || (*stream).metha.available > (*stream).metha.capacity
	) {
		return FLW_ST.crashed;
	}

	void *null_ptr_val = (*stream).mem_mngr.mem_allctr.nullptr_val;
	uint8_t *computed_free_mem_ptr = get_current_stream_addres(stream);
	if (   (*stream).metha.capacity > 0
	    && (   (*stream).mem_ptr      == null_ptr_val
	        || (*stream).free_mem_ptr == null_ptr_val
	        || (*stream).free_mem_ptr != computed_free_mem_ptr)
	) {
		return FLW_ST.crashed;
	}

	return FLW_ST.succeeded;
}

FlwSt
new_stream(
	  stream_ptr_t *pstream
	, mem_mngr_t mngr
	, size_t max_capacity
	, size_t init_capacity
) {
	if (   max_capacity != 0
	    && max_capacity <  init_capacity
	) {
		return FLW_ST.failed;
	}

	(*pstream) = malloc(sizeof(struct struct_stream));

	if ((*pstream) == NULL)
	{
		return FLW_ST.failed;
	}

	(**pstream).mem_mngr = mngr;
	(**pstream).mem_ptr =
		(uint8_t*)
		((*(mngr.mem_allctr.pmalloc))(init_capacity * sizeof(uint8_t)));

	if ((**pstream).mem_ptr == (**pstream).mem_mngr.mem_allctr.nullptr_val)
	{
		free(*pstream);
		return FLW_ST.failed;
	}

	(**pstream).metha.max_capacity = max_capacity;
	(**pstream).metha.capacity = init_capacity;
	(**pstream).metha.available = (**pstream).metha.capacity;
	(**pstream).free_mem_ptr = (**pstream).mem_ptr;

	return FLW_ST.succeeded;
}

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
) {
	return
		new_stream(
			  pstream
			, create_mem_mngr_ex(
					  pfree
					, pmalloc
					, pcalloc
					, prealloc
					, nullptr_val
					, pincrease
				)
			, max_capacity
			, init_capacity
		);
}

#define STREAM_CONSISTENT_ELSE_CRASHED(stream) \
if (is_flow_not_succeeded(check_stream_consistency(stream))) \
{ \
	return FLW_ST.crashed; \
}

FlwSt delete_stream(stream_ptr_t *pstream)
{
	if ((*pstream) == NULL)
	{
		return FLW_ST.succeeded;
	}

	STREAM_CONSISTENT_ELSE_CRASHED(*pstream);

	if ((**pstream).mem_ptr != (**pstream).mem_mngr.mem_allctr.nullptr_val)
	{
		(*((**pstream).mem_mngr.mem_allctr.pfree))((**pstream).mem_ptr);
	}
	free(*pstream);
	(*pstream) = NULL;
	return FLW_ST.succeeded;
}

FlwSt
request_stream_size(stream_ptr_t stream, size_t size)
{
	STREAM_NOT_NULL_ELSE_CRASHED(stream);
	// check available space
	if ((*stream).metha.available >= size)
	{
		return FLW_ST.succeeded;
	}
	// calculate target size
	size_t needed_capacity =
		size
		- (*stream).metha.available
		+ (*stream).metha.capacity;
	// check constraints with max_capacity
	if (   (*stream).metha.max_capacity > 0
	    && (*stream).metha.max_capacity < needed_capacity
	) {
		return FLW_ST.failed;
	}
	// calculate new capacity using increase function
	size_t new_capacity = (*stream).metha.capacity;
	while (new_capacity < needed_capacity)
	{
		size_t tmp = (*((*stream).mem_mngr.pincrease))(new_capacity);
		if (tmp < new_capacity)
		{
			// if increase function fails, use max_capacity or needed_capacity
			// if max_capacity is unlimited
			if ((*stream).metha.max_capacity > 0)
			{
				new_capacity = (*stream).metha.max_capacity;
			}
			else
			{
				new_capacity = needed_capacity;
			}
			break;
		}
		new_capacity = tmp;
	}
	// check new capacity are greater than 0
	if (new_capacity <= 0)
	{
		return FLW_ST.failed;
	}
	// try to realloc
	void *new_mem_ptr =
		(*((*stream).mem_mngr.mem_allctr.prealloc))(
			  (*stream).mem_ptr
			, new_capacity * sizeof(uint8_t)
		);

	if (new_mem_ptr == (*stream).mem_mngr.mem_allctr.nullptr_val)
	{
		return FLW_ST.failed;
	}

	// update mem_ptr and metha
	(*stream).mem_ptr = (uint8_t*) new_mem_ptr;
	(*stream).metha.available += new_capacity - (*stream).metha.capacity;
	(*stream).metha.capacity = new_capacity;
	(*stream).free_mem_ptr = get_current_stream_addres(stream);

	return FLW_ST.succeeded;
}

#define REQUEST_STREAM_SIZE_ELSE_RETURN(stream, size) \
{ \
	FlwSt st = request_stream_size((stream), (size)); \
	if (is_flow_not_succeeded(st)) \
	{ \
		return st; \
	} \
}

#define SERIALIZE(stream, serialize_function, value) \
{ \
	uint8_t *old_free_mem_ptr = (*(stream)).free_mem_ptr; \
	(*(stream)).free_mem_ptr = (serialize_function)(old_free_mem_ptr, (value)); \
	(*(stream)).metha.available -= \
		((*(stream)).free_mem_ptr - old_free_mem_ptr); \
}

#define SERIALIZE_WITH_ARG(stream, serialize_function, value, argument) \
{ \
	uint8_t *old_free_mem_ptr = (*(stream)).free_mem_ptr; \
	(*(stream)).free_mem_ptr = \
		(serialize_function)(old_free_mem_ptr, (value), (argument)); \
	(*(stream)).metha.available -= \
		((*(stream)).free_mem_ptr - old_free_mem_ptr); \
}

#ifdef INT8_SERIALIZATION_ALLOWED
FlwSt stream_int8_t(stream_ptr_t stream, int8_t value)
{
	STREAM_NOT_NULL_ELSE_CRASHED(stream);
	STREAM_CONSISTENT_ELSE_CRASHED(stream);
	REQUEST_STREAM_SIZE_ELSE_RETURN(stream, 1);
	SERIALIZE(stream, serialize_int8_t, value);
	return FLW_ST.succeeded;
}
FlwSt stream_uint8_t(stream_ptr_t stream, uint8_t value)
{
	STREAM_NOT_NULL_ELSE_CRASHED(stream);
	STREAM_CONSISTENT_ELSE_CRASHED(stream);
	REQUEST_STREAM_SIZE_ELSE_RETURN(stream, 1);
	SERIALIZE(stream, serialize_uint8_t, value);
	return FLW_ST.succeeded;
}
#endif // INT8_SERIALIZATION_ALLOWED

#ifdef INT16_SERIALIZATION_ALLOWED
FlwSt stream_int16_t(stream_ptr_t stream, int16_t value)
{
	STREAM_NOT_NULL_ELSE_CRASHED(stream);
	STREAM_CONSISTENT_ELSE_CRASHED(stream);
	REQUEST_STREAM_SIZE_ELSE_RETURN(stream, 2);
	SERIALIZE(stream, serialize_int16_t, value);
	return FLW_ST.succeeded;
}
FlwSt stream_uint16_t(stream_ptr_t stream, uint16_t value)
{
	STREAM_NOT_NULL_ELSE_CRASHED(stream);
	STREAM_CONSISTENT_ELSE_CRASHED(stream);
	REQUEST_STREAM_SIZE_ELSE_RETURN(stream, 2);
	SERIALIZE(stream, serialize_uint16_t, value);
	return FLW_ST.succeeded;
}
#endif // INT16_SERIALIZATION_ALLOWED

#ifdef INT32_SERIALIZATION_ALLOWED
FlwSt stream_int32_t(stream_ptr_t stream, int32_t value)
{
	STREAM_NOT_NULL_ELSE_CRASHED(stream);
	STREAM_CONSISTENT_ELSE_CRASHED(stream);
	REQUEST_STREAM_SIZE_ELSE_RETURN(stream, 4);
	SERIALIZE(stream, serialize_int32_t, value);
	return FLW_ST.succeeded;
}
FlwSt stream_uint32_t(stream_ptr_t stream, uint32_t value)
{
	STREAM_NOT_NULL_ELSE_CRASHED(stream);
	STREAM_CONSISTENT_ELSE_CRASHED(stream);
	REQUEST_STREAM_SIZE_ELSE_RETURN(stream, 4);
	SERIALIZE(stream, serialize_uint32_t, value);
	return FLW_ST.succeeded;
}
#endif // INT32_SERIALIZATION_ALLOWED

#ifdef INT64_SERIALIZATION_ALLOWED
FlwSt stream_int64_t(stream_ptr_t stream, int64_t value)
{
	STREAM_NOT_NULL_ELSE_CRASHED(stream);
	STREAM_CONSISTENT_ELSE_CRASHED(stream);
	REQUEST_STREAM_SIZE_ELSE_RETURN(stream, 8);
	SERIALIZE(stream, serialize_int64_t, value);
	return FLW_ST.succeeded;
}
FlwSt stream_uint64_t(stream_ptr_t stream, uint64_t value)
{
	STREAM_NOT_NULL_ELSE_CRASHED(stream);
	STREAM_CONSISTENT_ELSE_CRASHED(stream);
	REQUEST_STREAM_SIZE_ELSE_RETURN(stream, 8);
	SERIALIZE(stream, serialize_uint64_t, value);
	return FLW_ST.succeeded;
}
#endif // INT32_SERIALIZATION_ALLOWED

#ifdef FLOAT_SERIALIZATION_ALLOWED
FlwSt stream_float(stream_ptr_t stream, float value)
{
	STREAM_NOT_NULL_ELSE_CRASHED(stream);
	STREAM_CONSISTENT_ELSE_CRASHED(stream);
	REQUEST_STREAM_SIZE_ELSE_RETURN(stream, SIZE_OF_SERIALIZED_FLOAT);
	SERIALIZE(stream, serialize_float, value);
	return FLW_ST.succeeded;
}
#endif // FLOAT_SERIALIZATION_ALLOWED

#ifdef DOUBLE_SERIALIZATION_ALLOWED
FlwSt stream_double(stream_ptr_t stream, double value)
{
	STREAM_NOT_NULL_ELSE_CRASHED(stream);
	STREAM_CONSISTENT_ELSE_CRASHED(stream);
	REQUEST_STREAM_SIZE_ELSE_RETURN(stream, SIZE_OF_SERIALIZED_DOUBLE);
	SERIALIZE(stream, serialize_double, value);
	return FLW_ST.succeeded;
}
#endif // DOUBLE_SERIALIZATION_ALLOWED

#ifdef BLOB_SERIALIZATION_ALLOWED
FlwSt stream_blob(stream_ptr_t stream, void *data, uint32_t size)
{
	STREAM_NOT_NULL_ELSE_CRASHED(stream);
	STREAM_CONSISTENT_ELSE_CRASHED(stream);
	size_t rsize = 4 + size;
	if (rsize < size)
	{
		return FLW_ST.failed;
	}
	REQUEST_STREAM_SIZE_ELSE_RETURN(stream, rsize);
	SERIALIZE_WITH_ARG(stream, serialize_blob, data, size);
	return FLW_ST.succeeded;
}
#endif // BLOB_SERIALIZATION_ALLOWED

#ifdef BELOB_SERIALIZATION_ALLOWED
FlwSt stream_belob(stream_ptr_t stream, void *data, uint64_t size)
{
	STREAM_NOT_NULL_ELSE_CRASHED(stream);
	STREAM_CONSISTENT_ELSE_CRASHED(stream);
	size_t rsize = 8 + size;
	if (rsize < size)
	{
		return FLW_ST.failed;
	}
	REQUEST_STREAM_SIZE_ELSE_RETURN(stream, rsize);
	SERIALIZE_WITH_ARG(stream, serialize_belob, data, size);
	return FLW_ST.succeeded;
}
#endif // BELOB_SERIALIZATION_ALLOWED
