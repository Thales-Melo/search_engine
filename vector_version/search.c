#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "std_data/vector/vector.h"
#include "utils/utils.h"
#include "search_program/domain/engine/engine.h"


#define INDEX_FILE argv[1]
#define OUTPUT argv[2]

int main(int argc, char **argv)
{
    Vector *index = load_index(INDEX_FILE);

    char query[500];
    printf ("Query: ");
    scanf("%[^\n]s", query);

    Vector *docs = search_docs(index, query);

    search_output(docs, OUTPUT);
    


    search_destroy(docs);

    index_destroy_(index);


    return 0;
}