#include <stdio.h>
#include <stdlib.h>

#include "test.h"
#include "to-stream-serializer.h"
#include "internal-definitions/to-stream-serializer.h"

NEW_TEST(constants_check)
	// check DEF_MEM_ALLCTR
	if (   DEF_MEM_ALLCTR.pfree       != &free
	    || DEF_MEM_ALLCTR.pmalloc     != &malloc
	    || DEF_MEM_ALLCTR.pcalloc     != &calloc
	    || DEF_MEM_ALLCTR.prealloc    != &realloc
	    || DEF_MEM_ALLCTR.nullptr_val != NULL
	) {
		TEST_FAILURE;
	}
	// check DEF_MEM_MNGR
	if (   DEF_MEM_MNGR.mem_allctr.pfree       != &free
	    || DEF_MEM_MNGR.mem_allctr.pmalloc     != &malloc
	    || DEF_MEM_MNGR.mem_allctr.pcalloc     != &calloc
	    || DEF_MEM_MNGR.mem_allctr.prealloc    != &realloc
	    || DEF_MEM_MNGR.mem_allctr.nullptr_val != NULL
	    || DEF_MEM_MNGR.pincrease != &inc_x2_plus1
	) {
		TEST_FAILURE;
	}
TEST_FINISHED

NEW_TEST(increase_functions_check)
	size_t zero = 0;
	size_t one = 1;
	size_t thousand = 1000;
	// inc_plus32
	if (   inc_plus32(zero)     != 32
	    || inc_plus32(one)      != 33
	    || inc_plus32(thousand) != 1032
	) {
		TEST_FAILURE;
	}
	// inc_plus4k
	if (   inc_plus4k(zero)     != 4096
	    || inc_plus4k(one)      != 4097
	    || inc_plus4k(thousand) != 5096
	) {
		TEST_FAILURE;
	}
	// inc_plus16k
	if (   inc_plus16k(zero)     != 16384
	    || inc_plus16k(one)      != 16385
	    || inc_plus16k(thousand) != 17384
	) {
		TEST_FAILURE;
	}
	// inc_x2_plus1
	if (   inc_x2_plus1(zero)     != 1
	    || inc_x2_plus1(one)      != 3
	    || inc_x2_plus1(thousand) != 2001
	) {
		TEST_FAILURE;
	}
	// inc_x2_plus1
	if (   inc_on_one10th(zero)     != 100
	    || inc_on_one10th(one)      != 101
	    || inc_on_one10th(thousand) != 1200
	) {
		TEST_FAILURE;
	}
TEST_FINISHED

NEW_TEST(creating_functions_check)
	void *p1, *p2, *p3, *p4, *p5, *p6;
	p1 = (void *) 1;
	p2 = (void *) 2;
	p3 = (void *) 3;
	p4 = (void *) 4;
	p5 = (void *) 5;
	p6 = (void *) 6;
	// create_mem_allctr
	mem_allctr_t mem_allctr;
	mem_allctr = create_mem_allctr(p1, p2, p3, p4);
	if (   mem_allctr.pfree       != p1
	    || mem_allctr.pmalloc     != p2
	    || mem_allctr.pcalloc     != p3
	    || mem_allctr.prealloc    != p4
	    || mem_allctr.nullptr_val != NULL
	) {
		TEST_FAILURE;
	}
	mem_allctr = create_mem_allctr_ex(p1, p2, p3, p4, p5);
	if (   mem_allctr.pfree       != p1
	    || mem_allctr.pmalloc     != p2
	    || mem_allctr.pcalloc     != p3
	    || mem_allctr.prealloc    != p4
	    || mem_allctr.nullptr_val != p5
	) {
		TEST_FAILURE;
	}
	// create_mem_mngr
	mem_mngr_t mem_mngr;
	mem_mngr = create_mem_mngr(mem_allctr, p6);
	if (   mem_mngr.mem_allctr.pfree       != p1
	    || mem_mngr.mem_allctr.pmalloc     != p2
	    || mem_mngr.mem_allctr.pcalloc     != p3
	    || mem_mngr.mem_allctr.prealloc    != p4
	    || mem_mngr.mem_allctr.nullptr_val != p5
	    || mem_mngr.pincrease != p6
	) {
		TEST_FAILURE;
	}
	mem_mngr = create_mem_mngr_ex(p1, p2, p3, p4, p5, p6);
	if (   mem_mngr.mem_allctr.pfree       != p1
	    || mem_mngr.mem_allctr.pmalloc     != p2
	    || mem_mngr.mem_allctr.pcalloc     != p3
	    || mem_mngr.mem_allctr.prealloc    != p4
	    || mem_mngr.mem_allctr.nullptr_val != p5
	    || mem_mngr.pincrease != p6
	) {
		TEST_FAILURE;
	}
TEST_FINISHED

