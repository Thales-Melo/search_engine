#ifndef _NODE_H_
#define _NODE_H_

#include "../../../utils/utils.h"

typedef struct Node
{
    void *value;
    struct Node *next;
} Node;

/**
 * Constructs a new node with the given value and next node pointer.
 *
 * @param value The value to be stored in the new node.
 * @param next A pointer to the next node in the list.
 * @return A pointer to the newly constructed node.
 */
Node *node_construct(data_type value, Node *next);

/**
 * @brief Destroys a node and its data.
 * 
 * This function frees the memory allocated for a node and its data using the provided
 * free function.
 * 
 * @param n The node to be destroyed.
 * @param free_func The function to be used to free the memory allocated for the node's data.
 */
void node_destroy(Node *n, void (*free_func)(data_type));

/**
 * @brief Destroys a node without freeing its data.
 * 
 * This function frees the memory allocated for a node without freeing its data.
 * 
 * @param n The node to be destroyed.
 */
void only_node_destroy(Node *n);

#endif