CC = gcc
CFLAGS = -Wall -Wextra -g

all: allocator_test

allocator_test: src/allocator.c tests/main.c
	$(CC) $(CFLAGS) -I./src src/allocator.c tests/main.c -o allocator_test

clean:
	rm -f allocator_test