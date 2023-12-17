#include "build_index.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../file_reading/dir_read.h"
#include "../../../std_data/vector/vector.h"
#include "../../../collection/collection.h"
#include "../../../document/document.h"
#include "../../../word/word.h"
#include "../../../utils/utils.h"



void grow_word_frequency (Collection *col, char *doc) {
    Document *aux = document_construct(doc, 1);
    Document *document = vector_get(col->documents, vector_find(col->documents, aux, document_cmp));
    document_grow_frequency(document);
}



// Adicionar o documento à coleção
void add_document (Collection *collection, char *doc) {
    Document *document = document_construct(doc, 1);
    // A função collection_add_document já trata os casos em que o documento já existe
    // Então a frequência do documento é incrementada
    collection_add_document(collection, document);
}



void connect_word_to_index(Vector *index, char *word, char *document) {
    Word *aux = word_constructor(word);
    int idx = vector_find(index, aux, word_cmp);
    
    if (idx >= 0) {
            Word *W = vector_get(index, idx);

            add_document(W->collection, document);

            word_destroy(aux);

    } else {
        vector_push_back(index, aux);
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

    for (int i=0; i<vector_size(index); i++) {
        Word *word = vector_get(index, i);
        fprintf (file, "%s\n", word->word);
        collection_file_print(word->collection, file);
       
    }

    fclose(file);
}



void index_destroy (Vector *index) {
    for (int i=0; i<vector_size(index); i++) {
        Word *word = vector_get(index, i);
        word_destroy(word);
    }
    vector_destroy(index);
}