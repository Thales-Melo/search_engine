#include "collection.h"


Collection *colection_construct(Tree *documents, int freq) {
    Collection *collection = (Collection *)malloc(sizeof(Collection));
    collection->documents = documents;
    return collection;
}

void collection_destroy(Collection *collection) {
    tree_destroy(collection->documents);
    free(collection);
}

void collection_print(Collection *collection) {
    tree_print(collection->documents);
}
