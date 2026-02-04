.PHONY: tests

STD = c99
CC = gcc
LDFLAGS = -fsanitize=address,undefined
CFLAGS = -std=$(STD) $(LDFLAGS) -g -fno-omit-frame-pointer -Wall -Wextra

tests:
	mkdir -p tmp
	$(CC) $(CFLAGS) $(LDFLAGS) -o tmp/tests tests.c && ./tmp/tests

