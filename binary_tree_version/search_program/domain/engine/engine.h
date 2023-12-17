#ifndef _ENGINE_H_
#define _ENGINE_H_


#include "../../../std_data/binary_tree/tree/tree.h"


Tree *load_index(char *index_filename);

Tree *search_docs(Tree *index, char *query);

void search_output(Tree *docs, char* output_file, double duration);


#endif