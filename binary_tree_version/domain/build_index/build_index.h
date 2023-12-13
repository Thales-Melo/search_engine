#ifndef _BUILD_INDEX_H_
#define _BUILD_INDEX_H_

#include "../../std_data/binary_tree/tree/tree.h"


Tree *build_index(Vector *file_list, int (*compara_strings)(void *, void *), void (*print_key)(void *), void (*print_val)(void *));


#endif