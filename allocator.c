#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

#include "allocator.h"

struct block{
    size_t size;
    int free;
};

struct footer{
    size_t size;
};

void my_free(void* pointer);
void print_heap();

void* head = NULL;
void* heap_end;


void* my_malloc(size_t size){
    size = (size + 7) & ~7; //округлить до ближайшего верхнего числа кратного 8

    if(size == 0) return NULL;

    if(!head){
        head = sbrk(0);
        heap_end = head;
    }

    struct block* current = (struct block*)head;

    while((char*)current < (char*)heap_end){
        if(current->size >= size && current->free){
            if(current->size >= size + sizeof(struct block) + sizeof(struct footer) + 8){
                size_t old_size = current->size;
                struct block* separated = (struct block*)((char*)current + sizeof(struct block) 
                    + size + sizeof(struct footer));
                separated->size = old_size - size - sizeof(struct block) - sizeof(struct footer);
                separated->free = 1;
                current->size = size;

                ((struct footer*)((char*)(current) + sizeof(struct block) + current->size))->size = current->size;
                ((struct footer*)((char*)(separated) + sizeof(struct block) + separated->size))->size = separated->size;
            }
            current->free = 0;
            return current + 1;
        }
        current = (struct block*)((char*)current + sizeof(struct block) + current->size + sizeof(struct footer));
    }

    struct block* new_block = sbrk(sizeof(struct block) + size + sizeof(struct footer));

    if (new_block == (void*)-1) return NULL;

    new_block = (struct block*)heap_end;
    new_block->size = size;
    new_block->free = 0;
    ((struct footer*)((char*)(new_block) + sizeof(struct block) + size))->size = size;
    heap_end = ((char*)(new_block) + sizeof(struct block) + size + sizeof(struct footer));

    return new_block + 1;
}


void* my_realloc(void* ptr, size_t size){
    size = (size + 7) & ~7;

    if(ptr >= heap_end || ((struct block*)ptr - 1)->size == size || !size) {
        return ptr;
    }

    struct block* current = (struct block*)ptr - 1;
    
    if(current->size < size){
        struct block* new = my_malloc(size);
        if(!new) return ptr;
        new -= 1;
        memcpy((char*)(new + 1), (char*)(current + 1), current->size);
        my_free((char*)(current + 1));
        return (char*)(new + 1);
    }

    if(current->size > size){

        if(current->size - size > sizeof(struct block) + 8 + sizeof(struct footer)){
            struct block* separated = (struct block*)((char*)current 
            + sizeof(struct block) 
            + size 
            + sizeof(struct footer));
            separated->size = current->size - size - sizeof(struct block) - sizeof(struct footer);
            current->size = size;
            separated->free = 1;
            current->free = 0;

            ((struct footer*)((char*)(current + 1) + current->size))->size = current->size;
            ((struct footer*)((char*)(separated + 1) + separated->size))->size = separated->size;
        }

    return (char*)(current + 1);
    }
}


void print_heap(){
    struct block* current = head;

    while((char*)current < (char*)heap_end){
        printf("Block size: %zu, free: %d, address: %p, next address: %p\n", 
            current->size + sizeof(struct block) + sizeof(struct footer), 
            current->free, current, (char*)(current + 1) + current->size + sizeof(struct footer));

        current = (struct block*)((char*)(current + 1) + current->size + sizeof(struct footer));
    }
}


void my_free(void* pointer){
    if(!pointer) return;

    if((char*)pointer < (char*)head || (char*)pointer >= (char*)heap_end) return;

    struct block* block = (struct block*)pointer - 1;
    if(block->free) return;
    struct block* prev = NULL;
    struct block* next_b = NULL;

    if(block != head){
        prev = (struct block*)((char*)block - sizeof(struct footer) - 
        ((struct footer*)block - 1)->size - sizeof(struct block));
    }
    if(block < (struct block*)heap_end){
        next_b = (struct block*)((char*)(block + 1) + block->size + sizeof(struct footer));
    }
    if(next_b != NULL && next_b < (struct block*)heap_end && (next_b->free)){
        block->size += sizeof(struct block) + next_b->size + sizeof(struct footer);
        ((struct footer*)((char*)(block + 1) + block->size))->size = block->size;
    }
    if(prev != NULL && prev->free){
        prev->size += (block->size + sizeof(struct block) + sizeof(struct footer));
        ((struct footer*)((char*)(prev + 1) + prev->size))->size = prev->size;
    }

    block->free = 1;
}


