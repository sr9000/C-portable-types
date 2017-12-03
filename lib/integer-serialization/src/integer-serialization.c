#ifndef INTEGER_SERIALIZATION_H
#define INTEGER_SERIALIZATION_H

#include "integer-serialization.h"

void*
serialize_int8_t(
   void *address_to_serialize
 , int8_t value
) {
	int8_t *p = (int8_t*)address_to_serialize;
	(*p) = value;
	return (void*)(++p);
}

void*
deserialize_int8_t(
   int8_t &value
 , void *address_to_deserialize
) {
	int8_t *p = (int8_t*)address_to_serialize;
	value = *p;
	return (void*)(++p);
}

void*
serialize_uint8_t(
   void *address_to_serialize
 , uint8_t value
) {
	uint8_t *p = (uint8_t*)address_to_serialize;
	(*p) = value;
	return (void*)(++p);
}

void*
deserialize_uint8_t(
   uint8_t &value
 , void *address_to_deserialize
) {
	uint8_t *p = (uint8_t*)address_to_serialize;
	value = *p;
	return (void*)(++p);
}

#ifdef INT16_MAX

void*
serialize_int16_t(
   void *address_to_serialize
 , int16_t value
) {
	uint8_t *p = (uint8_t*)address_to_serialize;
	(*p) = (uint8_t)(0xff & (value>>8));
	++p;
	(*p) = (uint8_t)(0xff & value);
	return (void*)(++p);
}

void*
deserialize_int16_t(
   int16_t &value
 , void *address_to_deserialize
) {
	uint8_t *p = (uint8_t*)address_to_serialize;
	uint16_t h, l;
	h = (uint16_t)(*(p++));
	l = (uint16_t)(*p);
	value = (int16_t)((h<<8) | l);
	return (void*)(++p);
}

void*
serialize_uint16_t(
   void *address_to_serialize
 , uint16_t value
) {
	uint8_t *p = (uint8_t*)address_to_serialize;
	(*p) = (uint8_t)(0xff & (value>>8));
	++p;
	(*p) = (uint8_t)(0xff & value);
	return (void*)(++p);
}

void*
deserialize_uint16_t(
   uint16_t &value
 , void *address_to_deserialize
) {
	uint8_t *p = (uint8_t*)address_to_serialize;
	uint16_t h, l;
	h = (uint16_t)(*(p++));
	l = (uint16_t)(*p);
	value = (h<<8) | l;
	return (void*)(++p);
}
#endif //INT16_MAX

#ifdef INT32_MAX

void*
serialize_int32_t(
   void *address_to_serialize
 , int32_t value
) {
	uint8_t *p = (uint8_t*)address_to_serialize;
	(*p) = (uint8_t)(0xff & (value>>24));
	++p;
	(*p) = (uint8_t)(0xff & (value>>16));
	++p;
	(*p) = (uint8_t)(0xff & (value>>8));
	++p;
	(*p) = (uint8_t)(0xff & value);
	return (void*)(++p);
}

void*
deserialize_int32_t(
   int32_t &value
 , void *address_to_deserialize
) {
	uint8_t *p = (uint8_t*)address_to_serialize;
	uint32_t hh, hl, lh, ll;
	hh = (uint32_t)(*(p++));
	hl = (uint32_t)(*(p++));
	lh = (uint32_t)(*(p++));
	ll = (uint32_t)(*p);
	value = (int32_t)((hh<<24) | (hl<<16) | (lh<<8) | ll);
	return (void*)(++p);
}

void*
serialize_uint32_t(
   void *address_to_serialize
 , uint32_t value
) {
	uint8_t *p = (uint8_t*)address_to_serialize;
	(*p) = (uint8_t)(0xff & (value>>24));
	++p;
	(*p) = (uint8_t)(0xff & (value>>16));
	++p;
	(*p) = (uint8_t)(0xff & (value>>8));
	++p;
	(*p) = (uint8_t)(0xff & value);
	return (void*)(++p);
}

