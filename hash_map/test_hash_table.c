#include <stdio.h>
#include <assert.h>
#include "hash_table.h"

void test_insert_get()
{
    hash_table* ht = create(8);

    insert(&ht, "apple", 5);
    insert(&ht, "banana", 10);

    assert(*get(ht, "apple") == 5);
    assert(*get(ht, "banana") == 10);

    free_t(ht);
}

void test_update()
{
    hash_table* ht = create(8);

    insert(&ht, "apple", 5);
    insert(&ht, "apple", 20);

    assert(*get(ht, "apple") == 20); //возьми значение по ключу "apple" 
    //и проверь, что оно равно 20

    free_t(ht);
}

void test_remove()
{
    hash_table* ht = create(8);

    insert(&ht, "dog", 3);
    remove_t(ht, "dog");

    assert(get(ht, "dog") == NULL);

    free_t(ht);
}

void test_collision()
{
    hash_table* ht = create(2);

    insert(&ht, "a", 1);
    insert(&ht, "b", 2);

    assert(*get(ht, "a") == 1);
    assert(*get(ht, "b") == 2);

    free_t(ht);
}

int main(){
    // test_insert_get();
    // test_update();
    // test_remove();
    // test_collision();

    // printf("All tests passed!\n");

    hash_table* table = create(10);

    insert(&table,"hui",-10);
    insert(&table,"begemot",1488);
    insert(&table,"smasher",19);

    // remove_t(table,"porn");

    if(contains(table,"smasher")) printf("Yes, indeed\n");

    remove_t(table,"smasher");

    if(contains(table,"smasher")) printf("Yes, indeed\n");

    printf("For key 'hui' we get: %i\n", *get(table, "hui"));
}