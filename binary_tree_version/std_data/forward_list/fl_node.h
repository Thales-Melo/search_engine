#ifndef _FL_NODE_H_
#define _FL_NODE_H_

typedef void* data_type;

typedef struct fl_node {
    data_type value;
    struct fl_node *next;
} FL_Node;

FL_Node *fl_node_construct (data_type value, FL_Node *next);

data_type fl_node_destroy (FL_Node *n);

void fl_node_print (FL_Node *n, void (*print_fn)(data_type));


#endif