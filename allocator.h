#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stddef.h>

// Объявления функций
void* my_malloc(size_t size);
void* my_realloc(void* ptr, size_t size);
void* my_calloc(size_t num, size_t size);
void my_free(void* pointer);
char* my_strdup(char* input);

// Вспомогательные функции для отладки
void print_heap();
int check_heap();

// 3. Прототипы тестов (чтобы не было warning: implicit declaration)
void test_basic();
void test_reuse();
void test_split();
void test_coalesce();
void test_realloc_grow();
void test_realloc_shrink();
void test_calloc();
void test_strdup();
void test_stress();
void test_double_free();
void test_invalid_free();

#endif