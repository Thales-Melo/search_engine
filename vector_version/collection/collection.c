#include "collection.h"
#include <stdio.h>
#include <stdlib.h>
#include "../document/document.h"
#include <string.h>

Collection *collection_construct(collection_destroy_fn destroy_fn) {
    Collection *collection = (Collection *)malloc(sizeof(Collection));
    collection->documents = vector_construct(destroy_fn);
    collection->destroy_fn = destroy_fn;
    return collection;
}

void collection_destroy(Collection *collection) {
    if (collection == NULL) {
        printf ("collection_destroy: collection == NULL\n");
        return;
    }
    if (collection->documents != NULL) {
        for (int i=0; i<vector_size(collection->documents); i++) {
            collection->destroy_fn(vector_get(collection->documents, i));
        }
        // free(collection->documents);
        // collection->documents = NULL;
        vector_destroy(collection->documents);
    }

    free(collection);
    collection = NULL;
}

void collection_print(Collection *collection) {
    if (collection == NULL) {
        printf ("collection_print: collection == NULL\n");
        return;
    }
    printf ("Collection:\n");
    
    for (int i=0; i<vector_size(collection->documents); i++) {
        printf ("Document %d:\n", i);
        collection->destroy_fn(vector_get(collection->documents, i));
    }
}

void collection_file_print(Collection *collection, FILE *file) {
    if (collection == NULL) {
        printf ("collection_file_print: collection == NULL\n");
        return;
    }

    fprintf (file, "%d\n", vector_size(collection->documents));

    for (int i=0; i<vector_size(collection->documents); i++) {
        document_file_print(vector_get(collection->documents, i), file);
        // collection->destroy_fn(vector_get(collection->documents, i));
    }
}


void collection_add_document(Collection *collection, data_type document) {
    if (collection == NULL) {
        printf ("collection_add: collection == NULL\n");
        return;
    }
    if (document == NULL) {
        printf ("collection_add: document == NULL\n");
        return;
    }

    if (collection_contains(collection, document)) {
        // printf ("collection_add: collection_contains(collection, document)\n");
        Document *doc = vector_get(collection->documents, vector_find(collection->documents, document, document_cmp));
        document_destroy(document);
        document_grow_frequency(doc);
        return;
    }

    else {
        vector_push_back(collection->documents, document);
    }   
}


int collection_contains(Collection *collection, data_type document) {
    if (collection == NULL) {
        printf ("collection_contains: collection == NULL\n");
        return 0;
    }
    if (document == NULL) {
        printf ("collection_contains: document == NULL\n");
        return 0;
    }

    // printf ("collection_contains: vector_size(collection->documents) = %d\n", vector_size(collection->documents));
    for (int i=0; i<vector_size(collection->documents); i++) {
        if (strcmp(((Document *)vector_get(collection->documents, i))->document, ((Document *)document)->document) == 0) {
            // printf("collection contém documento\n");
            return 1;
        }
    }
    // printf("collection nao contem documento\n");

    return 0;

}

data_type collection_get(Collection *collection, data_type word) {
    if (collection == NULL) {
        printf ("collection_get: collection == NULL\n");
        return NULL;
    }
    if (word == NULL) {
        printf ("collection_get: word == NULL\n");
        return NULL;
    }

    for (int i=0; i<vector_size(collection->documents); i++) {
        if (strcmp(((Document *)vector_get(collection->documents, i))->document, (char*)word) == 0) {
            return vector_get(collection->documents, i);
        }
    }

    return NULL;
}



void fprint_col_value(data_type value, FILE *file) {
    fprintf (file, "%d\n", *(int *)value);
}

void fprint_col_key(data_type key, FILE *file) {
    fprintf (file, "%s ", (char *)key);
}