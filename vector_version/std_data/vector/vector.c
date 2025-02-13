#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

static const int VECTOR_INIT_SIZE = 10;
static const int VECTOR_GROWTH_RATE = 2;

typedef struct Vector
{
    data_type *data;
    int size;
    int allocated;
} Vector;

Vector *vector_construct()
{
    Vector *v = (Vector *)calloc(1, sizeof(Vector));

    v->allocated = VECTOR_INIT_SIZE;
    v->size = 0;
    v->data = (data_type *)calloc(VECTOR_INIT_SIZE, sizeof(data_type));

    return v;
}

int vector_size(Vector *v)
{
    return v->size;
}

data_type vector_get(Vector *v, int i)
{
    if (i >= vector_size(v))
    {
        printf("Error: vector_get: invalid index %d for vector with size %d.\n", i, vector_size(v));
        exit(0);
    }

    return v->data[i];
}

data_type vector_set(Vector *v, int i, data_type val)
{
    if (i >= vector_size(v))
    {
        printf("Error: vector_set: invalid index %d for vector with size %d.\n", i, vector_size(v));
        exit(0);
    }

    data_type prev_val = v->data[i];
    v->data[i] = val;

    return prev_val;
}

void vector_push_back(Vector *v, data_type val)
{
    if (v->size >= v->allocated)
    {
        v->allocated *= VECTOR_GROWTH_RATE;
        v->data = (data_type *)realloc(v->data, v->allocated * sizeof(data_type));
    }

    v->data[v->size] = val;
    v->size++;
}

int vector_find(Vector *v, data_type val, int (*cmp)(data_type, data_type))
{
    int i = 0;
    while (i < vector_size(v))
    {
        if (!cmp(vector_get(v, i), val))
            return i;
        i++;
    }

    return -1;
}

data_type vector_remove(Vector *v, int i)
{
    if (i >= v->size || i < 0)
    {
        printf("Error: vector_remove: invalid index %d for vector with size %d.\n", i, v->size);
        exit(0);
    }

    data_type val = v->data[i];

    for (int j = i; j < v->size - 1; j++)
        v->data[j] = v->data[j + 1];

    v->size--;

    return val;
}

data_type vector_pop_front(Vector *v)
{
    return vector_remove(v, 0);
}

data_type vector_pop_back(Vector *v)
{
    return vector_remove(v, v->size - 1);
}

data_type vector_insert(Vector *v, int i, data_type val)
{
    if (i < 0 || i > v->size)
    {
        printf("Error: vector_insert: invalid index %d for vector with size %d.\n", i, v->size);
        exit(0);
    }

    if (v->size == v->allocated)
    {
        v->allocated *= 2;
        v->data = (data_type *)realloc(v->data, v->allocated * sizeof(data_type));
    }

    for (int j = v->size; j > i; j--)
        v->data[j] = v->data[j - 1];

    data_type prev_val = v->data[i];

    v->data[i] = val;
    v->size++;

    return prev_val;
}

void vector_swap(Vector *v, int i, int j)
{
    if (i < 0 || i >= v->size || j < 0 || j >= v->size)
    {
        printf("Error: vector_swap: invalid indices %d and %d for vector with size %d.\n", i, j, v->size);
        exit(0);
    }

    data_type temp = v->data[i];
    v->data[i] = v->data[j];
    v->data[j] = temp;
}

void vector_sort(Vector *v, int (*cmp)(data_type, data_type))
{
    for (int i = 0; i < v->size - 1; i++)
    {
        int n_trocas = 0;

        for (int j = 0; j < v->size - i - 1; j++)
        {
            if (cmp(v->data[j], v->data[j + 1]) > 0)
            {
                vector_swap(v, j, j + 1);
                n_trocas++;
            }
        }

        if (n_trocas == 0)
            break;
    }
}

void vector_quick_sort_recursive(Vector *v, int st, int end, int (*cmp)(data_type, data_type))
{
    if (st >= end)
        return;

    int pivot = rand() % (end - st + 1) + st;
    int insert_point = st;

    vector_swap(v, pivot, end);

    for (int i = st; i <= end - 1; i++)
    {
        if (cmp(v->data[i], v->data[pivot]) < 0)
        {
            vector_swap(v, i, insert_point);
            insert_point++;
        }
    }

    vector_swap(v, pivot, insert_point);

    vector_quick_sort_recursive(v, st, insert_point - 1, cmp);
    vector_quick_sort_recursive(v, insert_point + 1, end, cmp);
}

void vector_quick_sort(Vector *v, int (*cmp)(data_type, data_type))
{
    vector_quick_sort_recursive(v, 0, v->size - 1, cmp);
}

int vector_binary_search(Vector *v, data_type val, int (*cmp)(data_type, data_type))
{
    int left = 0;
    int right = v->size - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (!cmp(v->data[mid], val))
            return mid;
        else if (cmp(v->data[mid], val) < 0)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}

void vector_reverse(Vector *v)
{
    for (int i = 0; i < v->size / 2; i++)
        vector_swap(v, i, v->size - i - 1);
}

Vector *vector_copy(Vector *v)
{
    Vector *copy = (Vector *)malloc(sizeof(Vector));

    copy->data = (data_type *)malloc(v->allocated * sizeof(data_type));
    copy->size = v->size;
    copy->allocated = v->allocated;

    memcpy(copy->data, v->data, v->size * sizeof(data_type));

    return copy;
}

void vector_destroy(Vector *v)
{   
    if (v == NULL) {
        return;
    }

    if (v->data != NULL) {
        free(v->data);
        v->data = NULL;
    }
    
    free(v);
    v = NULL;
}

void vector_clear(Vector *v) {
    v->size = 0;
}

Vector *vector_unique(Vector *v, int (*cmp)(data_type, data_type))
{
    Vector *output = vector_construct();

    for (int i = 0; i < vector_size(v); i++)
        if (vector_find(output, vector_get(v, i), cmp) == -1)
            vector_push_back(output, v->data[i]);
        
        else {
            free(v->data[i]);
            v->data[i] = NULL;
        }
    return output;
}