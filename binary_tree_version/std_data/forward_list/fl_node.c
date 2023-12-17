#include <stdio.h>
#include <stdlib.h>
#include "fl_node.h"


FL_Node *fl_node_construct (data_type value, FL_Node *next) {
    FL_Node *n = (FL_Node*)malloc(sizeof(FL_Node));
    n->value = value;
    n->next = next;

    return n;
}



data_type fl_node_destroy (FL_Node *n) {
    data_type value = n->value;

    if (n != NULL) {
        free(n);
        n = NULL;
    }

    return value;
}



void fl_node_print (FL_Node *n, void (*print_fn)(data_type)) {
    print_fn(n->value);
}