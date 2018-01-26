
#include "integer-serialization.h"
#include "blob-serialization.h"


void*
serialize_blob(
	  void *address_to_serialize
	, void *data
	, uint32_t size
) {
	void *p = address_to_serialize;
	uint8_t *d = (uint8_t *)data;

	p = serialize_uint32_t(p, size);
	while (size--)
	{
		p = serialize_uint8_t(p, *(d++));
	}

	return p;
}

uint32_t
get_size_of_blob(
	  void *address_to_deserialize
) {
	uint32_t size;
	deserialize_uint32_t(&size, address_to_deserialize);
	return size;
}

void*
deserialize_blob(
	  void *data
	, void *address_to_deserialize
) {
	uint32_t size;
	void *p = address_to_deserialize;
	uint8_t *d = (uint8_t *)data;

	p = deserialize_uint32_t(&size, p);
	while (size--)
	{
		p = deserialize_uint8_t((d++), p);
	}

	return p;
}

#ifdef BELOB_SERIALIZATION_ALLOWED

void*
serialize_belob(
	  void *address_to_serialize
	, void *data
	, uint64_t size
) {
	void *p = address_to_serialize;
	uint8_t *d = (uint8_t *)data;

	p = serialize_uint64_t(p, size);
	while (size--)
	{
		p = serialize_uint8_t(p, *(d++));
	}

	return p;
}

uint64_t
get_size_of_belob(
	  void *address_to_deserialize
) {
	uint64_t size;
	deserialize_uint64_t(&size, address_to_deserialize);
	return size;
}

void*
deserialize_belob(
	  void *data
	, void *address_to_deserialize
) {
	uint64_t size;
	void *p = address_to_deserialize;
	uint8_t *d = (uint8_t *)data;

	p = deserialize_uint64_t(&size, p);
	while (size--)
	{
		p = deserialize_uint8_t((d++), p);
	}

	return p;
}

#endif // BELOB_SERIALIZATION_ALLOWED
