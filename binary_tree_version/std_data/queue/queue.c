#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

Queue *queue_construct() {
    Queue *Q = (Queue*)malloc(sizeof(Queue));
    Q->FL = forward_list_construct();

    return Q;
}

void queue_enqueue(Queue *Q, data_type value) {
    forward_list_push_back(Q->FL, value);
}

data_type queue_dequeue(Queue *Q) {
    return forward_list_pop_front(Q->FL);
}
void queue_print(Queue *Q, void (*print_fn)(data_type)) {
    forward_list_print(Q->FL, print_fn);
}

int queue_isEmpty(Queue *Q) {
    if (forward_list_size(Q->FL) == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

void queue_destroy(Queue *Q, void (*free_func)(data_type)) {
    forward_list_destroy(Q->FL, free_func);
    free(Q);
}
