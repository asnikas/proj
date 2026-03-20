CC=gcc
CFLAGS=-Wall -Wextra -g

all:
	$(CC) $(CFLAGS) test_vec.c vec.c -o test

run:
	./test

valgrind:
	valgrind ./test

clean:
	rm -f test