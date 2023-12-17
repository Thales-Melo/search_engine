// Created by: Thales Melo da Penha
// Disciplina: Estrutura de Dados
// Universidade Federal do Espírito Santo
// Professor: Filipe Wall Mutz

/*
* EXECUTAR COMO: ./index DIRETORIO OUTPUT
*/

#include "std_data/vector/vector.h"
#include "utils/utils.h"
#include <stdio.h>
#include "index-program/domain/file_reading/dir_read.h"
#include <stdlib.h>
#include "index-program/domain/build_index/build_index.h"
#include "collection/collection.h"

#define DATA_DIR argv[1]
#define OUTPUT argv[2]
#define FILE_LIST_FILE_NAME "files.txt"


int main (int argc, char **argv) {

    Vector *file_list = dir_build_file_names(DATA_DIR, FILE_LIST_FILE_NAME);

    Vector *index = vector_construct();
    
    index_build(index, file_list);
    
    index_save(index, OUTPUT);

    libera_dados(file_list);

    index_destroy(index);

    // tree_destroy(index);
    // vector_destroy(index);

    return 0;
}

// valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./index ../datasets/small output.txt