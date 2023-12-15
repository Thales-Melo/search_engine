#include "collection.h"
#include <stdio.h>
#include <stdlib.h>


void collection_destroy(data_type collection) {
    Tree *col = (Tree *)collection;
    if (col == NULL) {
        printf ("collection_destroy: col == NULL\n");
        return;
    }
    tree_destroy(col);
}

void collection_print(data_type collection) {
    Tree *col = (Tree*)collection;
    tree_print(col);
}

void collection_file_print(data_type collection, FILE *file) {
    Tree *col = (Tree *)collection;
    fprintf (file, "%d\n", tree_size(col));
    tree_file_print_level_order(col, file);
}

void fprint_col_value(data_type value, FILE *file) {
    fprintf (file, "%d\n", *(int *)value);
}

void fprint_col_key(key_type key, FILE *file) {
    fprintf (file, "%s ", (char *)key);
}