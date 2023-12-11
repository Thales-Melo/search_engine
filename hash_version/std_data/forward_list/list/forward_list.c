#include "forward_list.h"
#include <stdio.h>
#include <stdlib.h>

ForwardList *forward_list_construct() {
    ForwardList *l = (ForwardList*)malloc(sizeof(ForwardList));
    l->size=0;
    l->head=NULL;
    return l;
}

int forward_list_size(ForwardList *l) {
    return l->size;
}

void forward_list_push_front(ForwardList *l,  data_type data) {
    Node *aux = l->head;
    l->head = node_construct(data, aux);
    l->size++; 
}

void forward_list_print(ForwardList *l, void (*print_fn)(data_type)) {
    Node *aux = l->head;
    //printf ("[");
    for (int i=0; i<l->size; i++) {
        print_fn(aux->value);
        aux=aux->next;

        if (i!=l->size-1) {
            printf ("\n");
        }
    }
    //printf ("]");
    printf ("\n\n");
}

void *forward_list_get(ForwardList *l, int i) {
    if (i==0) {
        return l->head->value;
    }
    Node *aux = l->head;

    for (int j=0; j<i; j++) {
        aux = aux->next;
    }

    return aux->value;
}

void *forward_list_pop_front(ForwardList *l, void (*free_func)(data_type)) {
    Node *aux = l->head;
    void *val = aux->value;

    l->head = aux->next;
    l->size--;
    
    node_destroy(aux, free_func);
    return val;
}

ForwardList *forward_list_reverse(ForwardList *l) {
    ForwardList *FL = forward_list_construct ();
    Node *aux = l->head;

    while (aux != NULL) {
        forward_list_push_front(FL, aux->value);
        aux = aux->next;
    }
    
    return FL;
}

void forward_list_clear(ForwardList *l, void (*free_func)(data_type)) {
    Node *aux;
    for (int i=0; i<l->size; i++) {
        aux = l->head->next;
        free_func(l->head->value);
        node_destroy(l->head, free_func);
        l->head = aux;
    }
    l->size = 0;
}

void forward_list_remove(ForwardList *l, data_type val, int (*cmp_func)(void *, data_type), void (*free_func)(data_type)) {
    Node *current = l->head;
    Node *previous = NULL;

    while (current != NULL) {

        if (cmp_func(current->value, val) == 0) {
            if (previous == NULL) {
                l->head = current->next;
                if (free_func != NULL) {
                    node_destroy(current, free_func);
                }
                else {
                    only_node_destroy(current);
                }
                current = l->head;
            } 

            else {
                previous->next = current->next;
                if (free_func != NULL) {
                    node_destroy(current, free_func);
                }
                else {
                    only_node_destroy(current);
                }
                current = previous->next;
            }
            l->size--; 

        } 

        else {
            previous = current;
            current = current->next;
        }

    }

}

// Not working yet
void forward_list_unique(ForwardList *l, int (*cmp_func)(void *, data_type), void (*free_func)(data_type)) {
    Node *current = l->head;
    Node *previous = NULL;

    while (current != NULL) {

        if (previous != NULL && cmp_func(previous->value, current->value) == 0) {
            forward_list_remove(l, current->value, cmp_func, free_func);
        } 
        else {
            // Avançar para o próximo nó
            previous = current;
            current = current->next;
        }

    }

}

void forward_list_cat(ForwardList *l, ForwardList *m) {
    if (m == NULL || l == NULL) {
        return;
    }
    
    if (l->head == NULL) {
        l->head = m->head;
        l->size = m->size;
    }

    Node *aux = m->head;
    for (int i=0; i<m->size; i++) {
        forward_list_push_front(l, aux->value);
        aux = aux->next;
    }
    
}

void forward_list_sort(ForwardList *l, int (*cmp_func)(void *, data_type)) {
    // verificar se NULO:  lista, cabeça, funcao de cmp, proximo da cabeça (se for nulo, nao precisa ordenar)
    if (l == NULL || l->head == NULL || cmp_func == NULL || l->head->next == NULL) {
        return;
    }

    int flag;
    Node *aux;
    Node *aux_2 = NULL;

    do {
        flag = 0;
        aux = l->head;

        while (aux->next != aux_2) {
            if (cmp_func(aux->value, aux->next->value) > 0) {
                void *temp = aux->value;
                aux->value = aux->next->value;
                aux->next->value = temp;
                flag = 1;
            }
            aux = aux->next;
        }
        aux_2 = aux;
    } while (flag);
}

void forward_list_destroy(ForwardList *l, void (*free_func)(data_type)) {
    Node *aux;

    
    for (int i=0; i<l->size; i++) {
        aux = l->head->next;
        if (l->head != NULL) {
            node_destroy(l->head, free_func);
        }
        l->head = aux;
    }

    if (l != NULL) {
        free(l);
        l = NULL;
    }

}

data_type forward_list_find(ForwardList *l, data_type val, int (*cmp_func)(void *, data_type)) {
    Node *aux = l->head;
    
    while (aux != NULL) {
        if (cmp_func(aux->value, val) == 0) {
            return aux->value;
        }
        aux = aux->next;
    }

    return NULL;
}

ForwardList *forward_list_copy(ForwardList *l) {
    ForwardList *FL = forward_list_construct();
    FL->size = l->size;
    FL->head = NULL;

    Node *aux = l->head;
    for (int i=0; i<l->size; i++) {
        forward_list_push_front(FL, aux->value);
        aux = aux->next;
    }

    return FL;
}

void forward_list_only_node_and_list_destroy (ForwardList *l) {
    Node *aux;

    while (l->head != NULL) {
        aux = l->head->next;
        if (l->head != NULL) {
            only_node_destroy(l->head);
        }
        l->head = aux;
    }

    if (l != NULL) {
        free(l);
        l = NULL;
    }
}

void forward_list_only_nodes_destroy (ForwardList *l) {
    Node *aux;

    for (int i=0; i<l->size; i++) {
        aux = l->head->next;
        if (l->head != NULL) {
            only_node_destroy(l->head);
        }
        l->head = aux;
    }
}
