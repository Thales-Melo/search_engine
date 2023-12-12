#ifndef _TREE_H_
#define _TREE_H_

#include "../node/node.h"

typedef struct Tree Tree;

typedef int (*CmpFn)(void *, void *);
typedef void (*KeyDestroyFn)(void *);
typedef void (*ValDestroyFn)(void *);
typedef void (*KeyPrintFn)(void *);
typedef void (*ValPrintFn)(void *);


Tree *tree_construct (CmpFn cmp_fn, KeyDestroyFn key_destroy_fn, ValDestroyFn val_destroy_fn, KeyPrintFn key_print_fn, ValPrintFn val_print_fn);

void tree_destroy (Tree *tree);

int tree_size (Tree *tree);

data_type tree_root (Tree *tree);

void tree_add (Tree *tree, key_type key, data_type value);

data_type tree_max (Tree *tree);

data_type tree_min (Tree *tree);

void tree_print (Tree *tree);

int tree_empty (Tree *tree);

//////////////////////////////////////////////////

data_type tree_search(Tree *tree, key_type key);

int tree_contains_key(Tree *tree, key_type key);

void tree_remove(Tree *tree, key_type key);

// lever order
// void tree_print_level_order(Tree *tree);

// pre order
void tree_print_pre_order(Tree *tree);

// in order
void tree_print_in_order(Tree *tree);

// post order
void tree_print_post_order(Tree *tree);


#endif