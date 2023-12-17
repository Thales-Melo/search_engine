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

int word_in_document(Tree *collection, char *doc) {
    return tree_contains_key(collection, doc);
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
void add_document (Tree *collection, char *doc) {
    int *freq = (int*)malloc(sizeof(int));
    *freq = 1;

    tree_add(collection, doc, freq);
}

// Se a palavra nao esta no indice, adicionamos ela
void word_index_add (Tree *index, char *word) {
    tree_add(index, word, tree_construct(compara_strings, 
                free, free, print_string, collection_print, fprint_col_key, fprint_col_value));
}


void connect_word_to_index(Tree *index, char *word, char *document) {
    Tree *collection = (Tree *)(tree_search(index, word));

    if (collection != NULL) {
        if (word_in_document(collection, document)) {
            grow_word_frequency(collection, document);
        } else {
            add_document(collection, document);
        }
        free(word);
    } else {
        Tree *col = tree_construct(compara_strings,
                            NULL, free, print_string, collection_print,
                                        fprint_col_key, fprint_col_value);
        tree_add(index, word, col);
        add_document(col, document);
    }
    
}


void process_document(Tree *index, char *document) {
    Vector *words = read_file_splited(document);

    // Para cada palavra
    for (int k = 0; k < vector_size(words); k++) {
        char *word = strdup(vector_get(words, k));
        connect_word_to_index(index, word, document);
    }

    libera_dados(words);
}


void index_build(Tree *index, Vector *files) {
    double start = get_timestamp();

    // Para cada arquivo na lista de arquivos
    for (int i = 0; i < vector_size(files); i++) {
        char *document = vector_get(files, i);
        process_document(index, document);
    }

    double end = get_timestamp();
    printf("TEMPO DE CONSTRUÇÃO DO ÍNDICE = %lf\n", end - start);
}




void index_save(Tree *index, char *output) {
    FILE *file = fopen(output, "w");

    fprintf (file, "%d\n", tree_size(index));

    tree_file_print_level_order(index, file);

    fclose(file);
}