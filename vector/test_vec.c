#include <stdio.h>
#include <assert.h>
#include "vec.h"

//assert - проверка условия во время выполнения программы

void test_push_back()
{
    vector* v = vec_create();

    for(int i = 0; i < 1000; i++)
        push_back(v, i);

    assert(size(v) == 1000);

    for(int i = 0; i < 1000; i++)
        assert(*get(v, i) == i);

    vec_free(v);
}

void test_insert()
{
    vector* v = vec_create();

    push_back(v, 1);
    push_back(v, 2);
    push_back(v, 3);

    vec_insert(v, 1, 99);

    assert(*get(v,0) == 1);
    assert(*get(v,1) == 99);
    assert(*get(v,2) == 2);

    vec_free(v);
}

void test_remove()
{
    vector* v = vec_create();

    push_back(v, 1);
    push_back(v, 2);
    push_back(v, 3);

    vec_remove(v, 1);

    assert(size(v) == 2);
    assert(*get(v,0) == 1);
    assert(*get(v,1) == 3);

    vec_free(v);
}

void test_reserve()
{
    vector* v = vec_create();

    vec_reserve(v, 100);

    assert(vec_capacity(v) >= 100);

    vec_free(v);
}

void test_shrink()
{
    vector* v = vec_create();

    for(int i = 0; i < 10; i++)
        push_back(v, i);

    vec_shrink_to_fit(v);

    assert(vec_capacity(v) == size(v));

    vec_free(v);
}

void test_big()
{
    vector* v = vec_create();

    for(int i = 0; i < 1000000; i++)
        push_back(v, i);

    for(int i = 0; i < 1000000; i++)
        assert(*get(v,i) == i);

    vec_free(v);
}

int main()
{
    // test_push_back();
    // test_insert();
    // test_remove();
    // test_reserve();
    // test_shrink();
    // test_big();

    // printf("All tests passed!\n");
    vector* v = vec_create_with_capacity(500000);

    push_back(v,12);
    push_back(v,122);
    push_back(v,32);

    // printf("%i from list\n", *get(v,3));

    return 0;
}