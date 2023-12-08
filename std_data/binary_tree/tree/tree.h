#ifndef _TREE_H_
#define _TREE_H_

#include "../../../utils/utils.h"
#include "../node/node.h"

typedef struct Tree Tree;

Tree *tree_construct ();

// Incompleta
void tree_destroy (Tree *tree, void (*free_func)(data_type));

int tree_size (Tree *tree);

data_type tree_root (Tree *tree);

void tree_add(Tree *tree, key_type key, data_type value);

data_type tree_max (Tree *tree);

data_type tree_min (Tree *tree);

void tree_print (Tree *tree);

// Node *tree_search (Tree *tree, key_type key);

// void tree_delete (Tree *tree, Node *z, void (*free_func)(data_type));

// void tree_remove (Tree *tree, key_type key, void (*free_func)(data_type));

#endif