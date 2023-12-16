#include "build_index.h"
#include <stdlib.h>
#include "../../../std_data/vector/vector.h"
#include "../file_reading/dir_read.h"
#include "../../../utils/utils.h"
#include "../../../collection/collection.h"
#include <stdio.h>
#include <string.h>


int word_already_indexed (Tree *index, char *word) {
    return tree_contains_key(index, word);
}

int word_in_document(Tree *index, char *word, char *doc) {
    // Se word em index
    // printf ("WORD: %s\n", word);
    // printf ("DOC: %s\n", doc);
    if (tree_contains_key(index, word)) {
        // printf ("WORD IN DOCUMENT\n");
        // Se doc em colecao de documentos
        Tree* collection = (Tree*)(tree_search(index, word));
        if (tree_contains_key(collection, doc)) {
            return 1;
        }
    }

    // printf ("WORD NOT IN DOCUMENT\n");
    return 0;
}

void grow_word_frequency (Tree *col, key_type key) {
    // int *freq = (int*)tree_search(col->documents, key);
    // tree_set_value(col->documents, key, &freq + 1);
    // printf ("FREQUENCIA: %d\n", *((int*)tree_search(col->documents, key)));
    int *freq = (int*)tree_search(col, key);
    // if (freq != NULL) {
        // Se a chave já existir na árvore, incrementa a frequência
    (*freq)++;
    // }
}


// Adicionar o documento com frequencia inicial 1
void add_document (Tree *index, char *word, char *doc) {
    Tree* collection = (Tree*)(tree_search(index, word));

    int *freq = (int*)malloc(sizeof(int));
    *freq = 1;

    tree_add(collection, doc, freq);
}

// Se a palavra nao esta no indice, adicionamos ela
void word_index_add (Tree *index, char *word) {
    tree_add(index, word, tree_construct(compara_strings, 
                free, free, print_string, collection_print, fprint_col_key, fprint_col_value));
}


// Em seguida, associamos a palavra o documento com frequência inicial 1
void connect_word_to_document (Tree *index, char *word, char *doc) {
    // Tree *aux = (Tree*)(tree_search(index, word));
    Tree* collection = (Tree*)(tree_search(index, word));
    // Collection* col = (Collection*)tree_search(collection, doc);
    int *freq = (int*)malloc(sizeof(int));
    *freq = 1;
    tree_add(collection, doc, freq);
}



void index_build (Tree *index, Vector *files) {
    double start = get_timestamp();
    // Para cada arquivo na lista de arquivos
    for (int i=0; i<vector_size(files); i++) {
        // Le o conteudo e separa as palavras
        char *document = vector_get(files, i);
        Vector *words = read_file_splited(document);

        // Para cada palavra
        for (int k=0; k<vector_size(words); k++) {
            char *word = strdup(vector_get(words, k));
            // Se a palavra já está no índice
            if (word_already_indexed(index, word)) {
                 // Se já vimos a palavra no documento
                if (word_in_document(index, word, document)) {
                    // Incrementamos a frequência
                    Tree* collection = (Tree*)(tree_search(index, word));
                    free(word);
                    grow_word_frequency(collection, document);
                }
                // Caso contrário
                else {
                    // Adicionamos o documento com frequência inicial 1
                    add_document(index, word, document);
                    free(word);
                }
            }
            else {
                // Se a palavra não está no índice, adicionamos ela
                tree_add(index, word, tree_construct(compara_strings, 
                        NULL, free, print_string, collection_print, fprint_col_key, fprint_col_value));

                // Em seguida, associamos a palavra o documento com frequência inicial 1
                connect_word_to_document(index, word, document);

            }
        }
        libera_dados(words);
    }  
    double end = get_timestamp();
    printf ("TEMPO DE CONSTRUÇÃO DO ÍNDICE = %lf\n", end - start);
}


void index_save(Tree *index, char *output) {
    FILE *file = fopen(output, "w");

    fprintf (file, "%d\n", tree_size(index));

    tree_file_print_level_order(index, file);

    fclose(file);
}