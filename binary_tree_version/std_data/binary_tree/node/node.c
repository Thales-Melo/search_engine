#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../queue/queue.h"

typedef struct Node {
    KeyValPair *key_val;
    Node *left;
    Node *right;
} Node;


Node *node_construct (KeyValPair *key_val, Node *left, Node *right) {
    Node *N = (Node*)malloc(sizeof(Node));

    N->key_val = key_val;
    N->left = left;
    N->right = right;

    return N;
}


void node_destroy_recursive(Node *N, void (*val_destroy_fn)(data_type), void (*key_destroy_fn)(key_type)) {
    if (N == NULL) {
        return;
    }

    // destruir os filhos (recursivamente)
    node_destroy_recursive(N->left, val_destroy_fn, key_destroy_fn);
    node_destroy_recursive(N->right, val_destroy_fn, key_destroy_fn);

    // agora sim libera a memória do nó
    if (N->key_val != NULL) {
        key_val_pair_destroy(N->key_val, val_destroy_fn, key_destroy_fn);
        N->key_val = NULL;
    }
    if (N != NULL) {
        free(N);
        N = NULL;
    }
}

void node_destroy (Node *N, void (*val_destroy_fn)(data_type), void (*key_destroy_fn)(key_type)) {
    if (N == NULL) {
        return;
    }

    key_val_pair_destroy(N->key_val, val_destroy_fn, key_destroy_fn);
    
    if (N != NULL) {
        free(N);
        N = NULL;
    }
}

key_type node_key (Node *N) {
    return key_val_pair_key(N->key_val);
}


data_type node_value (Node *N) {
    return key_val_pair_value(N->key_val);
}

KeyValPair *node_key_val_pair (Node *N) {
    return N->key_val;
}

Node *node_right (Node *N) {
    return N->right;
}


Node *node_left (Node *N) {
    return N->left;
}


Node *node_add_recursive(Node *node, KeyValPair *key_val, int (*cmp_fn)(data_type, data_type)) {
    if (node == NULL) {
        return node_construct(key_val, NULL, NULL);
    }

    if (cmp_fn(key_val_pair_key(key_val), key_val_pair_key(node->key_val)) < 0) {
        node->left = node_add_recursive(node->left, key_val, cmp_fn);
    } else {
        node->right = node_add_recursive(node->right, key_val, cmp_fn);
    }

    return node;  // Adicionado o retorno aqui para conectar o nó pai ao novo nó.
}


