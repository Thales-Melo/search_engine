#include "key_val_pair.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct KeyValPair {
    key_type key;
    data_type value;
} KeyValPair;


KeyValPair *key_val_pair_construct(void *key, void *value)
{
    KeyValPair *key_val = malloc(sizeof(KeyValPair));

    key_val->key = key;
    key_val->value = value;

    return key_val;
}


void key_val_pair_destroy(KeyValPair *key_val, void (*val_destroy_fn)(data_type), void (*key_destroy_fn)(key_type))
{   
    if (key_val == NULL) {
        return;
    }
    if (val_destroy_fn != NULL) {
        if (key_val->value != NULL) {
            val_destroy_fn(key_val->value);
            key_val->value = NULL;
        }
    }
    if (key_destroy_fn != NULL) {
        if (key_val->key != NULL) {
            printf ("key_val_pair_destroy: key_destroy_fn != NULL\n");
            // printf ("%s\n", (char*)key_val->key);
            key_destroy_fn(key_val->key);
            key_val->key = NULL;  
        }
    }

    if (key_val != NULL) {
        free(key_val);
        key_val = NULL;
    }
}


key_type key_val_pair_key(KeyValPair *key_val)
{
    return key_val->key;
}


data_type key_val_pair_value(KeyValPair *key_val)
{
    return key_val->value;
}


void key_val_pair_set_value(KeyValPair *key_val, data_type value)
{
    key_val->value = value;
}


void key_val_pair_set_key(KeyValPair *key_val, key_type key)
{
    key_val->key = key;
}


int key_val_pair_cmp(data_type a, data_type b, int (*cmp_fn)(data_type, data_type))
{
    return cmp_fn(a, b);
}


void key_val_pair_print(KeyValPair *key_val, void (*print_key)(key_type), void (*print_value)(data_type))
{   
    print_key(key_val->key);
    print_value(key_val->value);
    printf ("\n");
}


void key_val_pair_file_print(KeyValPair *key_val, void (*f_print_key)(key_type, FILE*), void (*f_print_value)(data_type, FILE*), FILE *file)
{
    f_print_key(key_val->key, file);
    f_print_value(key_val->value, file);
    // fprintf (file, "\n");
}
