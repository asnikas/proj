CC=gcc
CFLAGS=-Wall -Wextra -Werror

all: shell

shell: main.o shell.o
	$(CC) $(CFLAGS) main.o shell.o -o shell

main.o: main.c shell.h
	$(CC) $(CFLAGS) -c main.c

shell.o: shell.c shell.h
	$(CC) $(CFLAGS) -c shell.c

clean:
	rm -f *.o shell