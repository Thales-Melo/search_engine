#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "../../utils/utils.h"
#include "../forward_list/list/forward_list.h"

typedef int (*HashFunction)(const Hash *hash, data_type key);
typedef int (*CmpFunction)(const Hash *hash, data_type key1, data_type key2);

struct Pair {
    data_type key;
    data_type val;
};

struct Hash {
    ForwardList **buckets;
    HashFunction hash_fn;
    CmpFunction cmp_fn;
    int table_size;
    int n_elements;
};

Pair *_hash_pair_construct(data_type key, data_type val) {
    Pair *pair = calloc(1, sizeof(Pair));
    pair->key = key;
    pair->val = val;
    return pair;
}

void _hash_pair_destroy(Pair *pair) {
    if (pair->val != NULL) {
        free(pair->val);
        pair->val = NULL;
    }
    if (pair != NULL) {
        free(pair);
        pair = NULL;
    }
}

Hash *hash_table_construct(int table_size, HashFunction hash_fn, CmpFunction cmp_fn) {
    Hash *h = calloc(1, sizeof(Hash));
    h->buckets = (ForwardList **) calloc(table_size, sizeof(ForwardList*));
    h->table_size = table_size;
    h->hash_fn = hash_fn;
    h->cmp_fn = cmp_fn;
    return h;
}

void hash_table_destroy(Hash *h) {
    for (int i = 0; i < h->table_size; i++) {
        if (h->buckets[i] != NULL) {
            forward_list_destroy(h->buckets[i], _hash_pair_destroy);
        }
    }
    free(h->buckets);
    free(h);
}

void hash_table_insert(Hash *h, data_type key, data_type val) {
    int hash = h->hash_fn(h, key);
    if (h->buckets[hash] == NULL) {
        h->buckets[hash] = forward_list_construct();
    }
    Pair *new_pair = _hash_pair_construct(key, val);
    forward_list_push_front(h->buckets[hash], new_pair);
    h->n_elements++;
}

int hash_table_contains_key(Hash *h, data_type key) {
    int hash = h->hash_fn(h, key);
    if (h->buckets[hash] == NULL) return 0;
    return forward_list_get(h->buckets[hash], key, h->cmp_fn) != NULL;
}

Pair *hash_table_get(Hash *h, data_type key) {
    int hash = h->hash_fn(h, key);
    if (h->buckets[hash] == NULL) return NULL;
    return forward_list_get(h->buckets[hash], key, h->cmp_fn);
}
void hash_table_remove(Hash *h, data_type key) {
    int hash = h->hash_fn(h, key);
    if (h->buckets[hash] != NULL) {
        Pair *pair = forward_list_get(h->buckets[hash], key, h->cmp_fn);
        forward_list_remove(h->buckets[hash], pair, h->cmp_fn, _hash_pair_destroy);
    }
}