#include "load_index.h"
#include <stdio.h>
#include "../../../utils/utils.h"
#include <stdlib.h>
#include "../../../collection/collection.h"
#include <string.h>

Tree *load_index(char *filename) {
    Tree *index = tree_construct(compara_strings, free, collection_destroy,
        print_string, collection_print, fprint_string, collection_file_print);
    FILE *F = fopen(filename, "r");

    if (F == NULL) {
        printf("Erro ao abrir o arquivo %s\n", filename);
        exit(1);
    }
    int size;
    fscanf(F, "%d\n", &size);
    printf("%d\n", size);

    for (int i=0; i<size; i++) {
        char aux[100];
        fscanf(F, "%s\n", aux);
        // aux[strlen(aux)-1] = '\0'; // Remove o \n no final
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
            // aux2[strlen(aux2)-1] = '\0'; // Remove o espaço no final
            char *doc = strdup(aux2);
            printf ("%s ", doc);
            int freq;
            fscanf (F, "%d\n", &freq);
            printf ("%d\n", freq);
            tree_add(col->documents, doc, &freq);
        }

        tree_add(index, key, col);
    }    

    fclose(F);

    return index;
}




// Tree *load_index(char *filename) {
//     FILE *file = fopen(filename, "r");
//     if (file == NULL) {
//         printf("Error opening file %s\n", filename);
//         exit(1);
//     }

//     int size;
//     fscanf(file, "%d\n", &size);

//     Tree *index = tree_construct();

//     for (int i = 0; i < size; i++) {
//         char *word = (char *)malloc(WORD_SIZE * sizeof(char));
//         fscanf(file, "%s ", word);

//         int *value = (int *)malloc(sizeof(int));
//         fscanf(file, "%d\n", value);

//         tree_add(index, word, value);
//     }

//     fclose(file);

//     return index;
// }