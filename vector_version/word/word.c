#include "word.h"
#include "../collection/collection.h"
#include "../document/document.h"

Word *word_constructor(char *word) {
    Word *W = (Word *)malloc(sizeof(Word));
    W->word = word;
    W->collection = collection_construct(document_destroy);
    return W;
}

void word_destroy(Word *W) {
    if (W == NULL) {
        printf ("word_destroy: W == NULL\n");
        return;
    }
    if (W->word != NULL) {
        free(W->word);
        W->word = NULL;
    }
    if (W->collection != NULL) {
        collection_destroy(W->collection);
        W->collection = NULL;
    }

    free(W);
    W = NULL;
}

void word_add(Word *W, char *word) {
    if (W == NULL) {
        printf ("word_add: W == NULL\n");
        return;
    }
    if (W->collection == NULL) {
        printf ("word_add: W->collection == NULL\n");
        return;
    }
    if (word == NULL) {
        printf ("word_add: word == NULL\n");
        return;
    }
    if (collection_contains(W->collection, word)) {
        Document *doc = collection_get(W->collection, word);
        document_grow_frequency(doc);
    } else {
        Document *doc = document_construct(word, 1);
        collection_add(W->collection, doc);
    }
}

void word_print(Word *W) {
    if (W == NULL) {
        printf ("word_print: W == NULL\n");
        return;
    }
    printf ("%s\n", W->word);
    collection_print(W->collection);
}


int word_cmp(data_type word1, data_type word2) {
    Word *W1 = (Word *)word1;
    Word *W2 = (Word *)word2;

    return strcmp(W1->word, W2->word);
}