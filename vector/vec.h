#ifndef VEC_H
#define VEC_H

#include <stddef.h>

typedef struct{
    int* data;
    size_t size;
    size_t capacity;
} vector;

vector* vec_create();
vector* vec_create_with_capacity(size_t capacity);
void vec_free(vector* vec);

void push_back(vector* vec, int value);
void pop(vector* vec);

const int* get(const vector* vec, size_t index);
void set(vector* vec, size_t index, int value);

size_t size(vector* vec);
size_t vec_capacity(vector* vec);

void vec_insert(vector* vec, size_t index, int value);
void vec_remove(vector* vec, size_t index);

void vec_reserve(vector* vec, size_t new_capacity);
void vec_shrink_to_fit(vector* vec);
void vec_clear(vector* vec);

#endif