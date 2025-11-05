CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99
gram: gram.c
	$(CC) $(CFLAGS) gram.c -o gram 