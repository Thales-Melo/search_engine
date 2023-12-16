#include "engine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../std_data/binary_tree/tree/tree.h"
#include "../../../std_data/vector/vector.h"
#include "../../../collection/collection.h"
#include "../../../utils/utils.h"


typedef struct output {
    char *doc;
    int freq;
} Output;


Vector *read_query (char *query) {
    Vector *words = vector_construct();

    words = string_split(query);

    Vector *unique = vector_unique(words, compara_strings);

    vector_destroy(words);

    return unique;
}

////////////////////////////////////////
////////////////////////////////////////


Tree *load_index(char *index_filename) {
    Tree *index = tree_construct(compara_strings, free, collection_destroy,
        print_string, collection_print, fprint_string, collection_file_print);
    FILE *F = fopen(index_filename, "r");

    if (F == NULL) {
        printf("Erro ao abrir o arquivo %s\n", index_filename);
        exit(1);
    }
    int size;
    fscanf(F, "%d\n", &size);
    // printf("%d\n", size);

    for (int i=0; i<size; i++) {
        char aux[100];
        fscanf(F, "%s\n", aux);
        char *key = strdup(aux);
        // printf ("%s\n", key);
        int num_docs;
        fscanf (F,"%d\n", &num_docs);
        // printf ("%d\n", num_docs);
        Tree *col = tree_construct(compara_strings, free,
                     free, print_string, collection_print, 
                                        fprint_col_key, fprint_col_value);
        for (int j=0; j<num_docs; j++) {
            char aux2[100];
            fscanf (F, "%s ", aux2);
            // char *doc = (char*)malloc(sizeof(char)*(strlen(aux2)+1));
            // memcpy(doc, aux2, strlen(aux2)+1);
            char *doc = strdup(aux2);
            // printf ("%s ", doc);
            int *freq = (int *)malloc(sizeof(int));
            fscanf (F, "%d\n", freq);
            // printf ("%d\n", *freq);
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
    Tree *recommendations = tree_construct(compara_strings, NULL, NULL, print_string, print_string, fprint_string, fprint_string);
    
    // Para cada palavra da query
    for (int i=0; i<vector_size(words); i++) {
        // Obtém a lista de documentos em que a palavra aparecer e as respectivas frequencias
        Tree *col = (Tree *)tree_search(index, vector_get(words, i));
        // Se a palavra não estiver no índice, passa para a próxima
        if (col != NULL) {
            // Para cada documento em que a palavra aparece
            for (int j=0; j<tree_size(col); j++) {
                // Obtém o nome do documento
                char *doc = (char *)tree_get_key_in_order(col, j);
                // Obtém a frequência da palavra no documento
                int *freq = (int *)tree_get_value_in_order(col, j);

                // Se o documento não está na lista de recomendações
                if (tree_search(recommendations, doc) == NULL) {
                    tree_add(recommendations, doc, freq);
                }
                // Se o documento já está na lista de recomendações
                else {
                    int *old_freq = (int *)tree_search(recommendations, doc);
                    int *new_freq = (int *)malloc(sizeof(int));
                    if (old_freq != NULL) {
                        *new_freq = (*freq + (*old_freq));
                    }
                    else {
                        *new_freq = *freq;
                    }                  
                    tree_set_value(recommendations, doc, new_freq);

                }
            }
        }
    }

    double end = get_timestamp();
    printf("TEMPO DE BUSCA: %lf\n", end-start);
    libera_dados(words);
    // free(words);
    // vector_destroy(words);
    // vector_destroy(words);
    return recommendations;
}







// OUTPUT

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
        // printf ("doc = %s || freq = %d\n", doc, *freq);
        // fprintf(F, "%s %d\n", doc, *freq);
        Output *OP = output_construct(doc, *freq);
        // printf ("OP.doc = %s || OP.freq = %d\n", OP->doc, OP->freq);
        vector_push_back(V, OP);
    }

    vector_sort(V, compara_output);

    // printf ("vector_size: %d\n", vector_size(V));
    for (int i=0; i<vector_size(V); i++) {
        if (i == 10) {
            break;
        }
        Output *OP = (Output *)vector_get(V, i);
        fprintf(F, "%s: %d\n", OP->doc, OP->freq);
        // printf ("%s: %d\n", OP->doc, OP->freq);
    }

    for (int i=0; i<vector_size(V); i++) {
        Output *OP = (Output *)vector_get(V, i);
        output_destroy(OP);
    }
    vector_destroy(V);

    fclose(F);
}