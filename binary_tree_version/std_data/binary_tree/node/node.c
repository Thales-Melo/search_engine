#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    key_type key;
    data_type value;
    Node *left;
    Node *right;
    Node *parent;
} Node;

Node *node_construct (key_type key, data_type value, Node *left, Node *right) {
    Node *N = (Node*)malloc(sizeof(Node));

    N->key = key;
    N->value = value;
    N->left = left;
    N->right = right;

    return N;
}

void node_destroy(Node *N, void (*free_func)(data_type)) {
    if (N == NULL) {
        return;
    }

    // destruir os filhos (recursivamente)
    node_destroy(N->left, free_func);
    node_destroy(N->right, free_func);

    // agora sim libera a memória do nó
    if (free_func != NULL) {
        if (N->value != NULL) {
            free_func(N->value);
            N->value = NULL;
        }
    }
    if (N != NULL) {
        free(N);
        N = NULL;
    }
}

key_type node_key (Node *N) {
    return N->key;
}

data_type node_value (Node *N) {
    return N->value;
}

Node *node_right (Node *N) {
    return N->right;
}

Node *node_left (Node *N) {
    return N->left;
}

Node *node_add_recursive(Node *node, key_type key, data_type value) {
    if (node == NULL) {
        return node_construct(key, value, NULL, NULL);
    }
    if (strcmp(key, node->key) < 0) {
        node->left = node_add_recursive(node->left, key, value);
    }
    else {
        node->right = node_add_recursive(node->right, key, value);
    }

    return node;
}

void node_print (Node *N) {
    if (N == NULL) {
        return;
    }
    
    node_print(N->left);
    printf("%s ", (char*)N->value);
    node_print(N->right);
}

Node *node_parent(Node *N) {
    return N->parent;
}

void node_set_left(Node *N, Node *left) {
    N->left = left;
}

void node_set_right(Node *N, Node *right) {
    N->right = right;
}

/////////////////////////////////////////////////////////////

int compare_keys (key_type key1, key_type key2) {
    return strcmp(key1, key2);
}



/////////////////////////////////////////////////////////////
// FUNÇÕES DE BUSCA
/////////////////////////////////////////////////////////////

Node *node_search (Node *node, key_type key) {
    if (node == NULL) {
        return NULL;
    }

    if (strcmp(key, node->key) == 0) {
        return node;
    }

    if (strcmp(key, node->key) < 0) {
        return node_search(node->left, key);
    }

    else {
        return node_search(node->right, key);
    }
}


Node* node_remove_recursive(Node *node, key_type key) {
    if (node == NULL) {
        return NULL;
    }

    if (strcmp(key, node->key) < 0) {
        node->left = node_remove_recursive(node->left, key);
    }

    else if (strcmp(key, node->key) > 0) {
        node->right = node_remove_recursive(node->right, key);
    }

    else {
        if (node->left == NULL && node->right == NULL) {
            if (node != NULL) {
                free(node->value);
                free(node);
                node = NULL;
            }
            return NULL;
        } 
        else if (node->left == NULL || node->right == NULL) {
            Node *temp;
            if (node->left == NULL) {
                temp = node->right;
            }
            else {
                temp = node->left;
            }
            if (node != NULL) {
                free(node->value);
                free(node);
                node = NULL;
            }
            return temp;
        } 
        else {
            Node * temp = node->right;
            while (temp != NULL) {
                temp = temp->left;
            }
            node->key = temp->key;
            node->value = temp->value;
            node->right = node_remove_recursive(node->right, temp->key);
        }
    }
    return node;
}

Node *node_remove(Node *root, key_type key) {
    Node *node = node_search(root, key);
    if (node == NULL) {
        return NULL;
    }
    return node_remove_recursive(root, key);
}