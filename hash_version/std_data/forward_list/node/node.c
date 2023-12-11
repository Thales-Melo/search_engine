
#include <stdlib.h>
#include "node.h"

Node *node_construct(data_type value, Node *next)
{
    Node *n = (Node *)malloc(sizeof(Node));
    n->value = value;
    n->next = next;
    return n;
}

void node_destroy(Node *n, void (*free_func)(data_type))
{
    if (n->value != NULL) {
        free_func(n->value);
        n->value = NULL;
    }
    if (n != NULL) {
        free(n);
        n = NULL;
    }
}

void only_node_destroy(Node *n)
{
    if (n != NULL) {
        free(n);
        n = NULL;
    }
}