NEW_TEST(new_stream_check)
	stream_ptr_t stream;
	FlwSt st;
	// new_stream
	st = new_stream(&stream, DEF_MEM_MNGR, 0, 0);
	if (is_flow_not_succeeded(st))
	{
		TEST_FAILURE;
	}
	// delete_stream
	st = delete_stream(&stream);
	if (is_flow_not_succeeded(st))
	{
		TEST_FAILURE;
	}
	// new_stream_ex
	st = new_stream_ex(
		  &stream
		, &free
		, &malloc
		, &calloc
		, &realloc
		, NULL
		, &inc_x2_plus1
		, 0
		, 0
	);
	if (is_flow_not_succeeded(st))
	{
		TEST_FAILURE;
	}
	// delete_stream
	st = delete_stream(&stream);
	if (is_flow_not_succeeded(st))
	{
		TEST_FAILURE;
	}
TEST_FINISHED

NEW_TEST(stream_consistency_check)
	FlwSt st;
	stream_ptr_t stream;
	uint8_t mem[10 * sizeof(uint8_t)];
	void *non_null_ptr = &mem[0];
	// NULL stream
	stream = NULL;
	st = check_stream_consistency(stream);
	if (!is_flow_failed(st))
	{
		TEST_FAILURE;
	}
	// define stream
	struct struct_stream real_stream;
	real_stream.free_mem_ptr = non_null_ptr;
	real_stream.mem_ptr      = non_null_ptr;
	real_stream.mem_mngr     = DEF_MEM_MNGR;
	real_stream.metha.available    = 100;
	real_stream.metha.capacity     = 100;
	real_stream.metha.max_capacity = 0;
	stream = &real_stream;
	// available larger than capacity
	real_stream.metha.available = 100;
	real_stream.metha.capacity  = 99;
	st = check_stream_consistency(stream);
	if (!is_flow_crashed(st))
	{
		TEST_FAILURE;
	}
	// non zero max capacity less than capacity
	real_stream.metha.capacity     = 100;
	real_stream.metha.max_capacity = 99;
	st = check_stream_consistency(stream);
	if (!is_flow_crashed(st))
	{
		TEST_FAILURE;
	}
	// memory pointers
	real_stream.mem_ptr         = &mem[0];
	real_stream.free_mem_ptr    = &mem[3 * sizeof(uint8_t)];
	real_stream.metha.available = 6;
	real_stream.metha.capacity  = 10;
	st = check_stream_consistency(stream);
	if (!is_flow_crashed(st))
	{
		TEST_FAILURE;
	}
	real_stream.metha.available = 8;
	st = check_stream_consistency(stream);
	if (!is_flow_crashed(st))
	{
		TEST_FAILURE;
	}
	real_stream.metha.available = 7;
	real_stream.mem_ptr = NULL;
	st = check_stream_consistency(stream);
	if (!is_flow_crashed(st))
	{
		TEST_FAILURE;
	}
	real_stream.mem_ptr      = &mem[0];
	real_stream.free_mem_ptr = NULL;
	st = check_stream_consistency(stream);
	if (!is_flow_crashed(st))
	{
		TEST_FAILURE;
	}
	// successful consistency
	// zero capacity, null ptrs
	real_stream.free_mem_ptr = NULL;
	real_stream.mem_ptr      = NULL;
	real_stream.mem_mngr     = DEF_MEM_MNGR;
	real_stream.metha.available    = 0;
	real_stream.metha.capacity     = 0;
	real_stream.metha.max_capacity = 0;
	st = check_stream_consistency(stream);
	if (is_flow_not_succeeded(st))
	{
		TEST_FAILURE;
	}
	// zero capacity, null ptrs, non zero max capacity
	real_stream.free_mem_ptr = NULL;
	real_stream.mem_ptr      = NULL;
	real_stream.mem_mngr     = DEF_MEM_MNGR;
	real_stream.metha.available    = 0;
	real_stream.metha.capacity     = 0;
	real_stream.metha.max_capacity = 100;
	st = check_stream_consistency(stream);
	if (is_flow_not_succeeded(st))
	{
		TEST_FAILURE;
	}
	// capacity == availabble, freeptr==memptr
	real_stream.free_mem_ptr = non_null_ptr;
	real_stream.mem_ptr      = non_null_ptr;
	real_stream.mem_mngr     = DEF_MEM_MNGR;
	real_stream.metha.available    = 1;
	real_stream.metha.capacity     = 1;
	real_stream.metha.max_capacity = 0;
	st = check_stream_consistency(stream);
	if (is_flow_not_succeeded(st))
	{
		TEST_FAILURE;
	}
	// capacity == availabble, freeptr==memptr
	real_stream.free_mem_ptr = non_null_ptr;
	real_stream.mem_ptr      = non_null_ptr;
	real_stream.mem_mngr     = DEF_MEM_MNGR;
	real_stream.metha.available    = 100;
	real_stream.metha.capacity     = 100;
	real_stream.metha.max_capacity = 0;
	st = check_stream_consistency(stream);
	if (is_flow_not_succeeded(st))
	{
		TEST_FAILURE;
	}
	// non zero max capacity == capacity == availabble, freeptr==memptr
	real_stream.free_mem_ptr = non_null_ptr;
	real_stream.mem_ptr      = non_null_ptr;
	real_stream.mem_mngr     = DEF_MEM_MNGR;
	real_stream.metha.available    = 100;
	real_stream.metha.capacity     = 100;
	real_stream.metha.max_capacity = 100;
	st = check_stream_consistency(stream);
	if (is_flow_not_succeeded(st))
	{
		TEST_FAILURE;
	}
	// non zero max capacity != capacity == availabble, freeptr==memptr
	real_stream.free_mem_ptr = non_null_ptr;
	real_stream.mem_ptr      = non_null_ptr;
	real_stream.mem_mngr     = DEF_MEM_MNGR;
	real_stream.metha.available    = 100;
	real_stream.metha.capacity     = 100;
	real_stream.metha.max_capacity = 101;
	st = check_stream_consistency(stream);
	if (is_flow_not_succeeded(st))
	{
		TEST_FAILURE;
	}
	// non zero max capacity != capacity == availabble, freeptr==memptr
	real_stream.free_mem_ptr = non_null_ptr;
	real_stream.mem_ptr      = non_null_ptr;
	real_stream.mem_mngr     = DEF_MEM_MNGR;
	real_stream.metha.available    = 100;
	real_stream.metha.capacity     = 100;
	real_stream.metha.max_capacity = 900;
	st = check_stream_consistency(stream);
	if (is_flow_not_succeeded(st))
	{
		TEST_FAILURE;
	}
	// non zero max capacity != capacity != availabble, freeptr==memptr
	real_stream.free_mem_ptr = &mem[1 * sizeof(uint8_t)];
	real_stream.mem_ptr      = &mem[0];
	real_stream.mem_mngr     = DEF_MEM_MNGR;
	real_stream.metha.available    = 9;
	real_stream.metha.capacity     = 10;
	real_stream.metha.max_capacity = 100;
	st = check_stream_consistency(stream);
	if (is_flow_not_succeeded(st))
	{
		TEST_FAILURE;
	}
	// non zero max capacity != capacity != availabble, freeptr==memptr
	real_stream.free_mem_ptr = &mem[4 * sizeof(uint8_t)];
	real_stream.mem_ptr      = &mem[0];
	real_stream.mem_mngr     = DEF_MEM_MNGR;
	real_stream.metha.available    = 6;
	real_stream.metha.capacity     = 10;
	real_stream.metha.max_capacity = 100;
	st = check_stream_consistency(stream);
	if (is_flow_not_succeeded(st))
	{
		TEST_FAILURE;
	}
	// zero max capacity != capacity != availabble, freeptr==memptr
	real_stream.free_mem_ptr = &mem[4 * sizeof(uint8_t)];
	real_stream.mem_ptr      = &mem[0];
	real_stream.mem_mngr     = DEF_MEM_MNGR;
	real_stream.metha.available    = 6;
	real_stream.metha.capacity     = 10;
	real_stream.metha.max_capacity = 0;
	st = check_stream_consistency(stream);
	if (is_flow_not_succeeded(st))
	{
		TEST_FAILURE;
	}
	// non zero max capacity != capacity != zero availabble, freeptr==memptr
	real_stream.free_mem_ptr = &mem[10 * sizeof(uint8_t)];
	real_stream.mem_ptr      = &mem[0];
	real_stream.mem_mngr     = DEF_MEM_MNGR;
	real_stream.metha.available    = 0;
	real_stream.metha.capacity     = 10;
	real_stream.metha.max_capacity = 0;
	st = check_stream_consistency(stream);
	if (is_flow_not_succeeded(st))
	{
		TEST_FAILURE;
	}
