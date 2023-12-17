#ifndef _COLLECTION_H_
#define _COLLECTION_H_

#include "../std_data/vector/vector.h"
#include <stdio.h>

typedef void (*collection_destroy_fn)(data_type);


typedef struct collection {
    Vector *documents;
    collection_destroy_fn destroy_fn;
} Collection;

Collection *collection_construct(collection_destroy_fn destroy_fn);

void collection_destroy(Collection *collection);

void collection_print(Collection *collection);

void collection_file_print(Collection *collection, FILE *file);

void collection_add_document(Collection *collection, data_type document);

int collection_contains(Collection *collection, data_type document);

data_type collection_get(Collection *collection, data_type word);

// int collection_cmp(data_type collection1, data_type collection2);

#endif