void* my_calloc(size_t num, size_t size){
    if(num * size == 0 || SIZE_MAX / size < num) return NULL;

    void* curr = my_malloc(num * size);
    if(!curr) return NULL;

    memset(curr, 0, num * size);

    return curr;
}


int check_heap(){
    struct block* curr = (struct block*)head;

    while((char*)curr < (char*)heap_end){
        struct footer* f = (struct footer*)((char*)curr + sizeof(struct block) + curr->size);

        if((char*)f >= (char*)heap_end || curr->size != f->size || curr->size == 0 || 
        (curr->size >= (char*)heap_end - (char*)curr)) return 0;

        curr = (struct block*)((char*)(curr + 1) + curr->size + sizeof(struct footer));
        
    }

    return 1;
}


char* my_strdup(char* input){
    char* new = my_malloc(strlen(input) + 1);

    if(!new) return NULL;

    char* iterator = new;
    for(char* el = input; *el != '\0'; el++){
        *iterator++ = *el;
    }
    *iterator = '\0';

    return new;
}


void test_basic() {
    int* a = my_malloc(10 * sizeof(int));
    a[0] = 42;

    if (a[0] != 42) printf("FAIL basic\n");

    my_free(a);
    printf("PASS basic\n");
    print_heap();
}

void test_reuse() {
    void* a = my_malloc(100);
    printf("__________________________________\n");
    print_heap();
    my_free(a);

    printf("__________________________________\n");
    print_heap();
    
    void* b = my_malloc(100);
    printf("__________________________________\n");
    print_heap();

    if (a != b) printf("FAIL reuse\n");
    else printf("PASS reuse\n");

    printf("__________________________________\n");
    print_heap();
    printf("a: %p, b: %p\n", a,b);
}

void test_split() {
    void* a = my_malloc(200);
    my_free(a);

    void* b = my_malloc(50);

    if (!check_heap()) printf("FAIL split\n");
    else printf("PASS split\n");
}

void test_coalesce() {
    void* a = my_malloc(100);
    void* b = my_malloc(100);

    my_free(a);
    my_free(b);

    if (!check_heap()) printf("FAIL coalesce\n");
    else printf("PASS coalesce\n");
}

void test_realloc_grow() {
    int* a = my_malloc(5 * sizeof(int));

    for (int i = 0; i < 5; i++) a[i] = i;

    a = my_realloc(a, 10 * sizeof(int));

    for (int i = 0; i < 5; i++) {
        if (a[i] != i) {
            printf("FAIL realloc grow\n");
            return;
        }
    }

    printf("PASS realloc grow\n");
}

void test_realloc_shrink() {
    int* a = my_malloc(10 * sizeof(int));
    a[0] = 123;

    a = my_realloc(a, 2 * sizeof(int));

    if (a[0] != 123) printf("FAIL realloc shrink\n");
    else printf("PASS realloc shrink\n");
}

void test_calloc() {
    int* a = my_calloc(5, sizeof(int));

    for (int i = 0; i < 5; i++) {
        if (a[i] != 0) {
            printf("FAIL calloc\n");
            return;
        }
    }

    printf("PASS calloc\n");
}

void test_strdup() {
    char* s = my_strdup("hello");

    if (strcmp(s, "hello") != 0) printf("FAIL strdup\n");
    else printf("PASS strdup\n");
}

void test_stress() {
    void* arr[1000];

    for (int i = 0; i < 1000; i++) {
        arr[i] = my_malloc(rand() % 200);
    }

    for (int i = 0; i < 1000; i++) {
        if (rand() % 2) my_free(arr[i]);
    }

    if (!check_heap()) printf("FAIL stress\n");
    else printf("PASS stress\n");
}

void test_double_free() {
    void* a = my_malloc(100);
    my_free(a);
    my_free(a); 

    printf("PASS double free\n");
}

void test_invalid_free() {
    int x;
    my_free(&x); 

    printf("PASS invalid free\n");
}