TEST_FINISHED

NEW_TEST(stream_request_size)
	FlwSt st;
	struct struct_stream real_stream;
	stream_ptr_t stream = &real_stream;
	real_stream.mem_ptr  = NULL;
	real_stream.mem_mngr = DEF_MEM_MNGR;
	real_stream.metha.max_capacity = 0;
	// available enough
	real_stream.free_mem_ptr    = NULL;
	real_stream.metha.available = 10;
	real_stream.metha.capacity  = 10;
	st = request_stream_size(stream, 5);
	if (   is_flow_not_succeeded(st)
	    || real_stream.metha.capacity  != 10
	    || real_stream.metha.available != 10
	) {
		TEST_FAILURE;
	}
	// still enough
	st = request_stream_size(stream, 10);
	if (   is_flow_not_succeeded(st)
	    || real_stream.metha.capacity  != 10
	    || real_stream.metha.available != 10
	) {
		TEST_FAILURE;
	}
	// failed cause max capacity
	real_stream.metha.max_capacity = 15;
	real_stream.metha.available    = 10;
	real_stream.metha.capacity     = 10;
	st = request_stream_size(stream, 16);
	if (!is_flow_failed(st))
	{
		TEST_FAILURE;
	}
	real_stream.metha.max_capacity = 10;
	real_stream.metha.available    = 10;
	real_stream.metha.capacity     = 10;
	st = request_stream_size(stream, 11);
	if (!is_flow_failed(st))
	{
		TEST_FAILURE;
	}
	// failed cause max capacity, available != capacity
	real_stream.metha.max_capacity = 10;
	real_stream.metha.available    = 9;
	real_stream.metha.capacity     = 10;
	st = request_stream_size(stream, 10);
	if (!is_flow_failed(st))
	{
		TEST_FAILURE;
	}
	real_stream.metha.max_capacity = 10;
	real_stream.metha.available    = 1;
	real_stream.metha.capacity     = 10;
	st = request_stream_size(stream, 2);
	if (!is_flow_failed(st))
	{
		TEST_FAILURE;
	}
	real_stream.metha.max_capacity = 12;
	real_stream.metha.available    = 0;
	real_stream.metha.capacity     = 10;
	st = request_stream_size(stream, 3);
	if (!is_flow_failed(st))
	{
		TEST_FAILURE;
	}
