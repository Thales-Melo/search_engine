#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdio.h>

#include "../std_data/vector/vector.h"


Vector *string_split(char *str);

void libera_dados(Vector *words);

// precisamos fazer essa funcao porque as funcoes do vector esperam como argumento
// uma funcao que recebe dois void* e nao dois char*.
int compara_strings(void *a, void *b);

void print_string(void *a);

void print_key(void *a);

void print_val(void *a);

double get_timestamp();

// void fprint_key(void *a, FILE *f);

// void fprint_val(void *a, FILE *f);

void fprint_string(void *a, FILE *f);


#endif