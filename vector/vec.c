#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "vec.h"

//static - ф-ия видна только внутри vec.c

static bool is_out_of_bounds(const vector* vec, size_t index){
    if(index >= vec->size){
        printf("Error, requested index is %zu, while the size of the vector is %zu\n", index, vec->size);
        return true;
    }
    return false;
}


static void capacity_increase(vector* vec){
if(vec->size == vec->capacity){
        vec->capacity *= 2;
        int* temp = realloc(vec->data, vec->capacity * sizeof(int));
        if(temp != NULL) {
            vec->data = temp;
        }
        else exit(1);
    }
}


vector* vec_create(){
    return vec_create_with_capacity(4);
}


vector* vec_create_with_capacity(size_t capacity_n){
    vector* vec = malloc(sizeof(vector));
    if(!vec) {
        printf("There is no memory to create a vector\n");
        exit(1);
    }
    vec->capacity = capacity_n;
    vec->size = 0;
    vec->data = malloc(sizeof(int) * vec->capacity);

    return vec;
}


void vec_free(vector* vec){
    free(vec->data);
    free(vec);
}


void push_back(vector* vec, int value){
    vec_insert(vec,vec->size,value);
    return;
}

//const - нельзя менять значения
const int* get(const vector* vec, size_t index){
    if(!is_out_of_bounds(vec, index)){
        return &(vec->data[index]);
    }
    return NULL;
}


void set(vector* vec, size_t index, int value){
    if(!is_out_of_bounds(vec, index)){
        vec->data[index] = value;
    }
    return;
}


void pop(vector* vec){
    if(vec->size == 0){
        printf("vector size is 0, what are you trying to pop?\n");
        return;
    }
    vec->size--;
}


size_t size(vector* vec){
    return vec->size;
}


size_t vec_capacity(vector* vec){
    return vec->capacity;
}


void vec_insert(vector* vec, size_t index, int value){
if(index < vec->size + 1){
    capacity_increase(vec);
    int tmp;
    for(size_t i = index; i < vec->size + 1;i++){
        tmp = vec->data[i];
        vec->data[i] = value;
        value = tmp;
    }
    vec->size++;
}
return;
}


void vec_remove(vector* vec, size_t index){

    if(!is_out_of_bounds(vec, index)){
    for(size_t i = index; i < vec->size - 1;i++){
        vec->data[i] = vec->data[i + 1];
    }
    vec->size--;
    }

    return;
}


void vec_reserve(vector* vec, size_t new_capacity){
    if(new_capacity > vec->capacity){
        int* temp = realloc(vec->data, new_capacity * sizeof(int));
        if(temp != NULL) {
            vec->data = temp;
        }
        else exit(1);
        vec->capacity = new_capacity;
    }
    return;
}


void vec_shrink_to_fit(vector* vec){
    vec->data = realloc(vec->data, vec->size * sizeof(int));
    vec->capacity = vec->size;
    return;
}


void vec_clear(vector *vec){
    vec->size = 0;
}