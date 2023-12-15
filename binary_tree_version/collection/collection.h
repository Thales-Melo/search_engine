#ifndef _COLLECTION_H_
#define _COLLECTION_H_

#include "../std_data/binary_tree/tree/tree.h"


void collection_destroy(data_type collection);

void collection_print(data_type collection);

void collection_file_print(data_type collection, FILE *file);

void fprint_col_value(data_type value, FILE *file);

void fprint_col_key(key_type key, FILE *file);


#endif