#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

// buckets  -> массив указателей на entry
// capacity -> количество бакетов
// size     -> количество элементов
//size_t - стандартный беззнаковый целочисленный тип

hash_table* create(size_t capacity){

hash_table* table = malloc(sizeof(hash_table));
if(!table) exit(1);
table->buckets = calloc(capacity, sizeof(entry*)); // malloc - выделяет память и заполняет ее мусором
// вместо malloc, calloc выделяет память и заполняет ее нулями [NULL,NULL,NUll,...]
if(!table->buckets) exit(1);
table->size = 0;
table->capacity = capacity;

return table;
}


void free_t(hash_table* table){
    for(size_t i = 0;i < table->capacity;i++){
        while(table->buckets[i] != NULL){
            entry* next = table->buckets[i]->next;
            free(table->buckets[i]->key);
            free(table->buckets[i]);
            table->buckets[i] = next;
        }
    }
free(table->buckets); //поч??
free(table);
}


void resize(hash_table** table){
hash_table *new = create((*table)->capacity * 2);
for(size_t i = 0;i < (*table)->capacity;i++){
    entry* temp = (*table)->buckets[i];
    while(temp != NULL){
        insert(&new,temp->key,temp->value);
        temp = temp->next;
    }
}
free_t(*table);
(*table) = new;
}


size_t hash(const char* key){   
    size_t hash = 5381;
    int c;
    while((c = *key++))
    hash = ((hash << 5) + hash) + c;
    return hash;
}


void insert(hash_table** table, const char* key, int value){
if((*table)->size >= (*table)->capacity * 0.75){
    resize(table);
}

size_t index = hash(key) % (*table)->capacity;

entry* current = (*table)->buckets[index];


// ищем существующий ключ
while(current != NULL){
    if(strcmp(current->key, key) == 0){
        current->value = value;
        return;
    }
    current = current->next;
}

// создаём новый элемент
entry* new_entry = malloc(sizeof(entry));
if(!new_entry) exit(1);
new_entry->key = strdup(key);
new_entry->value = value;
new_entry->next = (*table)->buckets[index];
(*table)->buckets[index] = new_entry;

(*table)->size++;

}


bool contains(hash_table* table, const char* key){
size_t hash_v = hash(key) % table->capacity;
        entry* temp = table->buckets[hash_v];
        while(temp != NULL){
            if(strcmp(temp->key, key) == 0) return true;
            temp = temp->next;
        } 
return false;
}


int* get(hash_table* table, const char* key){
size_t hash_v = hash(key) % table->capacity;

entry* temp = table->buckets[hash_v];
while(temp != NULL){
    if(strcmp(temp->key, key) == 0){
        return &(temp->value);
    }
    temp = temp->next;
        
}
return NULL;
}


void remove_t(hash_table* table, const char* key){

    size_t hash_v = hash(key) % table->capacity;
    entry* temp = table->buckets[hash_v];
    entry* temp2 = NULL;
    while(temp != NULL){
        if(strcmp(temp->key, key) == 0) {
            if(temp2 == NULL){
                table->buckets[hash_v] = temp->next;
            }
            else{
                temp2->next = temp->next;
            }
            table->size--;
            free(temp->key);
            free(temp);
            return;
        }
        temp2 = temp;
        temp = temp->next;
    }
}



// int main(){

//     hash_table* table = create(20);
//     insert(&table,"begemot",1488);
//     printf("Answer for the key - begemot: %i\n", *get(table, "begemot"));
//     return 0;
// } 