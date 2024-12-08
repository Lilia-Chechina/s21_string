CC = gcc
CFLAGS = -Wall -Wextra -std=c11

all: test

test: test_str.c str.c str.h
	$(CC) $(CFLAGS) -o test test_str.c str.c
	./test

clean:
	rm -f test
