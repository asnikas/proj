#include <stdio.h>
#include "allocator.h"

int main() {
    //printf("sizeof block: %li, sizeof footer: %li", sizeof(struct block), sizeof(struct footer));
    test_basic();
    test_reuse();
    test_split();
    test_coalesce();
    test_realloc_grow();
    //test_realloc_shrink();
    test_calloc();
    test_strdup();
    test_stress();
    test_double_free();
    test_invalid_free();
}