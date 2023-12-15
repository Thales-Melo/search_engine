#ifndef _FORWARD_LIST_H_
#define _FORWARD_LIST_H_

#include "fl_node.h"

typedef struct forwardList {
    FL_Node *head;
    FL_Node *last;
    int size;
} ForwardList;

ForwardList *forward_list_construct ();

void forward_list_destroy (ForwardList *FL, void (*free_func)(data_type));

void forward_list_push_front(ForwardList *FL, data_type value);

void forward_list_push_back(ForwardList *FL, data_type value);

data_type forward_list_pop_front(ForwardList *FL);

void forward_list_print (ForwardList *FL, void (*print_fn)(data_type));

int forward_list_size (ForwardList *FL);

#endif