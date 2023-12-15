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

// void print_key (void *key) {
//     printf ("%s\n", (char *)key);
// }

int main (int argc, char **argv) {
    // TESTE DE LEITURA DE ARQUIVO

    Vector *file_list = dir_build_file_names(DATA_DIR, FILE_LIST_FILE_NAME);

    // Vector *words = read_file_splited(vector_get(file_list, 0));
    // Vector *unique_words = vector_unique(words, compara_strings);

    // TESTE DE CONSTRUCAO DO INDICE
    Tree *index = tree_construct(compara_strings, free, collection_destroy,
        print_string, collection_print, fprint_string, collection_file_print);
   
    index_build(index, file_list);

    index_save(index, OUTPUT);


    // for (int i=0; i<vector_size(unique_words); i++) {
    //     printf ("%s\n", (char *)vector_get(unique_words, i));
    // }

    // TESTE DE CRIAÇÃO DE INDEX
    // Tree *index = build_index(file_list, compara_strings, print_key, print_val);

    // libera_dados(words);

    // vector_destroy(words);

    // vector_destroy(unique_words);

    // vector_destroy(file_list);
    libera_dados(file_list);
    // free(file_list);
    // free(file_list);
    tree_destroy(index);
    // vector_destroy(file_list);

    return 0;
}

// valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./index ../datasets/small