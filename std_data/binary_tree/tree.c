#include "tree.h"
#include "../node/node.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct Tree {
    Node *root;
    int size;
} Tree;

Tree *tree_construct () {
    Tree *tree = (Tree*)malloc(sizeof(Tree));
    tree->root = node_construct(NULL, NULL, NULL);
}