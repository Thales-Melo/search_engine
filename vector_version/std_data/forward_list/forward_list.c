#include "forward_list.h"
#include <stdio.h>
#include <stdlib.h>

ForwardList *forward_list_construct () {
    ForwardList *FL = (ForwardList*)malloc(sizeof(ForwardList));

    FL->head = NULL;
    FL->last = NULL;
    FL->size = 0;

    return FL;
}

void forward_list_destroy (ForwardList *FL, void (*free_func)(data_type)) {
    FL_Node *aux = FL->head;
    while (aux != NULL) {
        FL->head = aux->next;
        // fl_node_destroy(aux, free_func);
        data_type value = aux->value;
        if (free_func != NULL) {
            if (value != NULL) {
                free_func(value);
            }
        }
        fl_node_destroy(aux);
        aux = FL->head;
    }

    free (FL);
    FL = NULL;
}

void forward_list_push_front(ForwardList *FL, data_type value) {
    FL_Node *aux = FL->head;
    FL->head = fl_node_construct(value, aux);
    if (FL->head == NULL) {
        FL->last = FL->head;
    }
    FL->size++;
} 

void forward_list_push_back(ForwardList *FL, data_type value) {
    if (FL->head == NULL) {
        FL->head = FL->last = fl_node_construct(value, NULL);
    }
    else {
        FL_Node *aux = FL->last;
        aux->next = fl_node_construct(value, NULL);
        FL->last = aux->next;
    }
    FL->size++;
}

data_type forward_list_pop_front(ForwardList *FL) {
    FL_Node *aux = FL->head;
    FL->head = aux->next;
    FL->size--;
    return fl_node_destroy(aux); 
}

void forward_list_print (ForwardList *FL, void (*print_fn)(data_type)) {
    FL_Node *aux = FL->head;
    while (aux != NULL) {
        print_fn(aux->value);
        printf ("\n");
        aux = aux->next;
    }
}

int forward_list_size (ForwardList *FL) {
    return FL->size;
}