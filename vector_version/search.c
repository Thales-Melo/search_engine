// Created by: Thales Melo da Penha
// Disciplina: Estrutura de Dados
// Universidade Federal do Espírito Santo
// Professor: Filipe Wall Mutz

/*
* EXECUTAR COMO: ./search INDICE OUTPUT
*/

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

    double start = get_timestamp();
    Vector *docs = search_docs(index, query);
    double end = get_timestamp();

    search_output(docs, OUTPUT, end-start);
    
    search_destroy(docs);

    index_loaded_destroy(index);

    return 0;
}