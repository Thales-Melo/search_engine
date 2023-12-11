#ifndef _NODE_H_
#define _NODE_H_

#include "../../../utils/utils.h"

typedef struct Node Node;


Node *node_construct (key_type key, data_type value, Node *left, Node *right);

void node_destroy (Node *N, void (*free_func)(data_type));

key_type node_key (Node *N);

data_type node_value (Node *N);

Node *node_right (Node *N);

Node *node_left (Node *N);

Node *node_add_recursive(Node *node, key_type key, data_type value);

void node_print (Node *N);

Node *node_parent(Node *N);

void node_set_left(Node *N, Node *left);

void node_set_right(Node *N, Node *right);

//////////////////////////////////////////////////

Node *node_find_min(Node *node);

Node *node_find_max(Node *node);

// Node *node_remove(Node *root, key_type key, void (*free_func)(data_type));

//////////////////////////////////////////////////

Node *node_search (Node *node, key_type key);

Node *node_remove(Node *root, key_type key);


#endif