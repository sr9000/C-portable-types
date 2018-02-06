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

FlwSt
check_stream_consistency(stream_ptr_t stream)
{
	if (stream == NULL)
	{
		return FLW_ST.crashed;
	}
	if (   (*stream).metha.capacity  > (*stream).metha.max_capacity
	    || (*stream).metha.available > (*stream).metha.capacity
	) {
		return FLW_ST.crashed;
	}
	if (   (*stream).metha.capacity > 0
	    && (*stream).mem_ptr == (*stream).mem_mngr.mem_allctr.nullptr_val)
	{
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
	if (   max_capacity  != 0
	    && init_capacity >  max_capacity
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

FlwSt delete_stream(stream_ptr_t *pstream)
{
	if ((*pstream) == NULL)
	{
		return FLW_ST.succeeded;
	}
	if (is_flow_not_succeeded(check_stream_consistency(*pstream)))
	{
		return FLW_ST.crashed;
	}

	if ((**pstream).mem_ptr != (**pstream).mem_mngr.mem_allctr.nullptr_val)
	{
		(*((**pstream).mem_mngr.mem_allctr.pfree))((**pstream).mem_ptr);
	}
	free(*pstream);
	(*pstream) = NULL;
	return FLW_ST.succeeded;
}
