#include "engine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../std_data/vector/vector.h"
#include "../../../word/word.h"
#include "../../../collection/collection.h"
#include "../../../document/document.h"
#include "../../../utils/utils.h"


typedef struct output {
    char *doc;
    int freq;
} Output;


Vector *read_query (char *query) {
    Vector *words = string_split(query);

    Vector *unique = vector_unique(words, compara_strings);

    vector_destroy(words);

    return unique;
}

////////////////////////////////////////
////////////////////////////////////////


Vector *load_index(char *index_filename) {
    Vector *index = vector_construct();
    FILE *F = fopen(index_filename, "r");

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
        Word *word = word_constructor(key);

        
        for (int j=0; j<num_docs; j++) {
            char aux2[100];
            fscanf (F, "%s ", aux2);
            int freq;
            fscanf (F, "%d\n", &freq);
            
            // int idx_word = vector_find(index, word, word_cmp);

            Document *document = document_construct(strdup(aux2), freq);
            // if (idx_word < 0) {
            //     vector_push_back(word->collection->documents, document);
            //     vector_push_back(index, word);
            // }
                
            // else {
            //     Word *aux = vector_get(index, idx_word);
            //     word_destroy(word);
            //     Document *document_aux = vector_get(aux->collection->documents, vector_find(aux->collection->documents, document, document_cmp));
            //     document_aux->frequency += freq;
            //     document_destroy(document);
            // }
        
           
            vector_push_back(word->collection->documents, document);
          

        }

        vector_push_back(index, word);
    }    

    fclose(F);

    return index;
}

Vector *search_docs(Vector *index, char *query) {
    // Palavras da query
    Vector *words = read_query(query);

    // Documentos recomendados e respectivas relevâncias
    Vector *recommendations = vector_construct();
    
    // Para cada palavra da query
    for (int i=0; i<vector_size(words); i++) {
        // Obtém a lista de documentos em que a palavra aparecer e as respectivas frequencias
        Word *aux = word_constructor(vector_get(words, i));
        int idx = vector_find(index, aux, word_cmp);
        // Se a palavra não estiver no índice, passa para a próxima
        if (idx >= 0) {
            Word *word = (Word *)vector_get(index, idx);
            // Para cada documento em que a palavra aparece
            for (int j=0; j<vector_size(word->collection->documents); j++) {
                // Obtém o nome do documento
                char *doc = ((Document *)vector_get(word->collection->documents, j))->document;
                // Obtém a frequência da palavra no documento
                int freq = (((Document *)vector_get(word->collection->documents, j))->frequency);

                Document *document = document_construct(doc, freq);
                // Se o documento não está na lista de recomendações
                if (vector_find(recommendations, document, document_cmp) < 0) {
                    vector_push_back(recommendations, document);
                }
                // Se o documento já está na lista de recomendações
                else {
                    Document *document_aux = vector_get(recommendations, vector_find(recommendations, document, document_cmp));
                    document_aux->frequency += freq;
                    document_destroy(document);
                }
            }
        }
        collection_destroy(aux->collection);
        free(aux);
        aux = NULL;
    }

    libera_dados(words);

    return recommendations;
}

////////////////////////////////////////
// OUTPUT FORMAT
////////////////////////////////////////

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



void search_output(Vector *docs, char* output_file, double duration) {
    FILE *F = fopen(output_file, "w");

    if (F == NULL) {
        printf("Erro ao abrir o arquivo %s\n", output_file);
        exit(1);
    }

    fprintf(F, "Tempo de busca: %lf\n", duration);

    Vector *V = vector_construct();

    for (int i=0; i<vector_size(docs); i++) {
        char *doc = ((Document *)vector_get(docs, i))->document;
        int freq = ((Document *)vector_get(docs, i))->frequency;
        Output *OP = output_construct(doc, freq);
        vector_push_back(V, OP);
    }

    vector_sort(V, compara_output);

    for (int i=0; i<vector_size(V); i++) {
        if (i == 10) {
            break;
        }
        Output *OP = (Output *)vector_get(V, i);
        fprintf(F, "%s: %d\n", OP->doc, OP->freq);
        output_destroy(OP);
    }

    vector_destroy(V);

    fclose(F);
}



void index_loaded_destroy (Vector *index) {
    for (int i=0; i<vector_size(index); i++) {
        Word *word = vector_get(index, i);
        for (int i=0; i<vector_size(word->collection->documents); i++) {
            Document *doc = vector_get(word->collection->documents, i);
            if (doc->document != NULL) {
                free(doc->document);
                doc->document = NULL;
            }
        }
        word_destroy(word);
    }
    vector_destroy(index);
}



void search_destroy (Vector *docs) {
    for (int i=0; i<vector_size(docs); i++) {
        Document *doc = vector_get(docs, i);
        document_destroy(doc);
    }
    vector_destroy(docs);
}