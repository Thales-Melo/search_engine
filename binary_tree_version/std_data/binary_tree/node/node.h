#ifndef _NODE_H_
#define _NODE_H_


#include "../key_val_pair/key_val_pair.h"
#include <stdio.h>

typedef struct Node Node;


Node *node_construct (KeyValPair *key_val, Node *left, Node *right);

void node_destroy_recursive(Node *N, void (*val_destroy_fn)(data_type), void (*key_destroy_fn)(key_type));

void node_destroy (Node *N, void (*val_destroy_fn)(data_type), void (*key_destroy_fn)(key_type));

key_type node_key (Node *N);

data_type node_value (Node *N);

KeyValPair *node_key_val_pair (Node *N);

Node *node_right (Node *N);

Node *node_left (Node *N);

Node *node_add_recursive(Node *node, KeyValPair *key_val, int (*cmp_fn)(data_type, data_type));

void node_print (Node *N, void (*key_print_fn)(key_type), void (*val_print_fn)(data_type));

void node_set_left(Node *N, Node *left);

void node_set_right(Node *N, Node *right);

/////////////////////////////////////////////////////////////

int compare_keys (key_type key1, key_type key2);



/////////////////////////////////////////////////////////////
// FUNÇÕES DE BUSCA
/////////////////////////////////////////////////////////////

Node *node_search (Node *node, key_type *key, int (*cmp_fn)(data_type, data_type));

Node* node_remove_recursive(Node *node, key_type *key, int (*cmp_fn)(data_type, data_type), void (*val_destroy_fn)(data_type), void (*key_destroy_fn)(key_type));

Node *node_remove(Node *root, key_type *key, int (*cmp_fn)(data_type, data_type), void (*val_destroy_fn)(data_type), void (*key_destroy_fn)(key_type));

void node_print_level_order(Node *root, void (*key_print_fn)(key_type), void (*val_print_fn)(data_type));

void node_print_in_order (Node *root, void (*key_print_fn)(key_type), void (*val_print_fn)(data_type));
    
void node_print_pre_order (Node *root, void (*key_print_fn)(key_type), void (*val_print_fn)(data_type));

void node_print_post_order (Node *root, void (*key_print_fn)(key_type), void (*val_print_fn)(data_type));

void node_set_value(Node *N, data_type value);


// FPRINTS (VERSOES PARA ESCRITA EM ARQUIVO)

void node_file_print_level_order(Node *root, void (*key_fprint_fn)(key_type, FILE*), void (*val_fprint_fn)(data_type, FILE*), FILE *fp);


void node_file_print_in_order (Node *root, void (*key_fprint_fn)(key_type, FILE*), void (*val_fprint_fn)(data_type, FILE*), FILE *fp);


void node_file_print_pre_order(Node *root, void (*key_fprint_fn)(key_type, FILE*), void (*val_fprint_fn)(data_type, FILE*), FILE *fp);


void node_file_print_post_order(Node *root, void (*key_fprint_fn)(key_type, FILE*), void (*val_fprint_fn)(data_type, FILE*), FILE *fp);

key_type node_index_key_in_order(Node *root, int index);

data_type node_index_value_in_order(Node *root, int index);


#endif