TEST_FINISHED

NEW_TEST(stream_request_size_with_real_memory)
	FlwSt st;
	struct struct_stream real_stream;
	stream_ptr_t stream = &real_stream;
	// successful realloc with limit
	void *pmem = malloc(10 * sizeof(uint8_t));
	real_stream.free_mem_ptr = (void *) (((uint8_t *) pmem) + 3);
	real_stream.mem_ptr      = pmem;
	real_stream.mem_mngr     = DEF_MEM_MNGR;
	real_stream.metha.available    = 7;
	real_stream.metha.capacity     = 10;
	real_stream.metha.max_capacity = 13;
	st = request_stream_size(stream, 10);
	if (   is_flow_not_succeeded(st)
	    || real_stream.metha.capacity  != 13
	    || real_stream.metha.available != 10
	) {
		TEST_FAILURE;
	}
	free(real_stream.mem_ptr);
	// successful realloc with far limit
	pmem = malloc(10 * sizeof(uint8_t));
	real_stream.free_mem_ptr = (void *) (((uint8_t *) pmem) + 3);
	real_stream.mem_ptr      = pmem;
	real_stream.mem_mngr     = DEF_MEM_MNGR;
	real_stream.metha.available    = 7;
	real_stream.metha.capacity     = 10;
	real_stream.metha.max_capacity = 22;
	st = request_stream_size(stream, 10);
	if (   is_flow_not_succeeded(st)
	    || real_stream.metha.capacity  != 21
	    || real_stream.metha.available != 18
	) {
		TEST_FAILURE;
	}
	free(real_stream.mem_ptr);
	// successful realloc with so far limit
	pmem = malloc(10 * sizeof(uint8_t));
	real_stream.free_mem_ptr = (void *) (((uint8_t *) pmem) + 3);
	real_stream.mem_ptr      = pmem;
	real_stream.mem_mngr     = DEF_MEM_MNGR;
	real_stream.metha.available    = 7;
	real_stream.metha.capacity     = 10;
	real_stream.metha.max_capacity = 1000;
	st = request_stream_size(stream, 10);
	if (   is_flow_not_succeeded(st)
	    || real_stream.metha.capacity  != 21
	    || real_stream.metha.available != 18
	) {
		TEST_FAILURE;
	}
	free(real_stream.mem_ptr);
	// successful realloc without limit
	pmem = malloc(10 * sizeof(uint8_t));
	real_stream.free_mem_ptr = (void *) (((uint8_t *) pmem) + 3);
	real_stream.mem_ptr      = pmem;
	real_stream.mem_mngr     = DEF_MEM_MNGR;
	real_stream.metha.available    = 7;
	real_stream.metha.capacity     = 10;
	real_stream.metha.max_capacity = 0;
	st = request_stream_size(stream, 10);
	if (   is_flow_not_succeeded(st)
	    || real_stream.metha.capacity  != 21
	    || real_stream.metha.available != 18
	) {
		TEST_FAILURE;
	}
	free(real_stream.mem_ptr);
	// one 10th increment
	pmem = malloc(10 * sizeof(uint8_t));
	real_stream.free_mem_ptr = (void *) (((uint8_t *) pmem) + 3);
	real_stream.mem_ptr      = pmem;
	real_stream.mem_mngr     = DEF_MEM_MNGR;
	real_stream.mem_mngr.pincrease = &inc_on_one10th;
	real_stream.metha.available    = 7;
	real_stream.metha.capacity     = 10;
	real_stream.metha.max_capacity = 9903;
	st = request_stream_size(stream, 9000);
	if (   is_flow_not_succeeded(st)
	    || real_stream.metha.capacity  != 9903
	    || real_stream.metha.available != 9900
		) {
		TEST_FAILURE;
	}
	free(real_stream.mem_ptr);
TEST_FINISHED

