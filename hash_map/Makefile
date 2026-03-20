CC=gcc
CFLAGS=-Wall -Wextra -g

all:
	$(CC) $(CFLAGS) test_hash_table.c hash_table.c -o test

run:
	./test

valgrind:
	valgrind ./test

clean:
	rm -f test