#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "std_data/vector/vector.h"
#include "std_data/binary_tree/tree/tree.h"
#include "utils/utils.h"
#include "search_program/domain/engine/engine.h"


#define INDEX_FILE argv[1]
#define OUTPUT argv[2]

int main(int argc, char **argv)
{   
    Tree *index = load_index(INDEX_FILE);
    
    char query[500];
    printf ("Query: ");
    scanf("%[^\n]s", query);
    
    double start = get_timestamp();
    Tree *docs = search_docs(index, query);
    double end = get_timestamp();

    search_output(docs, OUTPUT, end-start);

    tree_destroy(index);
    
    tree_destroy(docs);

    return 0;
}