NEW_TEST(to_stream_serialize_int8)
	stream_ptr_t stream;
	FlwSt st;
	int8_t val = -97;

	size_t max_capacity  = 128;
	size_t init_capacity = max_capacity / 2;
	size_t iterations    = init_capacity / sizeof(int8_t);
	// create stream
	st = new_stream(&stream, DEF_MEM_MNGR, max_capacity, init_capacity);
	if (is_flow_not_succeeded(st))
	{
		TEST_FAILURE;
	}
	// write until init capacity
	for (int i = 0; i < iterations; ++i)
	{
		st = stream_int8_t(stream, val);
		if (is_flow_not_succeeded(st))
		{
			TEST_FAILURE;
		}
	}
	if (   (*stream).metha.capacity  != init_capacity
	    || (*stream).metha.available != 0
	) {
		TEST_FAILURE;
	}
	// write until max capacity
	for (int i = 0; i < iterations; ++i)
	{
		st = stream_int8_t(stream, val);
		if (is_flow_not_succeeded(st))
		{
			TEST_FAILURE;
		}
	}
	if (   (*stream).metha.capacity  != max_capacity
	    || (*stream).metha.available != 0
	) {
		TEST_FAILURE;
	}
	// no more space
	st = stream_int8_t(stream, val);
	if (!is_flow_failed(st))
	{
		TEST_FAILURE;
	}
	// check memory values
	int8_t *p = (int8_t *) ((*stream).mem_ptr);
	int8_t dval;
	for (int i = 0; i < 2 * iterations; ++i)
	{
		deserialize_int8_t(&dval, p);
		if (dval != val)
		{
			TEST_FAILURE;
		}
		p++;
	}
	// delete stream
	st = delete_stream(&stream);
	if (is_flow_not_succeeded(st))
	{
		TEST_FAILURE;
	}
TEST_FINISHED

NEW_TEST(to_stream_serialize_uint8)
	stream_ptr_t stream;
	FlwSt st;
	uint8_t val = 97;

	size_t max_capacity  = 128;
	size_t init_capacity = max_capacity / 2;
	size_t iterations    = init_capacity / sizeof(uint8_t);
	// create stream
	st = new_stream(&stream, DEF_MEM_MNGR, max_capacity, init_capacity);
	if (is_flow_not_succeeded(st))
	{
		TEST_FAILURE;
	}
	// write until init capacity
	for (int i = 0; i < iterations; ++i)
	{
		st = stream_uint8_t(stream, val);
		if (is_flow_not_succeeded(st))
		{
			TEST_FAILURE;
		}
	}
	if (   (*stream).metha.capacity  != init_capacity
	    || (*stream).metha.available != 0
	) {
		TEST_FAILURE;
	}
	// write until max capacity
	for (int i = 0; i < iterations; ++i)
	{
		st = stream_uint8_t(stream, val);
		if (is_flow_not_succeeded(st))
		{
			TEST_FAILURE;
		}
	}
	if (   (*stream).metha.capacity  != max_capacity
	    || (*stream).metha.available != 0
	) {
		TEST_FAILURE;
	}
	// no more space
	st = stream_uint8_t(stream, val);
	if (!is_flow_failed(st))
	{
		TEST_FAILURE;
	}
	// check memory values
	uint8_t *p = (uint8_t *) ((*stream).mem_ptr);
	uint8_t dval;
	for (int i = 0; i < 2 * iterations; ++i)
	{
		deserialize_uint8_t(&dval, p);
		if (dval != val)
		{
			TEST_FAILURE;
		}
		p++;
	}
	// delete stream
	st = delete_stream(&stream);
	if (is_flow_not_succeeded(st))
	{
		TEST_FAILURE;
	}
TEST_FINISHED

#ifdef INT16_SERIALIZATION_ALLOWED
NEW_TEST(to_stream_serialize_int16)
	stream_ptr_t stream;
	FlwSt st;
	int16_t val = -9777;

	size_t max_capacity  = 128;
	size_t init_capacity = max_capacity / 2;
	size_t iterations    = init_capacity / sizeof(int16_t);
	// create stream
	st = new_stream(&stream, DEF_MEM_MNGR, max_capacity, init_capacity);
	if (is_flow_not_succeeded(st))
	{
		TEST_FAILURE;
	}
	// write until init capacity
	for (int i = 0; i < iterations; ++i)
	{
		st = stream_int16_t(stream, val);
		if (is_flow_not_succeeded(st))
		{
			TEST_FAILURE;
		}
	}
	if (   (*stream).metha.capacity  != init_capacity
	    || (*stream).metha.available != 0
	) {
		TEST_FAILURE;
	}
	// write until max capacity
	for (int i = 0; i < iterations; ++i)
	{
		st = stream_int16_t(stream, val);
		if (is_flow_not_succeeded(st))
		{
			TEST_FAILURE;
		}
	}
	if (   (*stream).metha.capacity  != max_capacity
	    || (*stream).metha.available != 0
	) {
		TEST_FAILURE;
	}
	// no more space
	st = stream_int16_t(stream, val);
	if (!is_flow_failed(st))
	{
		TEST_FAILURE;
	}
	// check memory values
	int16_t *p = (int16_t *) ((*stream).mem_ptr);
	int16_t dval;
	for (int i = 0; i < 2 * iterations; ++i)
	{
		deserialize_int16_t(&dval, p);
		if (dval != val)
		{
			TEST_FAILURE;
		}
		p++;
	}
	// delete stream
	st = delete_stream(&stream);
	if (is_flow_not_succeeded(st))
	{
		TEST_FAILURE;
	}
TEST_FINISHED