void*
deserialize_uint32_t(
   uint32_t &value
 , void *address_to_deserialize
) {
	uint8_t *p = (uint8_t*)address_to_serialize;
	uint32_t hh, hl, lh, ll;
	hh = (uint32_t)(*(p++));
	hl = (uint32_t)(*(p++));
	lh = (uint32_t)(*(p++));
	ll = (uint32_t)(*p);
	value = (hh<<24) | (hl<<16) | (lh<<8) | ll;
	return (void*)(++p);
}
#endif //INT32_MAX

#ifdef INT64_MAX

void*
serialize_int64_t(
   void *address_to_serialize
 , int64_t value
) {
	uint8_t *p = (uint8_t*)address_to_serialize;
	(*p) = (uint8_t)(0xff & (value>>56));
	++p;
	(*p) = (uint8_t)(0xff & (value>>48));
	++p;
	(*p) = (uint8_t)(0xff & (value>>40));
	++p;
	(*p) = (uint8_t)(0xff & (value>>32));
	++p;
	(*p) = (uint8_t)(0xff & (value>>24));
	++p;
	(*p) = (uint8_t)(0xff & (value>>16));
	++p;
	(*p) = (uint8_t)(0xff & (value>>8));
	++p;
	(*p) = (uint8_t)(0xff & value);
	return (void*)(++p);
}

void*
deserialize_int64_t(
   int64_t &value
 , void *address_to_deserialize
) {
	uint8_t *p = (uint8_t*)address_to_serialize;
	uint64_t hhh, hhl, hlh, hll, lhh, lhl, llh, lll;
	hhh = (uint64_t)(*(p++));
	hhl = (uint64_t)(*(p++));
	hlh = (uint64_t)(*(p++));
	hll = (uint64_t)(*(p++));
	lhh = (uint64_t)(*(p++));
	lhl = (uint64_t)(*(p++));
	llh = (uint64_t)(*(p++));
	lll = (uint64_t)(*p);
	value = (int64_t)(  (hhh<<56) | (hhl<<48) | (hlh<<40) | (hll<<32)
	                  | (lhh<<24) | (lhl<<16) | (llh<<8)  | lll);
	return (void*)(++p);
}

void*
serialize_uint64_t(
   void *address_to_serialize
 , uint64_t value
) {
	uint8_t *p = (uint8_t*)address_to_serialize;
	(*p) = (uint8_t)(0xff & (value>>56));
	++p;
	(*p) = (uint8_t)(0xff & (value>>48));
	++p;
	(*p) = (uint8_t)(0xff & (value>>40));
	++p;
	(*p) = (uint8_t)(0xff & (value>>32));
	++p;
	(*p) = (uint8_t)(0xff & (value>>24));
	++p;
	(*p) = (uint8_t)(0xff & (value>>16));
	++p;
	(*p) = (uint8_t)(0xff & (value>>8));
	++p;
	(*p) = (uint8_t)(0xff & value);
	return (void*)(++p);
}

void*
deserialize_uint64_t(
   uint64_t &value
 , void *address_to_deserialize
) {
	uint8_t *p = (uint8_t*)address_to_serialize;
	uint64_t hhh, hhl, hlh, hll, lhh, lhl, llh, lll;
	hhh = (uint64_t)(*(p++));
	hhl = (uint64_t)(*(p++));
	hlh = (uint64_t)(*(p++));
	hll = (uint64_t)(*(p++));
	lhh = (uint64_t)(*(p++));
	lhl = (uint64_t)(*(p++));
	llh = (uint64_t)(*(p++));
	lll = (uint64_t)(*p);
	value =   (hhh<<56) | (hhl<<48) | (hlh<<40) | (hll<<32)
	        | (lhh<<24) | (lhl<<16) | (llh<<8)  | lll;
	return (void*)(++p);
}
#endif //INT64_MAX
