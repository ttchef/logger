
CC := gcc
CFLAGS := -Wall -Wextra -pedantic -fsanitize=address -g -std=c11

all:
	$(CC) $(CFLAGS) main.c -o main