NEW_TEST(to_stream_serialize_uint16)
	stream_ptr_t stream;
	FlwSt st;
	uint16_t val = 9777;

	size_t max_capacity  = 128;
	size_t init_capacity = max_capacity / 2;
	size_t iterations    = init_capacity / sizeof(uint16_t);
	// create stream
	st = new_stream(&stream, DEF_MEM_MNGR, max_capacity, init_capacity);
	if (is_flow_not_succeeded(st))
	{
		TEST_FAILURE;
	}
	// write until init capacity
	for (int i = 0; i < iterations; ++i)
	{
		st = stream_uint16_t(stream, val);
		if (is_flow_not_succeeded(st))
		{
			TEST_FAILURE;
		}
	}
	if (   (*stream).metha.capacity  != init_capacity
	    || (*stream).metha.available != 0
	) {
		TEST_FAILURE;
	}
	// write until max capacity
	for (int i = 0; i < iterations; ++i)
	{
		st = stream_uint16_t(stream, val);
		if (is_flow_not_succeeded(st))
		{
			TEST_FAILURE;
		}
	}
	if (   (*stream).metha.capacity  != max_capacity
	    || (*stream).metha.available != 0
	) {
		TEST_FAILURE;
	}
	// no more space
	st = stream_uint16_t(stream, val);
	if (!is_flow_failed(st))
	{
		TEST_FAILURE;
	}
	// check memory values
	uint16_t *p = (uint16_t *) ((*stream).mem_ptr);
	uint16_t dval;
	for (int i = 0; i < 2 * iterations; ++i)
	{
		deserialize_uint16_t(&dval, p);
		if (dval != val)
		{
			TEST_FAILURE;
		}
		p++;
	}
	// delete stream
	st = delete_stream(&stream);
	if (is_flow_not_succeeded(st))
	{
		TEST_FAILURE;
	}
TEST_FINISHED
#endif // INT16_SERIALIZATION_ALLOWED

#ifdef INT32_SERIALIZATION_ALLOWED
NEW_TEST(to_stream_serialize_int32)
	stream_ptr_t stream;
	FlwSt st;
	int32_t val = -977777777;

	size_t max_capacity  = 128;
	size_t init_capacity = max_capacity / 2;
	size_t iterations    = init_capacity / sizeof(int32_t);
	// create stream
	st = new_stream(&stream, DEF_MEM_MNGR, max_capacity, init_capacity);
	if (is_flow_not_succeeded(st))
	{
		TEST_FAILURE;
	}
	// write until init capacity
	for (int i = 0; i < iterations; ++i)
	{
		st = stream_int32_t(stream, val);
		if (is_flow_not_succeeded(st))
		{
			TEST_FAILURE;
		}
	}
	if (   (*stream).metha.capacity  != init_capacity
	    || (*stream).metha.available != 0
	) {
		TEST_FAILURE;
	}
	// write until max capacity
	for (int i = 0; i < iterations; ++i)
	{
		st = stream_int32_t(stream, val);
		if (is_flow_not_succeeded(st))
		{
			TEST_FAILURE;
		}
	}
	if (   (*stream).metha.capacity  != max_capacity
	    || (*stream).metha.available != 0
	) {
		TEST_FAILURE;
	}
	// no more space
	st = stream_int32_t(stream, val);
	if (!is_flow_failed(st))
	{
		TEST_FAILURE;
	}
	// check memory values
	int32_t *p = (int32_t *) ((*stream).mem_ptr);
	int32_t dval;
	for (int i = 0; i < 2 * iterations; ++i)
	{
		deserialize_int32_t(&dval, p);
		if (dval != val)
		{
			TEST_FAILURE;
		}
		p++;
	}
	// delete stream
	st = delete_stream(&stream);
	if (is_flow_not_succeeded(st))
	{
		TEST_FAILURE;
	}
TEST_FINISHED

NEW_TEST(to_stream_serialize_uint32)
	stream_ptr_t stream;
	FlwSt st;
	uint32_t val = 977777777;

	size_t max_capacity  = 128;
	size_t init_capacity = max_capacity / 2;
	size_t iterations    = init_capacity / sizeof(uint32_t);
	// create stream
	st = new_stream(&stream, DEF_MEM_MNGR, max_capacity, init_capacity);
	if (is_flow_not_succeeded(st))
	{
		TEST_FAILURE;
	}
	// write until init capacity
	for (int i = 0; i < iterations; ++i)
	{
		st = stream_uint32_t(stream, val);
		if (is_flow_not_succeeded(st))
		{
			TEST_FAILURE;
		}
	}
	if (   (*stream).metha.capacity  != init_capacity
	    || (*stream).metha.available != 0
	) {
		TEST_FAILURE;
	}
	// write until max capacity
	for (int i = 0; i < iterations; ++i)
	{
		st = stream_uint32_t(stream, val);
		if (is_flow_not_succeeded(st))
		{
			TEST_FAILURE;
		}
	}
	if (   (*stream).metha.capacity  != max_capacity
	    || (*stream).metha.available != 0
	) {
		TEST_FAILURE;
	}
	// no more space
	st = stream_uint32_t(stream, val);
	if (!is_flow_failed(st))
	{
		TEST_FAILURE;
	}
	// check memory values
	uint32_t *p = (uint32_t *) ((*stream).mem_ptr);
	uint32_t dval;
	for (int i = 0; i < 2 * iterations; ++i)
	{
		deserialize_uint32_t(&dval, p);
		if (dval != val)
		{
			TEST_FAILURE;
		}
		p++;
	}
	// delete stream
	st = delete_stream(&stream);
	if (is_flow_not_succeeded(st))
	{
		TEST_FAILURE;
	}
