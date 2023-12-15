#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "std_data/vector/vector.h"
#include "std_data/binary_tree/tree/tree.h"
#include "utils/utils.h"

int main(int argc, char **argv)
{
    Tree *tree = tree_construct(compara_strings, NULL, NULL, print_key, print_val, fprint_string, fprint_string);

    printf ("\n\n");
    
    tree_add(tree, "flamengo", "flamengo");
    tree_add(tree, "abacate", "abacate");
    tree_add(tree, "flamengo", "flamengo");
    tree_add(tree, "dado", "dado");
    tree_add(tree, "hillsong", "hillsong");
    tree_add(tree, "castanheiras", "castanheiras");
    tree_add(tree, "bola", "bola");

    tree_print(tree);

    // tree_remove(tree, "bola");
    // tree_remove(tree, "castanheiras");
    // tree_remove(tree, "dado");
    // tree_remove(tree, "abacate");
    // tree_remove(tree, "hillsong");
    tree_remove(tree, "flamengo");

    tree_pop_max(tree);
    tree_pop_max(tree);
    tree_pop_min(tree);
    tree_pop_min(tree);

    printf ("\n\nAPÓS A REMOÇÃO: \n\n");

    tree_print(tree);

    tree_destroy(tree);

    printf ("\n\n");

    return 0;
}