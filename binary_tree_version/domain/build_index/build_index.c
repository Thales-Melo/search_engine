#include "build_index.h"
#include <stdlib.h>
#include "../../std_data/vector/vector.h"
#include "../file_reading/dir_read.h"
#include "../../utils/utils.h"
#include "../collection/collection.h"
#include <stdio.h>
#include <string.h>


int word_already_indexed (Tree *index, char *word) {
    return tree_contains_key(index, word);
}

int word_in_document(Tree *index, char *word, char *doc) {
    // Se word em index
    printf ("WORD: %s\n", word);
    printf ("DOC: %s\n", doc);
    if (tree_contains_key(index, word)) {
        printf ("WORD IN DOCUMENT\n");
        // Se doc em colecao de documentos
        Collection* aux = (Collection*)(tree_search(index, word));
        if (tree_contains_key(aux->documents, doc)) {
            return 1;
        }
    }

    printf ("WORD NOT IN DOCUMENT\n");
    return 0;
}

void grow_word_frequency (Collection *col, key_type key) {
    // int *freq = (int*)tree_search(col->documents, key);
    // tree_set_value(col->documents, key, &freq + 1);
    // printf ("FREQUENCIA: %d\n", *((int*)tree_search(col->documents, key)));
    int *freq = (int*)tree_search(col->documents, key);
    // if (freq != NULL) {
        // Se a chave já existir na árvore, incrementa a frequência
    (*freq)++;
    // }
}


// Adicionar o documento com frequencia inicial 1
void add_document (Tree *index, char *word, char *doc) {
    // Tree *aux = (Tree*)(tree_search(index, word));
    Collection* aux = (Collection*)(tree_search(index, word));
    // Collection* col = (Collection*)tree_search(aux, doc);
    // int *freq = (int*)malloc(sizeof(int));
    // *freq = 1;
    char *document = strdup(doc);

    // adicionar o documento com frequencia inicial 1
    // O valor da árvore é a frequencia
    // A funcao de adicionar espera um void* para a chave e para o valor
    // Coloque o valor da frequencia em um ponteiro para int

    // Crie o ponteiro para int "freq"
    int *freq = (int*)malloc(sizeof(int));
    // Atribua o valor 1 para o ponteiro
    *freq = 1;
    // Adicione o documento com frequencia 1
    tree_add(aux->documents, document, freq);

    }

// Se a palavra nao esta no indice, adicionamos ela
void word_index_add (Tree *index, char *word) {
    tree_add(index, word, collection_construct(tree_construct(compara_strings, 
                free, collection_destroy, print_string, collection_print, fprint_col_key, fprint_col_value)));
}


// Em seguida, associamos a palavra o documento com frequência inicial 1
void connect_word_to_document (Tree *index, char *word, char *doc) {
    // Tree *aux = (Tree*)(tree_search(index, word));
    Collection* aux = (Collection*)(tree_search(index, word));
    // Collection* col = (Collection*)tree_search(aux, doc);
    int *freq = (int*)malloc(sizeof(int));
    *freq = 1;
    tree_add(aux->documents, doc, freq);
}





void index_build (Tree *index, Vector *files) {
    double start = get_timestamp();

    // Para cada arquivo na lista de arquivos
    for (int i=0; i<vector_size(files); i++) {
        // Le o conteudo e separa as palavras
        char *document = vector_get(files, i);
        Vector *words = read_file_splited(document);
        printf ("\n_________________________\n");
        for (int i=0; i<vector_size(words); i++) {
            printf ("%s\n", (char*)vector_get(words, i));
        }
        printf ("\n_________________________\n");
        // Para cada palavra
        for (int k=0; k<vector_size(words); k++) {
            char *word = (char*)vector_get(words, k);
            printf ("\nWORD DA VEZ: %s\n\n", word);
            // Se a palavra já está no índice
            if (word_already_indexed(index, word)) {
                 // Se já vimos a palavra no documento
                if (word_in_document(index, word, document)) {
                    // Incrementamos a frequência
                    // Tree *aux = (Tree*)(tree_search(index, word));
                    Collection* aux = (Collection*)(tree_search(index, word));
                    // Collection* col = (Collection*)tree_search(aux, document);
                    // int freq = (int)tree_search(aux->documents, document);
                    grow_word_frequency(aux, document);
                    printf ("FREQUENCIA ||: %d\n", *((int*)tree_search(aux->documents, document)));
                }
                // Caso contrário
                else {
                    // Adicionamos o documento com frequência inicial 1
                    add_document(index, word, document);
                    printf("FREQUENCIA: %d\n", *((int*)tree_search(((Collection*)tree_search(index, word))->documents, document)));
                }
            }

            else {
                printf ("WORD NOT IN INDEX\n");
                printf ("WORD: %s\n", word);
                // Se a palavra não está no índice, adicionamos ela
                Collection *col = collection_construct(tree_construct(compara_strings, 
                        free, free, print_string, collection_print, fprint_col_key, fprint_col_value));
                tree_add(index, word, col);
                // word_index_add(index, word);
                // Em seguida, associamos a palavra o documento com frequência inicial 1
                connect_word_to_document(index, word, document);

                printf ("WORD ADDED\n");
                printf ("WORD: %s\n", word);
                // printf ("DOC: %s\n", (char*)document);
                // printf ("DOC: %s\n", (char*)tree_search(col->documents, document));
                printf ("NOME DO DOCUMENTO: %s\n", document);
                // printf ("_________________________\n");
                printf ("FREQUENCIA: %d\n", *((int*)tree_search(col->documents, document)));

            }
        }
        // libera_dados(words);
        vector_destroy(words);
    }

    double end = get_timestamp();

    double dt = (end - start);
    printf ("TEMPO DE CONSTRUÇÃO DO ÍNDICE = %lf", dt);

}


void index_save(Tree *index, char *output) {
    FILE *file = fopen(output, "w");

    fprintf (file, "%d\n", tree_size(index));

    tree_file_print_level_order(index, file);

    fclose(file);
}