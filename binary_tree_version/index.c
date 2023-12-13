// PROGRAMA QUE CRIA UM INDEX PARA UM ARQUIVO DE DADOS PREPROCESSADOS DE JORNAIS
// O INTUITO DO INDEX É FACILITAR A BUSCA POR PALAVRAS EM UM ARQUIVO DE TEXTO
// OU SEJA, COM O INDEX CRIADO, RODAREMOS UM "BUSCADOR" PARA BUSCAR OS ARQUIVOS COM MAIOR FREQUÊNCIA DAS PALAVRAS BUSCADAS

#include "std_data/binary_tree/tree/tree.h"
#include "std_data/vector/vector.h"
#include "utils/utils.h"
#include <stdio.h>
#include "file_reading/dir_read.h"

#define DATA_DIR argv[1]
#define OUTPUT argv[2]
#define FILE_LIST_FILE_NAME "files.txt"

int main (int argc, char **argv) {

    Vector *file_list = dir_build_file_names(DATA_DIR, FILE_LIST_FILE_NAME);

    Vector *words = read_file_splited(vector_get(file_list, 0));
    Vector *unique_words = vector_unique(words, compara_strings);

    for (int i=0; i<vector_size(unique_words); i++) {
        printf ("%s\n", (char *)vector_get(unique_words, i));
    }

    libera_dados(words);

    // vector_destroy(words);

    vector_destroy(unique_words);

    // vector_destroy(file_list);
    libera_dados(file_list);

    return 0;
}