# Hash Table in C

Hash table implementation using separate chaining

## Features

- string keys
- insert / get / remove / contains
- collision handling via linked lists
- dynamic resizing (load factor 0.75)
- memory-safe (checked with Valgrind)

## Structure

- `hash_table.c` – implementation
- `hash_table.h` – API
- `test_hash_table.c` – tests

## Build

gcc test_hash_table.c hash_table.c -o test

## Run

./test

## Memory check

valgrind ./test