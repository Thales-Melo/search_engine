#ifndef _WORD_H_
#define _WORD_H_

#include "../std_data/vector/vector.h"

typedef struct Word {
    char *word; // key
    Collection *collection; // value
} Word;


Word *word_constructor(char *word);

void word_destroy(Word *W);

void word_add(Word *W, char *word);

void word_print(Word *W);

int word_cmp(data_type word1, data_type word2);


#endif