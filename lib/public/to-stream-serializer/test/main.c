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
	uint8_t mem[10];
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
	real_stream.free_mem_ptr    = &mem[3];
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
TEST_FINISHED

INIT_TESTS_CHECKS
	CHECK_TEST(TEST_CHECK_UP, constants_check);
	CHECK_TEST(TEST_CHECK_UP, increase_functions_check);
	CHECK_TEST(TEST_CHECK_UP, creating_functions_check);
	CHECK_TEST(TEST_CHECK_UP, stream_consistency_check);
#ifdef BELOB_SERIALIZATION_ALLOWED
#endif // BELOB_SERIALIZATION_ALLOWED
DONE_TESTS_CHECKS
