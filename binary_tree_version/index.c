// PROGRAMA QUE CRIA UM INDEX PARA UM ARQUIVO DE DADOS PREPROCESSADOS DE JORNAIS
// O INTUITO DO INDEX É FACILITAR A BUSCA POR PALAVRAS EM UM ARQUIVO DE TEXTO
// OU SEJA, COM O INDEX CRIADO, RODAREMOS UM "BUSCADOR" PARA BUSCAR OS ARQUIVOS COM MAIOR FREQUÊNCIA DAS PALAVRAS BUSCADAS

#include "std_data/binary_tree/tree/tree.h"
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

    Tree *index = tree_construct(compara_strings, free, collection_destroy,
        print_string, collection_print, fprint_string, collection_file_print);
    
    index_build(index, file_list);
    
    index_save(index, OUTPUT);

    libera_dados(file_list);

    tree_destroy(index);


    return 0;
}

// valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./index ../datasets/small output.txt