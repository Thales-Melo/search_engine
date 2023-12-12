#ifndef _KEY_VAL_PAIR_H_
#define _KEY_VAL_PAIR_H_


typedef struct KeyValPair KeyValPair;


typedef void* key_type;

typedef void* data_type;


KeyValPair *key_val_pair_construct(void *key, void *value);

void key_val_pair_destroy(KeyValPair *key_val, void (*val_destroy_fn)(data_type), void (*key_destroy_fn)(key_type));

key_type key_val_pair_key(KeyValPair *key_val);

data_type key_val_pair_value(KeyValPair *key_val);

void key_val_pair_set_value(KeyValPair *key_val, data_type value);

void key_val_pair_set_key(KeyValPair *key_val, key_type key);

int key_val_pair_cmp(data_type a, data_type b, int (*cmp_fn)(data_type, data_type));

void key_val_pair_print(KeyValPair *key_val, void (*print_key)(key_type), void (*print_value)(data_type));


#endif