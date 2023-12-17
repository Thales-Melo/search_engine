#include "engine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../std_data/binary_tree/tree/tree.h"
#include "../../../std_data/vector/vector.h"
#include "../../../collection/collection.h"
#include "../../../utils/utils.h"

// Estrutura para armazenar os documentos e suas respectivas
// frequencias a serem printados no arquivo de saída
typedef struct output {
    char *doc;
    int freq;
} Output;


//////////////////////////////////////////////////////
// FUNCÕES AUXILIARES (CONTIDAS APENAS NO ENGINE.C)
//////////////////////////////////////////////////////

Vector *read_query (char *query) {
    Vector *words = string_split(query);

    Vector *unique = vector_unique(words, compara_strings);

    vector_destroy(words);

    return unique;
}

////////////////////////////////////////
////////////////////////////////////////


Tree *load_index(char *index_filename) {
    FILE *F = fopen(index_filename, "r");
    
    Tree *index = tree_construct(compara_strings, free, collection_destroy,
                    print_string, collection_print, fprint_string, collection_file_print);

    if (F == NULL) {
        printf("Erro ao abrir o arquivo %s\n", index_filename);
        exit(1);
    }
    int size;
    fscanf(F, "%d\n", &size);

    for (int i=0; i<size; i++) {
        char aux[100];
        fscanf(F, "%s\n", aux);
        char *key = strdup(aux);
        int num_docs;
        fscanf (F,"%d\n", &num_docs);
        Tree *col = tree_construct(compara_strings, free,
                     free, print_string, collection_print, 
                                        fprint_col_key, fprint_col_value);
        for (int j=0; j<num_docs; j++) {
            char aux2[100];
            fscanf (F, "%s ", aux2);
            char *doc = strdup(aux2);
            int *freq = (int *)malloc(sizeof(int));
            fscanf (F, "%d\n", freq);
            tree_add(col, doc, freq);
        }

        tree_add(index, key, col);
    }    

    fclose(F);

    return index;
}



Tree *search_docs(Tree *index, char *query) {
    double start = get_timestamp();

    // Palavras da query
    Vector *words = read_query(query);

    // Documentos recomendados e respectivas relevâncias
    Tree *recommendations = tree_construct(compara_strings, NULL, free, print_string, print_string, fprint_string, fprint_string);

    // Para cada palavra da query
    for (int i = 0; i < vector_size(words); i++) {
        // Obtém a lista de documentos em que a palavra aparece e as respectivas frequências
        Tree *col = (Tree *)tree_search(index, vector_get(words, i));
        // Se a palavra não estiver no índice, passa para a próxima
        if (col != NULL) {
            // Para cada documento em que a palavra aparece
            for (int j = 0; j < tree_size(col); j++) {
                // Obtém o nome do documento
                char *doc = (char *)tree_get_key_in_order(col, j);
                // Obtém a frequência da palavra no documento
                int *freq = (int *)tree_get_value_in_order(col, j);
                int *old_freq = (int *)tree_search(recommendations, doc);

                // Se o documento não está na lista de recomendações
                if (old_freq == NULL) {
                    // Cria uma cópia da frequência e adiciona à árvore
                    int *freq_copy = (int *)malloc(sizeof(int));
                    *freq_copy = *freq;
                    tree_add(recommendations, doc, freq_copy);
                }
                // Se o documento já está na lista de recomendações
                else {
                    int *new_freq = (int *)malloc(sizeof(int));
                    if (old_freq != NULL) {
                        *new_freq = (*freq + (*old_freq));
                    } else {
                        *new_freq = *freq;
                    }

                    // Libera a memória da frequência antiga
                    free(old_freq);
                    // Define a nova frequência
                    tree_set_value(recommendations, doc, new_freq);
                }
            }
        }
    }

    double end = get_timestamp();
    printf("TEMPO DE BUSCA: %lf\n", end - start);
    libera_dados(words);

    return recommendations;
}





////////////////////////////////////////////////
// OUTPUT FORMAT AND FUNCTIONS
////////////////////////////////////////////////

Output *output_construct(char *doc, int freq) {
    Output *output = (Output *)malloc(sizeof(Output));
    output->doc = strdup(doc);
    output->freq = freq;

    return output;
}



void output_destroy (void *output) {
    Output *OP = (Output *)output;
    if (OP == NULL) {
        return;
    }
    if (OP->doc != NULL) {
        printf("DOC: %s\n", OP->doc);
        free(OP->doc);
        OP->doc = NULL;
    }
    
    if (OP != NULL) {
        free(OP);
        OP = NULL;
    }
}



int compara_output (void *a, void *b) {
    Output *A = (Output *)a;
    Output *B = (Output *)b;

    if (A->freq > B->freq) {
        return -1;
    }
    else if (A->freq < B->freq) {
        return 1;
    }
    else {
        return 0;
    }
}



void search_output(Tree *docs, char* output_file) {
    FILE *F = fopen(output_file, "w");

    if (F == NULL) {
        printf("Erro ao abrir o arquivo %s\n", output_file);
        exit(1);
    }

    Vector *V = vector_construct();

    for (int i=0; i<tree_size(docs); i++) {
        char *doc = (char *)tree_get_key_in_order(docs, i);
        int *freq = (int *)tree_get_value_in_order(docs, i);
        Output *OP = output_construct(doc, *freq);
        vector_push_back(V, OP);
    }

    vector_sort(V, compara_output);

    for (int i=0; i<vector_size(V); i++) {
        if (i == 10) {
            break;
        }
        Output *OP = (Output *)vector_get(V, i);
        fprintf(F, "%s: %d\n", OP->doc, OP->freq);
    }

    for (int i=0; i<vector_size(V); i++) {
        Output *OP = (Output *)vector_get(V, i);
        output_destroy(OP);
    }

    vector_destroy(V);

    fclose(F);
}