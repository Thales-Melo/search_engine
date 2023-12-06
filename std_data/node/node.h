#ifndef _NODE_H_
#define _NODE_H_

typedef struct Node Node;

Node *node_construct (data_type value, Node *left, Node *right);

void node_destroy (Node *N, void (*free_func)(data_type));


#endif