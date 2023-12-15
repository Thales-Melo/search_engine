#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "std_data/vector/vector.h"
#include "std_data/binary_tree/tree/tree.h"
#include "utils/utils.h"
#include "search_program/domain/load_index/load_index.h"

#define INDEX_FILE argv[1]
#define OUTPUT argv[2]

int main(int argc, char **argv)
{
    Tree *index = load_index(INDEX_FILE);

    return 0;
}