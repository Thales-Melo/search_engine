#include "engine.h"
#include <stdio.h>
#include "../../../utils/utils.h"
#include <stdlib.h>
#include "../../../collection/collection.h"
#include <string.h>
#include "../../../std_data/vector/vector.h"
#include "../../../std_data/binary_tree/tree/tree.h"


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
    printf("%d\n", size);

    for (int i=0; i<size; i++) {
        char aux[100];
        fscanf(F, "%s\n", aux);
        char *key = strdup(aux);
        printf ("%s\n", key);
        int num_docs;
        fscanf (F,"%d\n", &num_docs);
        printf ("%d\n", num_docs);
        Collection *col = collection_construct(tree_construct(compara_strings, free,
                     free, print_string, collection_print, 
                                        fprint_col_key, fprint_col_value));
        for (int j=0; j<num_docs; j++) {
            char aux2[100];
            fscanf (F, "%s ", aux2);
            char *doc = strdup(aux2);
            printf ("%s ", doc);
            int *freq = (int *)malloc(sizeof(int));
            fscanf (F, "%d\n", freq);
            printf ("%d\n", *freq);
            tree_add(col->documents, doc, freq);
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
    Tree *recommendations = tree_construct(compara_strings, free, free, print_string, print_string, fprint_string, fprint_string);
    
    // Para cada palavra da query
    for (int i=0; i<vector_size(words); i++) {
        printf ("WORD: %s\n", (char *)vector_get(words, i));
        // Obtém a lista de documentos em que a palavra aparecer e as respectivas frequencias
        Collection *col = (Collection *)tree_search(index, vector_get(words, i));
        // Se a palavra não estiver no índice, passa para a próxima
        if (col != NULL) {
            // Para cada documento em que a palavra aparece
            printf ("tree_size: %d\n", tree_size(col->documents));
            for (int j=0; j<tree_size(col->documents); j++) {
                
                // Obtém o nome do documento
                char *doc = (char *)tree_get_key_in_order(col->documents, j);
                printf ("doc: %s\n", doc);
                // Obtém a frequência da palavra no documento
                void *result = tree_get_value_in_order(col->documents, j);
                // int freq = *(int *)result;
                int *freq = (int *)malloc(sizeof(int));
                *freq = *(int *)result;
                printf ("freq_A: %d\n", *freq);
                // Se o documento não está na lista de recomendações
                if (tree_search(recommendations, doc) == NULL) {
                    tree_add(recommendations, doc, freq);
                }
                // Se o documento já está na lista de recomendações
                else {
                    int *old_freq = (int *)malloc(sizeof(int));
                    old_freq = (int *)tree_search(recommendations, doc);
                    int *new_freq = (int *)malloc(sizeof(int));
                    if (old_freq != NULL) {
                        printf ("old_freq: %d\n", *old_freq);
                        *new_freq = (*freq + (*old_freq));
                    }
                    else {
                        *new_freq = *freq;
                    }
                    printf ("freq_B: %d\n", *freq);
                    printf ("new_freq: %d\n", *new_freq);
                    
                    tree_set_value(recommendations, doc, new_freq);
                }
            }
        }
    }

    double end = get_timestamp();

    printf("TEMPO DE BUSCA: %lf\n", end-start);

    return recommendations;
}







// OUTPUT

Output *output_construct(char *doc, int freq) {
    Output *output = (Output *)malloc(sizeof(Output));
    output->doc = strdup(doc);
    output->freq = freq;

    return output;
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
        printf ("doc = %s || freq = %d\n", doc, *freq);
        // fprintf(F, "%s %d\n", doc, *freq);
        Output *OP = output_construct(doc, *freq);
        printf ("OP.doc = %s || OP.freq = %d\n", OP->doc, OP->freq);
        vector_push_back(V, OP);
    }

    vector_sort(V, compara_output);

    printf ("vector_size: %d\n", vector_size(V));
    for (int i=0; i<vector_size(V); i++) {
        Output *OP = (Output *)vector_get(V, i);
        fprintf(F, "%s: %d\n", OP->doc, OP->freq);
        printf ("%s: %d\n", OP->doc, OP->freq);
    }

    vector_destroy(V);

    fclose(F);
}