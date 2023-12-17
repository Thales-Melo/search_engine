#ifndef _ENGINE_H_
#define _ENGINE_H_


#include "../../../std_data/vector/vector.h"


Vector *load_index(char *index_filename);

Vector *search_docs(Vector *index, char *query);

void search_output(Vector *docs, char* output_file);

void index_destroy_ (Vector *index);

void search_destroy (Vector *docs);

#endif