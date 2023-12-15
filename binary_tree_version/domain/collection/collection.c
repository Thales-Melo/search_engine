#include "collection.h"
#include <stdio.h>
#include <stdlib.h>

Collection *collection_construct(Tree *documents) {
    Collection *collection = (Collection *)malloc(sizeof(Collection));
    collection->documents = documents;
    return collection;
}

void collection_destroy(data_type collection) {
    Collection *aux = (Collection *)collection;
    tree_destroy(aux->documents);
    free(aux);
}

void collection_print(data_type collection) {
    Collection *aux = (Collection *)collection;
    tree_print(aux->documents);
}

void collection_file_print(data_type collection, FILE *file) {
    Collection *aux = (Collection *)collection;
    fprintf (file, "%d\n", tree_size(aux->documents));
    tree_file_print_level_order(aux->documents, file);
}

void fprint_col_value(data_type value, FILE *file) {
    fprintf (file, "%d\n", *(int *)value);
}

void fprint_col_key(key_type key, FILE *file) {
    fprintf (file, "%s ", (char *)key);
}