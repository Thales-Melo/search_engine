#include "tree.h"
#include "../node/node.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Tree {
    Node *root;
    int size;
} Tree;

Tree *tree_construct () {
    Tree *tree = (Tree*)malloc(sizeof(Tree));
    // tree->root = node_construct(NULL, NULL, NULL, NULL);
    tree->root = NULL;
    return tree;
}

void tree_destroy (Tree *tree, void (*free_func)(data_type)) {
    // libera a memória recursivamente a partir da raiz
    node_destroy(tree->root, free_func);
    if (tree != NULL) {
        free(tree);
    }
}

int tree_size (Tree *tree) {
    return tree->size;
}

data_type tree_root (Tree *tree) {
    return node_value(tree->root);
}

void tree_add (Tree *tree, key_type key, data_type value) {
    tree->root = node_add_recursive(tree->root, key, value);
}

data_type tree_max (Tree *tree) {
    Node *node = tree->root;
    while (node_right(node) != NULL) {
        node = node_right(node);
    }
    return node_value(node);
}

data_type tree_min (Tree *tree) {
    Node *node = tree->root;
    while (node_left(node) != NULL) {
        node = node_left(node);
    }
    return node_value(node);
}

void tree_print (Tree *tree) {
    printf("Tree: ");
    node_print(tree->root);
    printf("\n");
}

data_type tree_search(Tree *tree, key_type key) {
    Node *node = node_search(tree->root, key);
    return node != NULL ? node_value(node): NULL;
}

int tree_contains_key(Tree *tree, key_type key) {
    return node_search(tree->root, key) != NULL;
}

void tree_remove(Tree *tree, key_type key) {
    tree->root = node_remove(tree->root, key);
    tree->size--;
}

// lever order
void tree_print_level_order(Tree *tree) {
    printf("Tree: ");
    node_print_level_order(tree->root);
    printf("\n");
}

// pre order
void tree_print_pre_order(Tree *tree) {
    printf("Tree: ");
    node_print_pre_order(tree->root);
    printf("\n");
}

// in order
void tree_print_in_order(Tree *tree) {
    printf("Tree: ");
    node_print_in_order(tree->root);
    printf("\n");
}

// post order
void tree_print_post_order(Tree *tree) {
    printf("Tree: ");
    node_print_post_order(tree->root);
    printf("\n");
}