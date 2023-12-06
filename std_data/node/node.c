#include "node.h"
#include "../../utils/utils.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    data_type value;
    Node *left;
    Node *right;
} Node;

Node *node_construct (data_type value, Node *left, Node *right) {
    Node *N= (Node*)malloc(sizeof(Node));

    N->value = value;
    N->left = left;
    N->right = right;

    return N;
}

void node_destroy (Node *N, void (*free_func)(data_type)) {
    free_func(N->value);
    free(N);
}