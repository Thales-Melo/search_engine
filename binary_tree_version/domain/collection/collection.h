#ifndef _COLLECTION_H_
#define _COLLECTION_H_

#include "../../std_data/binary_tree/tree/tree.h"

// Cada nó na árvore "index" é um tipo Colection
// Cada nó na árvore "Colection->documents" é um tipo Document
typedef struct colection {
    Tree *documents;
} Collection;

Collection *colection_construct(Tree *documents, int freq);

void collection_destroy(Collection *collection);

void collection_print(Collection *collection);

#endif