TEST_FINISHED
#endif // INT32_SERIALIZATION_ALLOWED

#ifdef INT64_SERIALIZATION_ALLOWED
NEW_TEST(to_stream_serialize_int64)
	stream_ptr_t stream;
	FlwSt st;
	int64_t val = -977777777777777777L;

	size_t max_capacity  = 128;
	size_t init_capacity = max_capacity / 2;
	size_t iterations    = init_capacity / sizeof(int64_t);
	// create stream
	st = new_stream(&stream, DEF_MEM_MNGR, max_capacity, init_capacity);
	if (is_flow_not_succeeded(st))
	{
		TEST_FAILURE;
	}
	// write until init capacity
	for (int i = 0; i < iterations; ++i)
	{
		st = stream_int64_t(stream, val);
		if (is_flow_not_succeeded(st))
		{
			TEST_FAILURE;
		}
	}
	if (   (*stream).metha.capacity  != init_capacity
	       || (*stream).metha.available != 0
		) {
		TEST_FAILURE;
	}
	// write until max capacity
	for (int i = 0; i < iterations; ++i)
	{
		st = stream_int64_t(stream, val);
		if (is_flow_not_succeeded(st))
		{
			TEST_FAILURE;
		}
	}
	if (   (*stream).metha.capacity  != max_capacity
	       || (*stream).metha.available != 0
		) {
		TEST_FAILURE;
	}
	// no more space
	st = stream_int64_t(stream, val);
	if (!is_flow_failed(st))
	{
		TEST_FAILURE;
	}
	// check memory values
	int64_t *p = (int64_t *) ((*stream).mem_ptr);
	int64_t dval;
	for (int i = 0; i < 2 * iterations; ++i)
	{
		deserialize_int64_t(&dval, p);
		if (dval != val)
		{
			TEST_FAILURE;
		}
		p++;
	}
	// delete stream
	st = delete_stream(&stream);
	if (is_flow_not_succeeded(st))
	{
		TEST_FAILURE;
	}
TEST_FINISHED

NEW_TEST(to_stream_serialize_uint64)
	stream_ptr_t stream;
	FlwSt st;
	uint64_t val = 977777777777777777L;

	size_t max_capacity  = 128;
	size_t init_capacity = max_capacity / 2;
	size_t iterations    = init_capacity / sizeof(uint64_t);
	// create stream
	st = new_stream(&stream, DEF_MEM_MNGR, max_capacity, init_capacity);
	if (is_flow_not_succeeded(st))
	{
		TEST_FAILURE;
	}
	// write until init capacity
	for (int i = 0; i < iterations; ++i)
	{
		st = stream_uint64_t(stream, val);
		if (is_flow_not_succeeded(st))
		{
			TEST_FAILURE;
		}
	}
	if (   (*stream).metha.capacity  != init_capacity
	    || (*stream).metha.available != 0
	) {
		TEST_FAILURE;
	}
	// write until max capacity
	for (int i = 0; i < iterations; ++i)
	{
		st = stream_uint64_t(stream, val);
		if (is_flow_not_succeeded(st))
		{
			TEST_FAILURE;
		}
	}
	if (   (*stream).metha.capacity  != max_capacity
	    || (*stream).metha.available != 0
	) {
		TEST_FAILURE;
	}
	// no more space
	st = stream_uint64_t(stream, val);
	if (!is_flow_failed(st))
	{
		TEST_FAILURE;
	}
	// check memory values
	uint64_t *p = (uint64_t *) ((*stream).mem_ptr);
	uint64_t dval;
	for (int i = 0; i < 2 * iterations; ++i)
	{
		deserialize_uint64_t(&dval, p);
		if (dval != val)
		{
			TEST_FAILURE;
		}
		p++;
	}
	// delete stream
	st = delete_stream(&stream);
	if (is_flow_not_succeeded(st))
	{
		TEST_FAILURE;
	}
TEST_FINISHED
#endif // INT64_SERIALIZATION_ALLOWED

#ifdef FLOAT_SERIALIZATION_ALLOWED
#include <math.h>
NEW_TEST(to_stream_serialize_float)
	stream_ptr_t stream;
	FlwSt st;
	float val = -9.7777f;

	size_t iterations    = 64;
	size_t max_capacity  = 2 * iterations * SIZE_OF_SERIALIZED_FLOAT;
	size_t init_capacity = max_capacity / 2;
	// create stream
	st = new_stream(&stream, DEF_MEM_MNGR, max_capacity, init_capacity);
	if (is_flow_not_succeeded(st))
	{
		TEST_FAILURE;
	}
	// write until init capacity
	for (int i = 0; i < iterations; ++i)
	{
		st = stream_float(stream, val);
		if (is_flow_not_succeeded(st))
		{
			TEST_FAILURE;
		}
	}
	if (   (*stream).metha.capacity  != init_capacity
	    || (*stream).metha.available != 0
	) {
		TEST_FAILURE;
	}
	// write until max capacity
	for (int i = 0; i < iterations; ++i)
	{
		st = stream_float(stream, val);
		if (is_flow_not_succeeded(st))
		{
			TEST_FAILURE;
		}
	}
	if (   (*stream).metha.capacity  != max_capacity
	    || (*stream).metha.available != 0
	) {
		TEST_FAILURE;
	}
	// no more space
	st = stream_float(stream, val);
	if (!is_flow_failed(st))
	{
		TEST_FAILURE;
	}
	// check memory values
	uint8_t *p = ((*stream).mem_ptr);
	float dval;
	for (int i = 0; i < 2 * iterations; ++i)
	{
		deserialize_float(&dval, p);
		if (0.0001f < (fabsf(dval - val) / fabsf(val)))
		{
			TEST_FAILURE;
		}
		p += SIZE_OF_SERIALIZED_FLOAT;
	}
	// delete stream
	st = delete_stream(&stream);
	if (is_flow_not_succeeded(st))
	{
		TEST_FAILURE;
	}
