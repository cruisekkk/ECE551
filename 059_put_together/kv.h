#ifndef __KV_H__
#define __KV_H__

// define a pair of key-value
struct _kvpair_t {
  const char * key;
  const char * value;
};
typedef struct _kvpair_t kvpair_t;


// define an array of kv pairs
struct _kvarray_t {
  int length;
  kvpair_t * p;
};
typedef struct _kvarray_t kvarray_t;


kvarray_t * readKVs(const char * fname);

//kvpair_t kvline(char * line);

void freeKVs(kvarray_t * pairs);

void printKVs(kvarray_t * pairs);

char * lookupValue(kvarray_t * pairs, const char * key);

#endif
