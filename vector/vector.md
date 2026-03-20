# Vector in C

Dynamic array implementation in C

## Features

- dynamic resizing
- insert / remove
- reserve / shrink_to_fit
- bounds checking
- memory-safe (tested with Valgrind)

## Structure

- `vec.c` – implementation
- `vec.h` – API
- `test_vec.c` – tests

## Build

gcc test_vec.c vec.c -o test

## Run

./test

## Memory check

valgrind ./test