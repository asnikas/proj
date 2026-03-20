#ifndef HASH_TABLE_H //если HASH_TABLE_H еще не существует 
//(работает до компиляции при помощий препроцесоора)

#define HASH_TABLE_H //создать макрос с именем HASH_TABLE_H

//ifndef + define = include guard

#include <stddef.h>
#include <stdbool.h>

typedef struct entry{
char* key;
int value;
struct entry* next;
}entry;

typedef struct{
    entry **buckets; //массив указателей на entry
    size_t capacity;
    size_t size;
}hash_table;


hash_table* create(size_t capacity);
size_t hash(const char* key);
void resize(hash_table** table);
void insert(hash_table** table, const char* key, int value);
bool contains(hash_table* table, const char* key);
int* get(hash_table* table, const char* key);
void remove_t(hash_table* table, const char* key);
void free_t(hash_table* table);

#endif