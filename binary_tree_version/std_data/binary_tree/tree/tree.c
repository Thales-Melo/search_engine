#include "tree.h"
#include "../node/node.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct Tree {
    Node *root;
    int size;
    CmpFn cmp_fn;
    KeyDestroyFn key_destroy_fn;
    ValDestroyFn val_destroy_fn;
    KeyPrintFn key_print_fn;
    ValPrintFn val_print_fn;
    Key_fPrintFn key_fprint_fn;
    Val_fPrintFn val_fprint_fn;
} Tree;


Tree *tree_construct (CmpFn cmp_fn, KeyDestroyFn key_destroy_fn, ValDestroyFn val_destroy_fn, KeyPrintFn key_print_fn, ValPrintFn val_print_fn, Key_fPrintFn key_fprint_fn, Val_fPrintFn val_fprint_fn) {
    Tree *tree = (Tree*)malloc(sizeof(Tree));

    tree->root = NULL;
    tree->size = 0;
    tree->cmp_fn = cmp_fn;
    tree->key_destroy_fn = key_destroy_fn;
    tree->val_destroy_fn = val_destroy_fn;
    tree->key_print_fn = key_print_fn;
    tree->val_print_fn = val_print_fn;
    tree->key_fprint_fn = key_fprint_fn;
    tree->val_fprint_fn = val_fprint_fn;

    return tree;
}


void tree_destroy (Tree *tree) {
    // libera a memória recursivamente a partir da raiz
    node_destroy_recursive(tree->root, tree->val_destroy_fn, tree->key_destroy_fn);
    if (tree != NULL) {
        free(tree);
        tree = NULL;
    }
}


int tree_size (Tree *tree) {
    return tree->size;
}


data_type tree_root (Tree *tree) {
    return node_value(tree->root);
}


void tree_add (Tree *tree, key_type key, data_type value) {
    tree->root = node_add_recursive(tree->root, key_val_pair_construct(key, value), tree->cmp_fn);
    tree->size++;
}

void tree_set_value (Tree *tree, key_type key, data_type value) {
    Node *node = node_search(tree->root, key, tree->cmp_fn);
    if (node != NULL) {
        node_set_value(node, value);
    }
}

data_type tree_max_value (Tree *tree) {
    if (tree_empty(tree)) {
        return NULL;
    }
    Node *node = tree->root;
    while (node_right(node) != NULL) {
        node = node_right(node);
    }
    return node_value(node);
}


data_type tree_min_value (Tree *tree) {
    if (tree_empty(tree)) {
        return NULL;
    }
    Node *node = tree->root;
    while (node_left(node) != NULL) {
        node = node_left(node);
    }
    return node_value(node);
}

key_type tree_max_key (Tree *tree) {
    if (tree_empty(tree)) {
        return NULL;
    }
    Node *node = tree->root;
    while (node_right(node) != NULL) {
        node = node_right(node);
    }
    return node_key(node);

}

key_type tree_min_key (Tree *tree) {
    if (tree_empty(tree)) {
        return NULL;
    }
    Node *node = tree->root;
    while (node_left(node) != NULL) {
        node = node_left(node);
    }
    return node_key(node);

}


void tree_print (Tree *tree) {
    printf("Tree: \n\n");
    node_print(tree->root, tree->key_print_fn, tree->val_print_fn);
    printf("\n");
}


data_type tree_search(Tree *tree, key_type key) {
    Node *node = node_search(tree->root, key, tree->cmp_fn);
    return node != NULL ? node_value(node): NULL;
}


int tree_contains_key(Tree *tree, key_type key) {
    return node_search(tree->root, key, tree->cmp_fn) != NULL;
}


void tree_remove(Tree *tree, key_type key) {
    tree->root = node_remove(tree->root, key, tree->cmp_fn, tree->val_destroy_fn, tree->key_destroy_fn);
    tree->size--;
}

int tree_empty (Tree *tree) {
    return tree->root == NULL;
}

void tree_pop_max (Tree *tree) {
    tree_remove(tree, tree_max_key(tree));
}

void tree_pop_min (Tree *tree) {
    tree_remove(tree, tree_min_key(tree));
}

// lever order
void tree_print_level_order(Tree *tree) {
   printf("Tree: ");
   node_print_level_order(tree->root, tree->key_print_fn, tree->val_print_fn);
   printf("\n");
}


// pre order
void tree_print_pre_order(Tree *tree) {
    printf("Tree: ");
    node_print_pre_order(tree->root, tree->key_print_fn, tree->val_print_fn);
    printf("\n");
}


// in order
void tree_print_in_order(Tree *tree) {
    printf("Tree: ");
    node_print_in_order(tree->root, tree->key_print_fn, tree->val_print_fn);
    printf("\n");
}


// post order
void tree_print_post_order(Tree *tree) {
    printf("Tree: ");
    node_print_post_order(tree->root, tree->key_print_fn, tree->val_print_fn);
    printf("\n");
}


// FPRINTS (VERSOES PARA ESCRITA EM ARQUIVO)

void tree_file_print_level_order(Tree *tree, FILE *fp) {
    node_file_print_level_order(tree->root, tree->key_fprint_fn, tree->val_fprint_fn, fp);
}

void tree_file_print_in_order(Tree *tree, FILE *fp) {
    node_file_print_in_order(tree->root, tree->key_fprint_fn, tree->val_fprint_fn, fp);

}

void tree_file_print_pre_order(Tree *tree, FILE *fp) {
    node_file_print_pre_order(tree->root, tree->key_fprint_fn, tree->val_fprint_fn, fp);

}

void tree_file_print_post_order(Tree *tree, FILE *fp) {
    node_file_print_post_order(tree->root, tree->key_fprint_fn, tree->val_fprint_fn, fp);
}