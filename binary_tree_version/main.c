#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "std_data/vector/vector.h"
#include "std_data/binary_tree/tree/tree.h"
#include "utils/utils.h"

int main(int argc, char **argv)
{
    // char texto[100];

    // printf("Digite um texto: ");
    // scanf("%[^\n]", texto);

    // Vector *words = string_split(texto);
    // Vector *unique = vector_unique(words, compara_strings);

    // printf("Lista de palavras diferentes: \n");
    // for (int i = 0; i < vector_size(unique); i++)
    //     printf("%s\n", (char *)vector_get(unique, i));

    // libera_dados(words);

    // // o vector unique faz copia de ponteiros (shallow copy) e, por isso, nao
    // // precisa liberar os dados do vetor antes de remove-lo. Eles ja serao
    // // liberados acima.
    // vector_destroy(unique);

    Tree *tree = tree_construct(compara_strings, NULL, NULL, print_key, print_val);

    printf ("\n\n");
    
    tree_add(tree, "hillsong", "hillsong");
    tree_add(tree, "abacate", "abacate");
    tree_add(tree, "flamengo", "flamengo");
    // tree_add(tree, "flamengo", "flamengo");
    tree_add(tree, "dado", "dado");
    tree_add(tree, "castanheiras", "castanheiras");
    tree_add(tree, "bola", "bola");

    tree_print(tree);

    tree_remove(tree, "bola");
    tree_remove(tree, "castanheiras");
    tree_remove(tree, "dado");
    tree_remove(tree, "abacate");
    tree_remove(tree, "hillsong");
    // tree_remove(tree, "flamengo");

    printf ("\n\n");

    tree_print(tree);

    tree_destroy(tree);

    printf ("\n\n");

    return 0;
}