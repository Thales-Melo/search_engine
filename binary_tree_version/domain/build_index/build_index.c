#include "build_index.h"
#include <stdlib.h>
#include "../../std_data/vector/vector.h"

// Cada nó na árvore "index" é um tipo Colection
// Cada nó na árvore "Colection->documents" é um tipo Document
typedef struct colection {
    Tree *documents;
} Colection;

// Um tipo Document armazena o nome do arquivo e a frequência da palavra no arquivo
typedef struct document {
    char *file_name;
    int freq;
} Document;


Colection *colection_construct(Tree *documents, int freq) {
    Colection *colection = (Colection *)malloc(sizeof(Colection));
    colection->documents = documents;
    return colection;
}

void colection_destroy(Colection *colection) {
    tree_destroy(colection->documents);
    free(colection);
}

void colection_print(Colection *colection) {
    tree_print(colection->documents);
}
