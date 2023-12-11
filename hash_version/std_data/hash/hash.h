#ifndef _HASH_H_
#define _HASH_H_

typedef struct Hash Hash;

typedef struct Pair Pair;


typedef int (*HashFunction)(const Hash *hash, data_type key);

typedef int (*CmpFunction)(const Hash *hash, data_type key1, data_type key2);


Pair *_hash_pair_construct(data_type key, data_type val);

void _hash_pair_destroy(Pair *pair);

Hash *hash_table_construct(int table_size, HashFunction hash_fn, CmpFunction cmp_fn);

void hash_table_destroy(Hash *h);

void hash_table_insert(Hash *h, data_type key, data_type val);

int hash_table_contains_key(Hash *h, data_type key);

Pair *hash_table_get(Hash *h, data_type key);

void hash_table_remove(Hash *h, data_type key);


#endif