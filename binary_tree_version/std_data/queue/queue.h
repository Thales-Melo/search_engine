#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "../forward_list/forward_list.h"

typedef struct queue {
    ForwardList *FL;
} Queue;

Queue *queue_construct();
void queue_enqueue(Queue *Q, data_type value);
data_type queue_dequeue(Queue *Q);
void queue_print(Queue *Q, void (*print_fn)(data_type));
int queue_isEmpty(Queue *Q);
void queue_destroy(Queue *Q, void (*free_func)(data_type));

#endif