TEST_FINISHED
#endif // FLOAT_SERIALIZATION_ALLOWED

#ifdef DOUBLE_SERIALIZATION_ALLOWED
#include <math.h>
NEW_TEST(to_stream_serialize_double)
	stream_ptr_t stream;
	FlwSt st;
	double val = -9.777777777777;

	size_t iterations    = 64;
	size_t max_capacity  = 2 * iterations * SIZE_OF_SERIALIZED_DOUBLE;
	size_t init_capacity = max_capacity / 2;
	// create stream
	st = new_stream(&stream, DEF_MEM_MNGR, max_capacity, init_capacity);
	if (is_flow_not_succeeded(st))
	{
		TEST_FAILURE;
	}
	// write until init capacity
	for (int i = 0; i < iterations; ++i)
	{
		st = stream_double(stream, val);
		if (is_flow_not_succeeded(st))
		{
			TEST_FAILURE;
		}
	}
	if (   (*stream).metha.capacity  != init_capacity
	       || (*stream).metha.available != 0
		) {
		TEST_FAILURE;
	}
	// write until max capacity
	for (int i = 0; i < iterations; ++i)
	{
		st = stream_double(stream, val);
		if (is_flow_not_succeeded(st))
		{
			TEST_FAILURE;
		}
	}
	if (   (*stream).metha.capacity  != max_capacity
	       || (*stream).metha.available != 0
		) {
		TEST_FAILURE;
	}
	// no more space
	st = stream_double(stream, val);
	if (!is_flow_failed(st))
	{
		TEST_FAILURE;
	}
	// check memory values
	uint8_t *p = ((*stream).mem_ptr);
	double dval;
	for (int i = 0; i < 2 * iterations; ++i)
	{
		deserialize_double(&dval, p);
		if (0.0000000000001 < (fabs(dval - val) / fabs(val)))
		{
			TEST_FAILURE;
		}
		p += SIZE_OF_SERIALIZED_DOUBLE;
	}
	// delete stream
	st = delete_stream(&stream);
	if (is_flow_not_succeeded(st))
	{
		TEST_FAILURE;
	}
TEST_FINISHED
#endif // DOUBLE_SERIALIZATION_ALLOWED

INIT_TESTS_CHECKS
	CHECK_TEST(TEST_CHECK_UP, constants_check);
	CHECK_TEST(TEST_CHECK_UP, increase_functions_check);
	CHECK_TEST(TEST_CHECK_UP, creating_functions_check);
	CHECK_TEST(TEST_CHECK_UP, stream_consistency_check);
	CHECK_TEST(TEST_CHECK_UP, stream_request_size);
	CHECK_TEST(TEST_CHECK_UP, stream_request_size_with_real_memory);
	CHECK_TEST(TEST_CHECK_UP, to_stream_serialize_int8);
	CHECK_TEST(TEST_CHECK_UP, to_stream_serialize_uint8);
#ifdef INT16_SERIALIZATION_ALLOWED
	CHECK_TEST(TEST_CHECK_UP, to_stream_serialize_int16);
	CHECK_TEST(TEST_CHECK_UP, to_stream_serialize_uint16);
#endif // INT16_SERIALIZATION_ALLOWED
#ifdef INT32_SERIALIZATION_ALLOWED
	CHECK_TEST(TEST_CHECK_UP, to_stream_serialize_int32);
	CHECK_TEST(TEST_CHECK_UP, to_stream_serialize_uint32);
#endif // INT32_SERIALIZATION_ALLOWED
#ifdef INT64_SERIALIZATION_ALLOWED
	CHECK_TEST(TEST_CHECK_UP, to_stream_serialize_int64);
	CHECK_TEST(TEST_CHECK_UP, to_stream_serialize_uint64);
#endif // INT64_SERIALIZATION_ALLOWED
#ifdef FLOAT_SERIALIZATION_ALLOWED
	CHECK_TEST(TEST_CHECK_UP, to_stream_serialize_float);
#endif // FLOAT_SERIALIZATION_ALLOWED
#ifdef DOUBLE_SERIALIZATION_ALLOWED
	CHECK_TEST(TEST_CHECK_UP, to_stream_serialize_double);
#endif // DOUBLE_SERIALIZATION_ALLOWED
DONE_TESTS_CHECKS
