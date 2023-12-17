#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdio.h>

#include "../std_data/vector/vector.h"


Vector *string_split(char *str);

void libera_dados(Vector *words);

// precisamos fazer essa funcao porque as funcoes do vector esperam como argumento
// uma funcao que recebe dois void* e nao dois char*.
int compara_strings(void *a, void *b);

double get_timestamp();


#endif