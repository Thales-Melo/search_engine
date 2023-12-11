#ifndef _UTILS_H_
#define _UTILS_H_


#include "../std_data/vector/vector.h"


typedef char* key_type;
typedef void* data_type;


Vector *string_split(char *str);

void libera_dados(Vector *words);

// precisamos fazer essa funcao porque as funcoes do vector esperam como argumento
// uma funcao que recebe dois void* e nao dois char*.
int compara_strings(void *a, void *b);


#endif