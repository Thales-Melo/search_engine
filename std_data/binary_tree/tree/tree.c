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

// void transplant(Tree *tree, Node *u, Node *v) {
//     if (u == tree->root) {
//         tree->root = v;
//     } 
//     else {
//         Node *parent = tree->root;
//         while (parent != NULL && node_left(parent) != u && node_right(parent) != u) {
//             if (node_key(u) < node_key(parent)) {
//                 parent = node_left(parent);
//             } 
//             else {
//                 parent = node_right(parent);
//             }
//         }
        
//         if (parent != NULL) {
//             if (node_left(parent) == u) {
//                 set_node_left(parent, v);
//             } 
//             else {
//                 set_node_right(parent, v);
//             }
//         }
//     }
// }

// void tree_delete(Tree *tree, Node *z, void (*free_func)(data_type)) {
//     if (node_left(z) == NULL) {
//         transplant(tree, z, node_right(z));
//     } else if (node_right(z) == NULL) {
//         transplant(tree, z, node_left(z));
//     } 
//     else {
//         Node *y = node_left(z);
//         while (node_right(y) != NULL) {
//             y = node_right(y);
//         }

//         if (node_parent(y) != z) {
//             transplant(tree, y, node_right(y));
//             set_node_right(y, node_right(z));
//         }

//         transplant(tree, z, y);
//         set_node_left(y, node_left(z));
//     }

//     // printf ("ENTROU NO DELETE\n");
//     // exit(1);
//     // free_func(node_value(z));
//     if (z != NULL){ 
//         free(z);
//     z = NULL;
//     tree->size--;
// }


// Node *tree_search (Tree *tree, key_type key) {
//     Node *node = tree->root;
//     while (node != NULL && strcmp(key, node_key(node)) != 0) {
//         if (strcmp(key, node_key(node)) < 0) {
//             node = node_left(node);
//         } 
//         else {
//             node = node_right(node);
//         }
//         printf ("\nnode = %s\n", node_key(node));
//         printf ("key = %s\n", key);
//     }
//     return node;
// }

// void tree_remove (Tree *tree, key_type key, void (*free_func)(data_type)) {
//     Node *z = tree_search(tree, key);
//     node_print(z);
//     if (z != NULL) {
//         tree_delete(tree, z, free_func);
//     }
// }