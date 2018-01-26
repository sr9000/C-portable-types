#include <stdlib.h>
#include <string.h>

#include "blob-serialization.h"
#include "test.h"

#define MAX_SERIALIZE_SIZE 200
uint8_t random_data[] =
	{ 145, 132, 135, 125, 139
	,  83, 109, 120, 157,  35
	, 120,  81, 203, 138, 116
	, 195, 249, 226, 226,  96};
char string_data[] = "blob as a simple string";
void *zero_data = NULL;

NEW_TEST(blob_random)
	char to_serialize [MAX_SERIALIZE_SIZE] = {0xff};
	int size = sizeof(random_data) / sizeof(uint8_t);
	int offset = sizeof(uint32_t) / sizeof(uint8_t);
	uint8_t *p;

	p = (uint8_t *)serialize_blob(to_serialize, random_data, size);

	// check shift
	if ((p - ((uint8_t *)to_serialize)) != size + offset)
		TEST_FAILURE;

	// check memory content
	if (memcmp(((uint8_t *)to_serialize) + offset, random_data, size))
		TEST_FAILURE;

	// check written size of blob
	uint32_t gsize;
	deserialize_uint32_t(&gsize, to_serialize);
	if (get_size_of_blob(to_serialize) != gsize || gsize != size)
		TEST_FAILURE;

	// read blob
	char to_deserialize [MAX_SERIALIZE_SIZE] = {0xff};
	p = (uint8_t *)deserialize_blob(to_deserialize, to_serialize);

	// check shift
	if ((p - ((uint8_t *)to_serialize)) != size + offset)
		TEST_FAILURE;

	// check memory content
	if (memcmp(random_data, to_deserialize, size))
		TEST_FAILURE;
TEST_FINISHED

NEW_TEST(blob_string)
	char to_serialize [MAX_SERIALIZE_SIZE] = {0xff};
	int size = sizeof(string_data) / sizeof(uint8_t);
	int offset = sizeof(uint32_t) / sizeof(uint8_t);
	uint8_t *p;

	p = (uint8_t *)serialize_blob(to_serialize, string_data, size);

	// check shift
	if ((p - ((uint8_t *)to_serialize)) != size + offset)
		TEST_FAILURE;

	// check memory content
	if (memcmp(((uint8_t *)to_serialize) + offset, string_data, size))
		TEST_FAILURE;

	// check written size of blob
	uint32_t gsize;
	deserialize_uint32_t(&gsize, to_serialize);
	if (get_size_of_blob(to_serialize) != gsize || gsize != size)
		TEST_FAILURE;

	// read blob
	char to_deserialize [MAX_SERIALIZE_SIZE] = {0xff};
	p = (uint8_t *)deserialize_blob(to_deserialize, to_serialize);

	// check shift
	if ((p - ((uint8_t *)to_serialize)) != size + offset)
		TEST_FAILURE;

	// check memory content
	if (memcmp(string_data, to_deserialize, size))
		TEST_FAILURE;
TEST_FINISHED

NEW_TEST(blob_zero)
	char to_serialize [MAX_SERIALIZE_SIZE] = {0xff};
	int size = 0;
	int offset = sizeof(uint32_t) / sizeof(uint8_t);
	uint8_t *p;

	p = (uint8_t *)serialize_blob(to_serialize, string_data, size);

	// check shift
	if ((p - ((uint8_t *)to_serialize)) != size + offset)
		TEST_FAILURE;

	// check written size of blob
	uint32_t gsize;
	deserialize_uint32_t(&gsize, to_serialize);
	if (get_size_of_blob(to_serialize) != gsize || gsize != size)
		TEST_FAILURE;

	// read blob
	char to_deserialize [MAX_SERIALIZE_SIZE] = {0xff};
	p = (uint8_t *)deserialize_blob(to_deserialize, to_serialize);

	// check shift
	if ((p - ((uint8_t *)to_serialize)) != size + offset)
		TEST_FAILURE;
TEST_FINISHED

#ifdef BELOB_SERIALIZATION_ALLOWED

