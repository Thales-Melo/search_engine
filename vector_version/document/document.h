#ifndef _DOCUMENT_H_
#define _DOCUMENT_H_

#include <stdio.h>

typedef struct Document {
    char *document;
    int frequency;
} Document;

Document *document_construct(char *document, int frequency);

void document_destroy(Document *document);

void document_print(Document *document);

void document_file_print(Document *document, FILE *file);

void document_grow_frequency(Document *document);

int document_cmp (void *a, void *b);


#endif