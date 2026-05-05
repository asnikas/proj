# Custom C Memory Allocator

A memory management library implemented in C using `sbrk`. 

## Features
- Implementation of `malloc`, `free`, `realloc`, and `calloc`.
- **Memory Alignment**: All blocks are 8-byte aligned.
- **Coalescing**: Automatic merging of adjacent free blocks to prevent fragmentation.
- **Splitting**: Large free blocks are split to satisfy smaller requests.
- **Heap Consistency Check**: Includes a `check_heap()` function for debugging.