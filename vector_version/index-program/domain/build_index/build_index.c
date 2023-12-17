#include "build_index.h"
#include <stdlib.h>
#include "../../../std_data/vector/vector.h"
#include "../file_reading/dir_read.h"
#include "../../../utils/utils.h"
#include "../../../collection/collection.h"
#include <stdio.h>
#include <string.h>
#include "../../../document/document.h"
#include "../../../word/word.h"


int word_already_indexed (Vector *index, Word *word) {
    return vector_find(index, word, word_cmp);
}

int word_in_document(Vector *words, char *doc) {
    // int *freq = (int*)malloc(sizeof(int));
    // *freq = 1;
    Document *aux = document_construct(doc, 1);
    return vector_find(words, aux, document_cmp);
}

void grow_word_frequency (Collection *col, char *doc) {
    // int *freq = (int*)malloc(sizeof(int));
    // *freq = 1;
    Document *aux = document_construct(doc, 1);
    Document *document = vector_get(col->documents, vector_find(col->documents, aux, document_cmp));
    document_grow_frequency(document);
}


// Adicionar o documento com frequencia inicial 1
void add_document (Collection *collection, char *doc) {
    // int *freq = (int*)malloc(sizeof(int));
    // *freq = 1;

    Document *document = document_construct(doc, 1);
    collection_add_document(collection, document);
}

// Se a palavra nao esta no indice, adicionamos ela
void word_index_add (Vector *index, char *word) {
    Word *W = word_constructor(word);
    vector_push_back(index, W);
}


// Em seguida, associamos a palavra o documento com frequência inicial 1
void connect_word_to_document (Vector *index, char *word, char *doc) {
    Word *aux = word_constructor(word);

    Word *W = vector_get(index, vector_find(index, aux, word_cmp));

    add_document(W->collection, doc);
}


void connect_word_to_index(Vector *index, char *word, char *document) {
    Word *aux = word_constructor(word);
    int idx = vector_find(index, aux, word_cmp);
    
    if (idx >= 0) {
        // if (word_in_document(aux->collection->documents, document)) {
            // grow_word_frequency(aux->collection, document);
        // } 
        // else {
            // Document *doc = document_construct(document, 1);
            Word *W = vector_get(index, idx);

            add_document(W->collection, document);

            word_destroy(aux);
        // }
        // CHECAR ESSE FREE AQUI DEPOIS
        // free(word);
    } else {
        vector_push_back(index, aux);
        // printf ("word = %s\n", word);
        // printf ("document = %s\n", document);
        // connect_word_to_document(index, word, document);
        add_document(aux->collection, document);
    }
    
}


void process_document(Vector *index, char *document) {
    Vector *words = read_file_splited(document);

    // Para cada palavra
    for (int k = 0; k < vector_size(words); k++) {
        char *word = strdup(vector_get(words, k));
        connect_word_to_index(index, word, document);
    }

    libera_dados(words);
}


void index_build(Vector *index, Vector *files) {
    double start = get_timestamp();

    // Para cada arquivo na lista de arquivos
    for (int i = 0; i < vector_size(files); i++) {
        char *document = vector_get(files, i);
        process_document(index, document);
    }

    double end = get_timestamp();
    printf("TEMPO DE CONSTRUÇÃO DO ÍNDICE = %lf\n", end - start);
}




void index_save(Vector *index, char *output) {
    FILE *file = fopen(output, "w");

    fprintf (file, "%d\n", vector_size(index));
    // fclose(file);
    for (int i=0; i<vector_size(index); i++) {
        Word *word = vector_get(index, i);
        fprintf (file, "%s\n", word->word);
        collection_file_print(word->collection, file);
       
    }

    // tree_file_print_level_order(index, file);

    fclose(file);
}


void index_destroy (Vector *index) {
    for (int i=0; i<vector_size(index); i++) {
        Word *word = vector_get(index, i);
        word_destroy(word);
    }
    vector_destroy(index);
}