NEW_TEST(belob_random)
	char to_serialize [MAX_SERIALIZE_SIZE] = {0xff};
	int size = sizeof(random_data) / sizeof(uint8_t);
	int offset = sizeof(uint64_t) / sizeof(uint8_t);
	uint8_t *p;

	p = (uint8_t *)serialize_belob(to_serialize, random_data, size);

	// check shift
	if ((p - ((uint8_t *)to_serialize)) != size + offset)
		TEST_FAILURE;

	// check memory content
	if (memcmp(((uint8_t *)to_serialize) + offset, random_data, size))
		TEST_FAILURE;

	// check written size of blob
	uint64_t gsize;
	deserialize_uint64_t(&gsize, to_serialize);
	if (get_size_of_belob(to_serialize) != gsize || gsize != size)
		TEST_FAILURE;

	// read blob
	char to_deserialize [MAX_SERIALIZE_SIZE] = {0xff};
	p = (uint8_t *)deserialize_belob(to_deserialize, to_serialize);

	// check shift
	if ((p - ((uint8_t *)to_serialize)) != size + offset)
		TEST_FAILURE;

	// check memory content
	if (memcmp(random_data, to_deserialize, size))
		TEST_FAILURE;
TEST_FINISHED

NEW_TEST(belob_string)
	char to_serialize [MAX_SERIALIZE_SIZE] = {0xff};
	int size = sizeof(string_data) / sizeof(uint8_t);
	int offset = sizeof(uint64_t) / sizeof(uint8_t);
	uint8_t *p;

	p = (uint8_t *)serialize_belob(to_serialize, string_data, size);

	// check shift
	if ((p - ((uint8_t *)to_serialize)) != size + offset)
		TEST_FAILURE;

	// check memory content
	if (memcmp(((uint8_t *)to_serialize) + offset, string_data, size))
		TEST_FAILURE;

	// check written size of blob
	uint64_t gsize;
	deserialize_uint64_t(&gsize, to_serialize);
	if (get_size_of_belob(to_serialize) != gsize || gsize != size)
		TEST_FAILURE;

	// read blob
	char to_deserialize [MAX_SERIALIZE_SIZE] = {0xff};
	p = (uint8_t *)deserialize_belob(to_deserialize, to_serialize);

	// check shift
	if ((p - ((uint8_t *)to_serialize)) != size + offset)
		TEST_FAILURE;

	// check memory content
	if (memcmp(string_data, to_deserialize, size))
		TEST_FAILURE;
TEST_FINISHED

NEW_TEST(belob_zero)
	char to_serialize[MAX_SERIALIZE_SIZE] = {0xff};
	int size = 0;
	int offset = sizeof(uint64_t) / sizeof(uint8_t);
	uint8_t *p;

	p = (uint8_t *)serialize_belob(to_serialize, string_data, size);

	// check shift
	if ((p - ((uint8_t *)to_serialize)) != size + offset)
		TEST_FAILURE;

	// check written size of blob
	uint64_t gsize;
	deserialize_uint64_t(&gsize, to_serialize);
	if (get_size_of_belob(to_serialize) != gsize || gsize != size)
		TEST_FAILURE;

	// read blob
	char to_deserialize [MAX_SERIALIZE_SIZE] = {0xff};
	p = (uint8_t *)deserialize_belob(to_deserialize, to_serialize);

	// check shift
	if ((p - ((uint8_t *)to_serialize)) != size + offset)
		TEST_FAILURE;
TEST_FINISHED

#endif // BELOB_SERIALIZATION_ALLOWED

INIT_TESTS_CHECKS
	CHECK_TEST(TEST_CHECK_UP, blob_random);
	CHECK_TEST(TEST_CHECK_UP, blob_string);
	CHECK_TEST(TEST_CHECK_UP, blob_zero);
#ifdef BELOB_SERIALIZATION_ALLOWED
	CHECK_TEST(TEST_CHECK_UP, belob_random);
	CHECK_TEST(TEST_CHECK_UP, belob_string);
	CHECK_TEST(TEST_CHECK_UP, belob_zero);
#endif // BELOB_SERIALIZATION_ALLOWED
DONE_TESTS_CHECKS