void node_print (Node *N, void (*key_print_fn)(key_type), void (*val_print_fn)(data_type)) {
    if (N == NULL) {
        return;
    }
    
    key_val_pair_print(N->key_val, key_print_fn, val_print_fn);
    node_print(N->left, key_print_fn, val_print_fn);
    node_print(N->right, key_print_fn, val_print_fn);
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

Node *node_search (Node *node, key_type *key, int (*cmp_fn)(data_type, data_type)) {
    if (node == NULL) {
        return NULL;
    }

    if (key_val_pair_cmp(key, key_val_pair_key(node->key_val), cmp_fn) == 0) {
        return node;
    }

    if (key_val_pair_cmp(key, key_val_pair_key(node->key_val), cmp_fn) < 0) {
        return node_search(node->left, key, cmp_fn);
    }

    else {
        return node_search(node->right, key, cmp_fn);
    }
}


Node *node_remove_recursive(Node *node, key_type *key, int (*cmp_fn)(data_type, data_type), void (*val_destroy_fn)(data_type), void (*key_destroy_fn)(key_type)) {
    if (node == NULL) {
        return NULL;
    }

    if (key_val_pair_cmp(key, key_val_pair_key(node->key_val), cmp_fn) < 0) {
        node->left = node_remove_recursive(node->left, key, cmp_fn, val_destroy_fn, key_destroy_fn);
    } else if (key_val_pair_cmp(key, key_val_pair_key(node->key_val), cmp_fn) > 0) {
        node->right = node_remove_recursive(node->right, key, cmp_fn, val_destroy_fn, key_destroy_fn);
    } else {
        if (node->left == NULL && node->right == NULL) {
            key_val_pair_destroy(node->key_val, val_destroy_fn, key_destroy_fn);
            free(node);
            node = NULL;
            return NULL;
        } else if (node->left == NULL || node->right == NULL) {
            Node *temp = (node->left == NULL) ? node->right : node->left;
            key_val_pair_destroy(node->key_val, val_destroy_fn, key_destroy_fn);
            free(node);
            node = NULL;
            return temp;
        } else {
            Node *temp = node->right;
            while (temp->left != NULL) {
                temp = temp->left;
            }
            key_val_pair_set_key(node->key_val, key_val_pair_key(temp->key_val));
            key_val_pair_set_value(node->key_val, key_val_pair_value(temp->key_val));
            node->right = node_remove_recursive(node->right, key_val_pair_key(temp->key_val), cmp_fn, val_destroy_fn, key_destroy_fn);
        }
    }
    return node;
}


Node *node_remove(Node *root, key_type *key, int (*cmp_fn)(data_type, data_type), void (*val_destroy_fn)(data_type), void (*key_destroy_fn)(key_type)) {
    Node *node = node_search(root, key, cmp_fn);
    if (node == NULL) {
        return NULL;
    }
    return node_remove_recursive(root, key, cmp_fn, val_destroy_fn, key_destroy_fn);
}


void node_print_level_order(Node *root, void (*key_print_fn)(key_type), void (*val_print_fn)(data_type)) {
    if (root == NULL)
        return;

    Queue *queue = queue_construct();
    queue_enqueue(queue, root);

    while (queue->FL->head != NULL) {
        Node *currentNode = queue_dequeue(queue);
        // printf("%d ", currentNode->data);
        key_val_pair_print(currentNode->key_val, key_print_fn, val_print_fn);

        if (currentNode->left != NULL)
            queue_enqueue(queue, currentNode->left);

        if (currentNode->right != NULL)
            queue_enqueue(queue, currentNode->right);
    }

    free(queue);
    queue = NULL;
}


void node_print_in_order (Node *root, void (*key_print_fn)(key_type), void (*val_print_fn)(data_type)) {
    if (root == NULL) {
        return;
    }

    node_print_in_order(root->left, key_print_fn, val_print_fn);
    key_val_pair_print(root->key_val, key_print_fn, val_print_fn);
    node_print_in_order(root->right, key_print_fn, val_print_fn);
}
    
void node_print_pre_order (Node *root, void (*key_print_fn)(key_type), void (*val_print_fn)(data_type)) {
    if (root == NULL) {
        return;
    }

    key_val_pair_print(root->key_val, key_print_fn, val_print_fn);
    node_print_pre_order(root->left, key_print_fn, val_print_fn);
    node_print_pre_order(root->right, key_print_fn, val_print_fn);
}

void node_print_post_order (Node *root, void (*key_print_fn)(key_type), void (*val_print_fn)(data_type)) {
    if (root == NULL) {
        return;
    }

    node_print_post_order(root->left, key_print_fn, val_print_fn);
    node_print_post_order(root->right, key_print_fn, val_print_fn);
    key_val_pair_print(root->key_val, key_print_fn, val_print_fn);
}

void node_set_value(Node *N, data_type value) {
    key_val_pair_set_value(N->key_val, value);
}



// FPRINTS (VERSOES PARA ESCRITA EM ARQUIVO)

void node_file_print_level_order(Node *root, void (*key_fprint_fn)(key_type, FILE*), void (*val_fprint_fn)(data_type, FILE*), FILE *fp) {
    if (root == NULL)
        return;

    Queue *queue = queue_construct();
    queue_enqueue(queue, root);

    while (queue->FL->head != NULL) {
        Node *currentNode = queue_dequeue(queue);
        // printf("%d ", currentNode->data);
        key_val_pair_file_print(currentNode->key_val, key_fprint_fn, val_fprint_fn, fp);
        // fl_node_destroy(currentNode);

        if (currentNode->left != NULL) {
            queue_enqueue(queue, currentNode->left);
        }

        if (currentNode->right != NULL) {
            queue_enqueue(queue, currentNode->right);
        }

    }

    queue_destroy(queue, free);
}


void node_file_print_in_order (Node *root, void (*key_fprint_fn)(key_type, FILE*), void (*val_fprint_fn)(data_type, FILE*), FILE *fp) {
    if (root == NULL) {
        return;
    }

    node_file_print_in_order(root->left, key_fprint_fn, val_fprint_fn, fp);
    key_val_pair_file_print(root->key_val, key_fprint_fn, val_fprint_fn, fp);
    node_file_print_in_order(root->right, key_fprint_fn, val_fprint_fn, fp);
}


void node_file_print_pre_order(Node *root, void (*key_fprint_fn)(key_type, FILE*), void (*val_fprint_fn)(data_type, FILE*), FILE *fp) {
    if (root == NULL) {
        return;
    }

    key_val_pair_file_print(root->key_val, key_fprint_fn, val_fprint_fn, fp);
    node_file_print_pre_order(root->left, key_fprint_fn, val_fprint_fn, fp);
    node_file_print_pre_order(root->right, key_fprint_fn, val_fprint_fn, fp);
}


void node_file_print_post_order(Node *root, void (*key_fprint_fn)(key_type, FILE*), void (*val_fprint_fn)(data_type, FILE*), FILE *fp) {
    if (root == NULL) {
        return;
    }

    node_file_print_post_order(root->left, key_fprint_fn, val_fprint_fn, fp);
    node_file_print_post_order(root->right, key_fprint_fn, val_fprint_fn, fp);
    key_val_pair_file_print(root->key_val, key_fprint_fn, val_fprint_fn, fp);
}


int node_count(Node *root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + node_count(root->left) + node_count(root->right);
}


key_type node_index_key_in_order(Node *root, int index) {
    if (root == NULL || index < 0) {
        return NULL;
    }

    // Número de nós na subárvore à esquerda
    int leftSubtreeSize = node_count(root->left);

    // Se o índice estiver na subárvore à esquerda, busca nessa subárvore
    if (index < leftSubtreeSize) {
        return node_index_key_in_order(root->left, index);
    }
    // Se o índice for igual ao tamanho da subárvore à esquerda, encontramos o nó
    else if (index == leftSubtreeSize) {
        return node_key(root);
    }
    // Se o índice estiver na subárvore à direita, busca nessa subárvore
    else {
        return node_index_key_in_order(root->right, index - leftSubtreeSize - 1);
    }
}


data_type node_index_value_in_order(Node *root, int index) {
    if (root == NULL || index < 0) {
        return NULL;  // Assumindo que o tipo de dado value_type é um ponteiro
    }

    // Número de nós na subárvore à esquerda
    int leftSubtreeSize = node_count(root->left);

    // Se o índice estiver na subárvore à esquerda, busca nessa subárvore
    if (index < leftSubtreeSize) {
        return node_index_value_in_order(root->left, index);
    }
    // Se o índice for igual ao tamanho da subárvore à esquerda, encontramos o nó
    else if (index == leftSubtreeSize) {
        return node_value(root);
    }
    // Se o índice estiver na subárvore à direita, busca nessa subárvore
    else {
        return node_index_value_in_order(root->right, index - leftSubtreeSize - 1);
    }
}
