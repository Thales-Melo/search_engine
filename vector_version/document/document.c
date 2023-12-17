#include "document.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Document *document_construct(char *document, int frequency) {
    Document *doc = (Document *)malloc(sizeof(Document));
    doc->document = document;
    doc->frequency = frequency;
    return doc;
}

void document_destroy(Document *document) {
    if (document == NULL) {
        printf ("document_destroy: document == NULL\n");
        return;
    }
    // if (document->document != NULL) {
    //     free(document->document);
    //     document->document = NULL;
    // }

    free(document);
    document = NULL;
}

void document_print(Document *document) {
    printf ("%s ", document->document);
    printf ("%d\n", document->frequency);
}

void document_file_print(Document *document, FILE *file) {
    fprintf (file, "%s ", document->document);
    fprintf (file, "%d\n", document->frequency);
}

void document_grow_frequency(Document *document) {
    document->frequency++;
}

int document_cmp (void *a, void *b) {
    Document *A = (Document *)a;
    Document *B = (Document *)b;

    return strcmp(A->document, B->document);
}