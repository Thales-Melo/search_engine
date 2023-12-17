#include "utils.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


Vector *string_split(char *str)
{
    Vector *words = vector_construct();

    // Split the string at every space character
    char *word = strtok(str, " ");

    while (word != NULL)
    {
        // o strdup faz um malloc internamente! Lembre-se de remove-lo!
        vector_push_back(words, strdup(word));
        word = strtok(NULL, " ");
    }

    return words;
}



void libera_dados(Vector *words)
{
    if (words == NULL) {
        return;
    }
    char *word = NULL;
    for (int i = 0; i < vector_size(words); i++) {
        // libera os espacos alocados pelo strdup
        word = (char*)vector_get(words, i);
        if (word != NULL) {
            free(word);
            word = NULL;
        }
    }   

    // libera o vetor
    vector_destroy(words);
    words = NULL;
}



// precisamos fazer essa funcao porque as funcoes do vector esperam como argumento
// uma funcao que recebe dois void* e nao dois char*.
int compara_strings(void *a, void *b)
{
    return strcmp((char *)a, (char *)b);
}



double get_timestamp()
{
    struct timespec now;
    timespec_get(&now, TIME_UTC);
    return now.tv_sec + (((double)now.tv_nsec) / 1e9);
}

